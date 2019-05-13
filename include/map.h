/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** map
*/

#pragma once

#include <stdlib.h> 

typedef enum ITEM_E {
    FOOD,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
} ITEM_T; 

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


void init_map(map_t *map, size_t w, size_t h);
