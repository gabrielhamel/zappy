/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** map
*/

#include <stdio.h>

#include "map.h"

bool init_map(map_t *map, size_t w, size_t h)
{
    printf("INIT MAP\n");
    if (!(map->graph = malloc(sizeof(tile_t *) * h)))
        return (false);
    for (size_t i = 0; i < h; i++) {
        if (!(map->graph[i] = malloc(sizeof(tile_t) * w)))
            return (false);
    }
    return (true);
}

void link_map(tile_t **graph, size_t w, size_t h)
{
    for (size_t x = 0; x < w; x++) {
        for (size_t y = 0; y < h; y++) {
            graph[x][y].x = x;
            graph[x][y].y = y;
        }
    }
    link_top(graph, w, h);
    link_right(graph, w, h);
    link_bottom(graph, w, h);
    link_left(graph, w, h);
}

void add_random_rock(map_t map)
{
    (void)map;
    //TODO 
}
