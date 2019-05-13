/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** list_close
*/

#include <stdlib.h>
#include <string.h>
#include "socket.h"

static void remove_first_elem_no_close(sock_list_t *list, sock_t *socket)
{
    sock_node_t *node = list->start->next;

    if (FD_ISSET(socket->fd, &list->fdlist))
        FD_CLR(socket->fd, &list->fdlist);
    socket_destroy_no_close(socket);
    free(list->start);
    list->start = node;
}

int socket_list_remove_no_close(sock_list_t *list, sock_t *socket)
{
    sock_node_t *node = list->start;
    sock_node_t *tmp;

    if (node == NULL)
        return (-1);
    if (list->start->socket == socket) {
        remove_first_elem_no_close(list, socket);
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
    socket_destroy_no_close(tmp->socket);
    free(tmp);
    return (0);
}

int socket_destroy_no_close(sock_t *socket)
{
    if (socket->dtor != NULL)
        socket->dtor(socket, socket->data);
    free(socket);
    return (0);
}

int socket_list_destroy_no_close(sock_list_t *list)
{
    sock_node_t *node = list->start;
    sock_node_t *tmp = NULL;

    while (node != NULL) {
        tmp = node->next;
        socket_destroy_no_close(node->socket);
        free(node);
        node = tmp;
    }
    FD_ZERO(&list->fdlist);
    free(list);
    return (0);
}