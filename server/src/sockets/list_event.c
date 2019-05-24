/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** list_event
*/

#include <stdlib.h>
#include <string.h>
#include "socket.h"
#include "server.h"

sock_t *socket_list_get_socket(sock_list_t *list, int fd)
{
    sock_node_t *node = list->start;

    if (list->start == NULL)
        return (NULL);
    for (; node != NULL; node = node->next)
        if (node->socket->fd == fd)
            return (node->socket);
    return (NULL);
}

sock_t **socket_list_get_event(sock_list_t *list)
{
    fd_set tmp = list->fdlist;
    struct timeval val = {.tv_sec = 0, .tv_usec = REFRESH_USEC};
    int ret = select(FD_SETSIZE, &tmp, NULL, NULL, &val);
    sock_t **tab = NULL;
    size_t idx = 0;

    if (ret == 0 || ret == -1)
        return (NULL);
    tab = malloc(sizeof(sock_t *) * (ret + 1));
    if (tab == NULL)
        return (NULL);
    memset(tab, 0, sizeof(sock_t *) * (ret + 1));
    for (int i = 0; i < FD_SETSIZE; i++)
        if (FD_ISSET(i, &tmp))
            tab[idx++] = socket_list_get_socket(list, i);
    return (tab);
}