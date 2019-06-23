/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** link
*/

#include "map.h"

void link_top(tile_t **graph, size_t w, size_t h)
{
    for (size_t x = 0; x < w; x++)
        for (size_t y = 1; y < h; y++)
            graph[y][x].top = &graph[y - 1][x];
    for (size_t x = 0; x < w; x++)
        graph[0][x].top = &graph[h - 1][x];
}

void link_right(tile_t **graph, size_t w, size_t h)
{
    for (size_t x = 0; x < w - 1; x++)
        for (size_t y = 0; y < h; y++)
            graph[y][x].right = &graph[y][x + 1];
    for (size_t y = 0; y < h; y++)
        graph[y][w - 1].right = &graph[y][0];
}

void link_bottom(tile_t **graph, size_t w, size_t h)
{
    for (size_t x = 0; x < w; x++)
        for (size_t y = 0; y < h - 1; y++)
            graph[y][x].bottom = &graph[y + 1][x];
    for (size_t x = 0; x < w; x++)
        graph[h - 1][x].bottom = &graph[0][x];
}

void link_left(tile_t **graph, size_t w, size_t h)
{
    for (size_t x = 1; x < w; x++)
        for (size_t y = 0; y < h; y++)
            graph[y][x].left = &graph[y][x - 1];
    for (size_t y = 0; y < h; y++)
        graph[y][0].left = &graph[y][w - 1];
}
