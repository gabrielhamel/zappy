/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** core
*/

#pragma once

#include "map.h"

typedef struct core_s {
    map_t map;
} core_t;


void init_core(core_t *core, size_t w, size_t h);

void core_loop(core_t *core);
