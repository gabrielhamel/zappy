/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** main
*/

#include "server.h"

int main(int ac, char **av)
{
    arg_t arg = {0};
    zarg_t zarg = {0};

    if (parsing(&arg, ac, av) == false)
        return (84);
    return (launch_zappy(&zarg));
}