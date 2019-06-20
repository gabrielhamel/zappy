/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** incant
*/

#include "graph_commands.h"
#include "ia_commands.h"
#include "server.h"

void destroy_incantation(sock_list_t *list, incantation_t *inc, bool success)
{
    char buff[4096] = {0};
    char *str;

    LIST_REMOVE(inc, next);
    for (size_t i = 0; i < inc->nb_ia; i++) {
        if (inc->ia[i] == NULL)
            continue;
        if (success) {
            inc->ia[i]->level++;
            graph_send_ia_plv(list, inc->ia[i]);
        }
        sock_write(ia_get_sock(inc->ia[i]), "Current level: %d\n", inc->ia[i]->level);
        inc->ia[i]->fixed = false;
    }
    str = success ? "ok" : "ko";
    sprintf(buff, "pie %ld %ld %s\n", inc->tile->x, inc->tile->y, str);
    send_all_graphics(list, buff);
    free(inc->ia);
    free(inc);
}

void incantation_player_death(sock_list_t *list, ia_t *ia)
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
            inc->ia[i] = NULL;
            if ((int)inc->nb_valid < inc_get_level(inc->level, 0))
                destroy_incantation(list, inc, false);
        }
        inc = tmp;
    }
}

void new_incantation(sock_list_t *list, ia_t **ia, tile_t *tile, zarg_t *zarg)
{
    incantation_t *inc = malloc(sizeof(incantation_t));
    game_t *game = GET_GAME(list);

    inc->ia = ia;
    inc->nb_ia = array_lenght((char **)ia);
    inc->nb_valid = inc->nb_ia;
    inc->tile = tile;
    inc->time = 300.f / zarg->freq;
    inc->level = ia[0]->level + 1;
    LIST_INSERT_HEAD(&game->incantations, inc, next);
    for (size_t i = 0; i < inc->nb_ia; i++) {
        inc->ia[i]->fixed = true;
        sock_write(ia_get_sock(inc->ia[i]), "Elevation underway\n");
    }
}

void refresh_incantation(sock_list_t *list, float ellapsed)
{
    game_t *game = GET_GAME(list);
    incantation_t *inc;
    incantation_t *tmp;

    for (inc = game->incantations.lh_first; inc;) {
        inc->time -= ellapsed;
        tmp = inc->next.le_next;
        if (inc->time < 0)
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
        sock_write(cli, "ko\n");
        return;
    }
    new_incantation(list, ias, tile, zarg);
    sprintf(buff, "pic %ld %ld %d", tile->x, tile->y, ia->level + 1);
    for (size_t i = 0; ias[i] != NULL; i++)
        sprintf(buff + strlen(buff), " %d", ias[i]->id);
    sprintf(buff + strlen(buff), "\n");
    send_all_graphics(list, buff);
}
