/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** time_manage
*/

#include "ia_commands.h"
#include "server.h"

static buffer_cmd_t *get_head(sock_t *sock)
{
    zappy_client_t *cli;

    if (sock == NULL)
        return (NULL);
    if (sock->type != CLIENT)
        return (NULL);
    cli = sock->data;
    if (cli->cli_type != IA)
        return (NULL);
    return (list_head(LIST_CMD(sock)));
}

void refresh_cmd(sock_list_t *list, zarg_t *zarg, long int ellapsed)
{
    buffer_cmd_t *tmp;
    sock_node_t *i = list->start;
    sock_node_t *next;

    while (i) {
        tmp = get_head(i->socket);
        if (tmp == NULL) {
            i = i->next;
            continue;
        }
        next = i->next;
        tmp->time -= (float)ellapsed / 1000.f;
        if (tmp->time <= 0)
            exec_ia_cmd(i->socket, list, zarg);
        i = next;
    }
}