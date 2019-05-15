/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** core
*/

#include <stdio.h>

#include "core.h"

bool init_core(core_t *core, size_t w, size_t h)
{
    printf("INIT CORE\n");
    return (init_map(&core->map, w, h));
}

void core_loop(core_t *core)
{
    (void)core;
}
