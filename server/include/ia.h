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

typedef enum {
    NORTH = 1,
    EAST,
    SOUTH,
    WEAST
} facing_t;

typedef struct {
    STAILQ_HEAD(, buffer_cmd_s) list_head;
    int id;
    size_t x;
    size_t y;
    int level;
    facing_t ori;
    struct team_t *team;
} ia_t;
