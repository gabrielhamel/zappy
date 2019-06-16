/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** connect_nbr
*/

#include "graph_commands.h"
#include "server.h"

size_t get_nb_hatcheg_egg(team_t *team)
{
    egg_t *egg;
    size_t nb = 0;

    LIST_FOREACH(egg, &team->eggs, next) {
        if (egg->state != HATCHED)
            continue;
        nb++;
    }
    return nb;
}

void cmd_ia_cnt_nbr(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    ia_t *ia = ZAPPY_CLIENT(cli)->client.ia;
    int nb_remaining;

    (void)arg;
    (void)list;
    nb_remaining = zarg->clients_nb - ia->team->nb_clients +
    get_nb_hatcheg_egg(ia->team);
    nb_remaining = nb_remaining < 0 ? 0 : nb_remaining;
    dprintf(cli->fd, "%d\n", nb_remaining);
}
