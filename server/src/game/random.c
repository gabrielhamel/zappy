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

void add_random_food(tile_t *map)
{
    map->items[FOOD] += (rand() % 101) / 60;
}
