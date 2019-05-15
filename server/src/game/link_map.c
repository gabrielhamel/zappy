/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** link
*/

#include "map.h"

void link_top(tile_t **graph, size_t w, size_t h)
{
    for (size_t x = 0; x < w; x++) {
        for (size_t y = 1; y < h; y++) {
            graph[x][y].top = &graph[x][y - 1]; // NE FONCTIONNE PEUT ËTRE PAS, PAREIL POUR LES AUTRES EN DESSOUS
        }
    }
    for (size_t x = 0; x < w; x++) {
        graph[x][0].top = &graph[x][h];
    }
}

void link_right(tile_t **graph, size_t w, size_t h)
{
    for (size_t x = 0; x < w - 1; x++) {
        for (size_t y = 1; y < h; y++) {
            graph[x][y].right = &graph[x + 1][y];
        }
    }
    for (size_t y = 0; y < h; y++) {
        graph[w][y].right = &graph[0][y];
    }
}

void link_bottom(tile_t **graph, size_t w, size_t h)
{
    for (size_t x = 0; x < w; x++) {
        for (size_t y = 0; y < h - 1; y++) {
            graph[x][y].bottom = &graph[x][y + 1];
        }
    }
    for (size_t x = 0; x < w; x++) {
        graph[x][h].bottom = &graph[x][0];
    }
}


void link_left(tile_t **graph, size_t w, size_t h)
{
    for (size_t x = 1; x < w; x++) {
        for (size_t y = 0; y < h; y++) {
            graph[x][y].left = &graph[x - 1][y];
        }
    }
    for (size_t y = 0; y < h; y++) {
        graph[0][y].left = &graph[w][y];
    }
}
