/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** main
*/

#include <stdlib.h>
#include <time.h>
#include "server.h"

int main(int ac, char **av)
{
    arg_t arg = {0};
    zarg_t zarg = {0};
    int ret;

    srand(time(NULL));
    if (parsing(&arg, ac, av))
        arg_to_zarg(&arg, &zarg);
    else if (get_environment(&zarg) == false)
        return 84;
    ret = launch_zappy(&zarg);
    free(zarg.team_names);
    return (ret);
}
