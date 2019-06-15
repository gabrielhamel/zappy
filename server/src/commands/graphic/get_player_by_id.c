/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** get_player_by_id
*/

#include "graph_commands.h"

ia_t *get_player_by_id(int id, sock_list_t *list)
{
    sock_node_t *node = list->start;
    zappy_client_t *cli;

    for (; node != NULL; node = node->next) {
        if (node->socket->type != CLIENT)
            continue;
        cli = node->socket->data;
        if (cli == NULL)
            continue;
        if (cli->cli_type != IA)
            continue;
        if (cli->client.ia->id == id)
            return cli->client.ia;
    }
    return NULL;
}
