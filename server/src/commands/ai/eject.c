/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** eject
*/

#include "graph_commands.h"
#include "ia_commands.h"

static void send_res(sock_list_t *list, sock_t *cli, size_t nb)
{
    char buff[4096] = {0};

    if (nb == 0)
        sock_write(cli, "ko\n");
    else {
        sock_write(cli, "ok\n");
        sprintf(buff, "pex %d\n", cli->fd);
        send_all_graphics(list, buff);
    }
}

static void incantation_player_ejected(sock_list_t *list, ia_t *ia)
{
    game_t *game = GET_GAME(list);
    incantation_t *inc;
    size_t i;
    incantation_t *tmp;

    for (inc = game->incantations.lh_first; inc;) {
        for (i = 0; inc->ia[i] != ia && i < inc->nb_ia; i++);
        tmp = inc->next.le_next;
        if (i != inc->nb_ia) {
            inc->nb_valid--;
            dprintf(inc->ia[i]->id, "Current level: %d\n", inc->ia[i]->level);
            inc->ia[i] = NULL;
            if ((int)inc->nb_valid < inc_get_level(inc->level, 0))
                destroy_incantation(list, inc, false);
        }
        inc = tmp;
    }
}

static void eject(sock_list_t *list, ia_t *ejecter, ia_t *ejected)
{
    int k = 0;
    tile_t *begin = GET_TILE(GET_GAME(list), ejected->x, ejected->y);
    tile_t *end;

    ia_move(list, ejected, ejecter->ori);
    end = GET_TILE(GET_GAME(list), ejected->x, ejected->y);
    if (ejecter->ori == NORTH)
        k = get_direction(ejected, ZERO, NEGATIVE);
    if (ejecter->ori == EAST)
        k = get_direction(ejected, NEGATIVE, ZERO);
    if (ejecter->ori == SOUTH)
        k = get_direction(ejected, ZERO, POSITIVE);
    if (ejecter->ori == WEAST)
        k = get_direction(ejected, POSITIVE, ZERO);
    dprintf(ejected->id, "eject: %d\n", k);
    if (begin != end)
        incantation_player_ejected(list, ejected);
}

void cmd_ia_eject(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    zappy_client_t *client;
    ia_t *me = ZAPPY_CLIENT(cli)->client.ia;
    size_t nb = 0;
    ia_t *ia;

    (void)arg;
    (void)zarg;
    for (sock_node_t *node = list->start; node != NULL; node = node->next) {
        client = node->socket->data;
        if (node->socket->type != CLIENT || client == NULL ||
        client->cli_type != IA)
            continue;
        ia = client->client.ia;
        if (ia->x != me->x || ia->y != me->y || ia == me)
            continue;
        nb++;
        eject(list, me, ia);
    }
    send_res(list, cli, nb);
}
