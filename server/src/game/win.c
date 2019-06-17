/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** win
*/

#include "graph_commands.h"
#include "ia_commands.h"
#include "server.h"

bool check_win_ia(sock_list_t *list, ia_t *ia)
{
    char buff[4096] = {0};
    zappy_client_t *client;
    sock_t *cli;

    if (ia->level != 8)
        return false;
    sprintf(buff, "seg %s\n", ia->team->name);
    send_all_graphics(list, buff);
    for (sock_node_t *node = list->start; node != NULL;) {
        cli = node->socket;
        client = node->socket->data;
        node = node->next;
        if (cli->type != CLIENT || client == NULL ||
        client->cli_type != IA)
            continue;
        ia = client->client.ia;
        destroy_ftp_sock(list, cli);
    }
    return true;
}
