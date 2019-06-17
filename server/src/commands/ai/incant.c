/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** incant
*/

#include "graph_commands.h"
#include "ia_commands.h"
#include "server.h"

void new_incantation(game_t *game, ia_t **ia, tile_t *tile, zarg_t *zarg)
{
    incantation_t *inc = malloc(sizeof(incantation_t));

    inc->ia = ia;
    inc->nb_ia = array_lenght((char **)ia);
    inc->tile = tile;
    inc->time = 300.f / zarg->freq;
    LIST_INSERT_HEAD(&game->incantations, inc, next);
    for (size_t i = 0; i < inc->nb_ia; i++) {
        inc->ia[i]->fixed = true;
        dprintf(inc->ia[i]->id, "Elevation underway\n");
    }
}

void destroy_incantation(sock_list_t *list, incantation_t *inc, bool success)
{
    char buff[4096] = {0};
    int level;

    LIST_REMOVE(inc, next);
    for (size_t i = 0; i < inc->nb_ia; i++) {
        if (success)
            inc->ia[i]->level++;
        dprintf(inc->ia[i]->id, "Current level: %d\n", inc->ia[i]->level);
        level = inc->ia[i]->level;
        inc->ia[i]->fixed = false;
    }
    sprintf(buff, "pie %ld %ld %d\n", inc->tile->x, inc->tile->y, level);
    send_all_graphics(list, buff);
    free(inc->ia);
    free(inc);
}

void refresh_incantation(sock_list_t *list, float ellapsed)
{
    game_t *game = GET_GAME(list);
    incantation_t *inc;
    incantation_t *tmp;

    for (inc = game->incantations.lh_first; inc;) {
        inc->time -= ellapsed;
        tmp = inc->next.le_next;
        if (inc->time <= 0)
            destroy_incantation(list, inc, true);
        inc = tmp;
    }
}

void cmd_ia_incant(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    ia_t *ia = ZAPPY_CLIENT(cli)->client.ia;
    ia_t **ias = get_players_incantable(GET_GAME(list), ia, ia->level + 1);
    tile_t *tile = GET_TILE(GET_GAME(list), ia->x, ia->y);
    char buff[4096] = {0};

    (void)arg;
    if (ias == NULL) {
        dprintf(cli->fd, "ko\n");
        return;
    }
    new_incantation(GET_GAME(list), ias, tile, zarg);
    sprintf(buff, "pic %ld %ld %d", tile->x, tile->y, ia->level + 1);
    for (size_t i = 0; ias[i] != NULL; i++)
        sprintf(buff + strlen(buff), " %d", ias[i]->id),
    sprintf(buff + strlen(buff), "\n");
    send_all_graphics(list, buff);
}
