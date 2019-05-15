/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** main
*/

#include <stdlib.h>

#include "server.h"
// #include "core.h"

int main(int ac, char **av)
{
    exec_command(NULL, NULL, NULL, NULL); // test des listes chaînées

    // size_t w = 10;
    // size_t h = 10;
    arg_t arg = {0};
    zarg_t zarg = {0};

    // core_t core;

    // init_core(&core, w, h);

    // loop_core(&core);

    if (parsing(&arg, ac, av) == false)
        return (84);
    return (launch_zappy(&zarg));

}
