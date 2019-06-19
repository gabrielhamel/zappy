/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** map
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "map.h"

void init_tile(tile_t *tile)
{
    for (size_t i = 0; i < N_ITEMS; i++)
        tile->items[i] = 0;
}

bool init_map(map_t *map, size_t w, size_t h)
{
    map->graph = malloc(sizeof(tile_t *) * h);
    for (size_t i = 0; i < h; i++)
        map->graph[i] = malloc(sizeof(tile_t) * w);
    map->h = h;
    map->w = w;
    link_map(map->graph, w, h);
    return (true);
}

void link_map(tile_t **graph, size_t w, size_t h)
{
    for (size_t y = 0; y < h; y++) {
        for (size_t x = 0; x < w; x++) {
            graph[y][x].x = x;
            graph[y][x].y = y;
            init_tile(&graph[y][x]);
            add_random_rock(&graph[y][x]);
        }
    }
    link_top(graph, w, h);
    link_right(graph, w, h);
    link_bottom(graph, w, h);
    link_left(graph, w, h);
}

void add_random_rock(tile_t *tile)
{
    for (int i = 0; i < 6; i++)
        tile->items[1 + i] += (rand() % 101) / 87;
}
