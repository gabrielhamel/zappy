/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** incantation
*/

#include "ia.h"

static const int incantation[7][7] = {
    {1, 1, 0, 0, 0, 0, 0},
    {2, 1, 1, 1, 0, 0, 0},
    {2, 2, 0, 1, 0, 2, 0},
    {4, 1, 1, 2, 0, 1, 0},
    {4, 1, 2, 1, 3, 0, 0},
    {6, 1, 2, 3, 0, 1, 0},
    {6, 2, 2, 2, 2, 2, 1}
};

int inc_get_level(int level, int value)
{
    return incantation[level - 2][value];
}

static void insert_ia(ia_t ***array, ia_t *ia)
{
    ia_t **tab = *array;
    size_t len = array_lenght((char **)tab);
    ia_t **ptr = realloc(tab, sizeof(ia_t *) * (len + 2));

    ptr[len] = ia;
    ptr[len + 1] = NULL;
    *array = ptr;
}

static bool is_on_tile(tile_t *tile, ia_t *me, int level, ia_t *ia)
{
    const int *require = incantation[level - 2];

    if (ia->x != tile->x || ia->y != tile->y)
        return false;
    if (ia == me)
        return false;
    if (ia->level != level - 1)
        return false;
    if (tile->items[1] != require[1] || tile->items[2] != require[2] ||
        tile->items[3] != require[3] || tile->items[4] != require[4] ||
        tile->items[5] != require[5] || tile->items[6] != require[6])
            return false;
    return true;
}

static void explore_team(game_t *game, ia_t ***array, int level, ia_t *me)
{
    ia_t *ia;
    tile_t *tile = GET_TILE(game, me->x, me->y);

    for (size_t t = 0; t < game->nb_teams; t++)
        for (size_t p = 0; p < game->teams[t]->nb_clients; p++) {
            ia = ZAPPY_CLIENT(game->teams[t]->sock[p])->client.ia;
            is_on_tile(tile, me, level, ia) ? insert_ia(array, ia) : 0;
        }
}

ia_t **get_players_incantable(game_t *game, ia_t *me, int level)
{
    ia_t **array = malloc(sizeof(ia_t *));
    tile_t *tile = GET_TILE(game, me->x, me->y);

    if (array == NULL)
        return NULL;
    if (level < 2 || level > 8) {
        free(array);
        return NULL;
    }
    array[0] = NULL;
    if (!is_on_tile(tile, NULL, level, me)) {
        free(array);
        return NULL;
    }
    insert_ia(&array, me);
    explore_team(game, &array, level, me);
    if ((int)array_lenght((char **)array) < incantation[level - 2][0]) {
        free(array);
        return NULL;
    }
    return array;
}
