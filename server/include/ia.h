/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** ia
*/

#pragma once

#include <stdlib.h>
#include "sys/queue.h"
// #include "game.h"

typedef struct ia_s {
    STAILQ_HEAD(, buffer_cmd_s) list_head;
    size_t x;
    size_t y;
    // team_t *team;
} ia_t;