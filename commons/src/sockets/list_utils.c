/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** list
*/

#include <stdlib.h>
#include <string.h>
#include "socket.h"

int socket_list_add(sock_list_t *list, sock_t *socket)
{
    sock_node_t *idx = NULL;
    sock_node_t *node;

    node = malloc(sizeof(sock_node_t));
    if (node == NULL)
        return (-1);
    FD_SET(socket->fd, &list->fdlist);
    node->next = NULL;
    node->socket = socket;
    if (list->start == NULL) {
        list->start = node;
        return (0);
    }
    for (idx = list->start; idx->next != NULL; idx = idx->next);
    idx->next = node;
    return (0);
}

static void remove_first_elem(sock_list_t *list, sock_t *socket)
{
    sock_node_t *node = list->start->next;

    if (FD_ISSET(socket->fd, &list->fdlist))
        FD_CLR(socket->fd, &list->fdlist);
    socket_destroy(socket);
    free(list->start);
    list->start = node;
}

int socket_list_remove(sock_list_t *list, sock_t *socket)
{
    sock_node_t *node = list->start;
    sock_node_t *tmp;

    if (node == NULL)
        return (-1);
    if (list->start->socket == socket) {
        remove_first_elem(list, socket);
        return (0);
    }
    for (; node->next != NULL && node->next->socket != socket;
    node = node->next);
    if (node->next == NULL && node->socket != socket)
        return (-1);
    tmp = node->next;
    node->next = node->next->next;
    if (FD_ISSET(tmp->socket->fd, &list->fdlist))
        FD_CLR(tmp->socket->fd, &list->fdlist);
    socket_destroy(tmp->socket);
    free(tmp);
    return (0);
}

int socket_list_destroy(sock_list_t *list)
{
    sock_node_t *node = list->start;
    sock_node_t *tmp = NULL;

    while (node != NULL) {
        tmp = node->next;
        socket_destroy(node->socket);
        free(node);
        node = tmp;
    }
    FD_ZERO(&list->fdlist);
    free(list);
    return (0);
}

sock_list_t *socket_list_create(void)
{
    sock_list_t *list = malloc(sizeof(sock_list_t));

    if (list == NULL)
        return (NULL);
    memset(list, 0, sizeof(sock_list_t));
    FD_ZERO(&list->fdlist);
    return (list);
}