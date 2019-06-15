/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** connect_nbr
*/

#include "graph_commands.h"
#include "server.h"

void cmd_ia_cnt_nbr(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    ia_t *ia = ZAPPY_CLIENT(cli)->client.ia;
    int nb_remaining;

    (void)arg;
    (void)list;
    nb_remaining = zarg->clients_nb - ia->team->nb_clients;
    nb_remaining = nb_remaining < 0 ? 0 : nb_remaining;
    dprintf(cli->fd, "%d\n", nb_remaining);
}
