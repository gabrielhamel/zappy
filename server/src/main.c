/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** main
*/

#include "server.h"

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    exec_command(NULL, NULL, NULL);
    launch_zappy(8080);
    return (0);
}