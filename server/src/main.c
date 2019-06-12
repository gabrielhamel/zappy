/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** main
*/

#include <stdlib.h>
#include "server.h"

int main(int ac, char **av)
{
    arg_t arg = {0};
    zarg_t zarg = {0};
    int ret;

    if (parsing(&arg, ac, av) == false)
        return (84);
    arg_to_zarg(&arg, &zarg);
    ret = launch_zappy(&zarg);
    free(zarg.team_names);
    return (ret);
}
