/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** map
*/

#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "socket.h"
#include "item.h"

#define GET_TILE(game, x, y) (&game->map.graph[y][x])

typedef struct tile_s tile_t;

typedef struct tile_s {
    size_t x;
    size_t y;
    tile_t *top;
    tile_t *right;
    tile_t *bottom;
    tile_t *left;
    unsigned short items[N_ITEMS];
} tile_t;

typedef struct map_s {
    size_t w;
    size_t h;
    tile_t **graph;
} map_t;

bool init_map(map_t *map, size_t w, size_t h);
void add_random_rock(tile_t *tile);
void add_random_food(sock_list_t *list, map_t *map);
void send_bct_change(sock_list_t *list, tile_t *tile);
void link_map(tile_t **graph, size_t w, size_t h);

void link_top(tile_t **graph, size_t w, size_t h);
void link_right(tile_t **graph, size_t w, size_t h);
void link_bottom(tile_t **graph, size_t w, size_t h);
void link_left(tile_t **graph, size_t w, size_t h);
