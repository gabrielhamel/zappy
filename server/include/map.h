/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** map
*/

#pragma once

#include <stdlib.h>
#include <stdbool.h>

#include "item.h"

typedef struct tile_s tile_t;

typedef struct tile_s {
    size_t x;
    size_t y;
    tile_t *top;
    tile_t *right;
    tile_t *bottom;
    tile_t *left;
    ITEM_T items[];
} tile_t;

typedef struct map_s {
    size_t w;
    size_t h;
    tile_t **graph;
} map_t;


bool init_map(map_t *map, size_t w, size_t h);
void link_top(tile_t **graph, size_t w, size_t h);
void link_right(tile_t **graph, size_t w, size_t h);
void link_bottom(tile_t **graph, size_t w, size_t h);
void link_left(tile_t **graph, size_t w, size_t h);
