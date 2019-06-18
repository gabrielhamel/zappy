/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** look
*/

#include "graph_commands.h"
#include "server.h"

void cmd_ia_look(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    ia_t *ia = ZAPPY_CLIENT(cli)->client.ia;

    (void)arg;
    (void)zarg;
    (void)list;
    (void)ia;
}
