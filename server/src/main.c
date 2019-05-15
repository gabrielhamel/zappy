/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** main
*/

#include <stdlib.h>

#include "core.h"

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    size_t w = 10;
    size_t h = 10;

    core_t core;

    init_core(&core, w, h);

    loop_core(&core);

    return (0);
}
