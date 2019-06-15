/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** random
*/

#include <stdio.h>
#include "map.h"
#include "graph_commands.h"

void graph_send_tile_bct(sock_list_t *list, tile_t *tile)
{
    char buff[4096] = {0};

    sprintf(buff, "bct %ld %ld %hd %hd %hd %hd %hd %hd %hd\n",
        tile->x, tile->y,
        tile->items[0], tile->items[1], tile->items[2], tile->items[3],
        tile->items[4], tile->items[5], tile->items[6]);
    send_all_graphics(list, buff);
}

void add_random_food(sock_list_t *list, map_t *map)
{
    int value;

    for (size_t y = 0; y < map->h; y++)
        for (size_t x = 0; x < map->w; x++) {
            value = (rand() % 101) / 87;
            map->graph[y][x].items[0] += value;
            value ? graph_send_tile_bct(list, &map->graph[y][x]) : 0;
        }
}
