/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** map
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"

void init_tile(tile_t* tile)
{
    for (size_t i = 0; i < N_ITEMS; i++)
        tile->items[i] = 0;
}

bool init_map(map_t *map, size_t w, size_t h)
{
    if (!(map->graph = malloc(sizeof(tile_t *) * h)))
        return (false);
    for (size_t i = 0; i < h; i++) {
        if (!(map->graph[i] = malloc(sizeof(tile_t) * w)))
            return (false);
    }
    map->h = h;
    map->w = w;
    link_map(map->graph, w, h);
    return (true);
}

void link_map(tile_t **graph, size_t w, size_t h)
{
    for (size_t x = 0; x < w; x++) {
        for (size_t y = 0; y < h; y++) {
            graph[x][y].x = x;
            graph[x][y].y = y;
            init_tile(&graph[x][y]);
        }
    }
    link_top(graph, w, h);
    // link_right(graph, w, h);
    link_bottom(graph, w, h);
    link_left(graph, w, h);
}

void add_random_rock(map_t map)
{
    (void)map;
}

char *tile_to_string(tile_t *tile)
{
    char *res;
    char temp[12];

    memset(temp, 0, 12);
    sprintf(temp, "%d", tile->items[FOOD]);
    str_add(2, res, temp);

    for (size_t i = 0; i < N_ITEMS; i ++) {
        memset(temp, 0, 12);
        sprintf(temp, "%d", tile->items[FOOD]);
        str_add(3, res, temp, ",");
    }
    return (res);
}
