/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** ia
*/

#pragma once

#include <stdlib.h>
#include <sys/queue.h>
#include "game.h"
#include "item.h"

typedef enum {
    NORTH = 1,
    EAST,
    SOUTH,
    WEAST
} facing_t;

typedef struct ia_s {
    STAILQ_HEAD(, buffer_cmd_s) list_head;
    int id;
    int inventory[N_ITEMS];
    size_t x;
    size_t y;
    int level;
    facing_t ori;
    struct team_t *team;
    float live;
} ia_t;

typedef enum {
    POSITIVE = -1,
    ZERO,
    NEGATIVE
} direction_t;

int get_direction(ia_t *ia, direction_t x, direction_t y);
