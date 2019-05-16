/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** player
*/

#pragma once

#include <sys/queue.h>

typedef struct player_s {
    STAILQ_HEAD(, buffer_cmd_s) list_head;
} player_t;
