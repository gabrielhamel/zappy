/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** ia
*/

#pragma once

#include <stdlib.h>
#include <sys/queue.h>
#include <stdbool.h>
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
    bool fixed;
} ia_t;

typedef enum {
    POSITIVE = -1,
    ZERO,
    NEGATIVE
} direction_t;

int get_direction(ia_t *ia, direction_t x, direction_t y);
void incantation_player_death(sock_list_t *list, ia_t *ia);
sock_t *ia_get_sock(sock_t *sock, ia_t *ia);
