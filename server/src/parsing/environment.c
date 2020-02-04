/*
** EPITECH PROJECT, 2020
** PSU_zappy_2018
** File description:
**
*/

#include "server.h"
#include "utils.h"

bool get_environment(zarg_t *args)
{
    char *port = getenv("ZPY_PORT");
    char *width = getenv("ZPY_WIDTH");
    char *height = getenv("ZPY_HEIGHT");
    char *speed = getenv("ZPY_SPEED");
    char *nb_client_team = getenv("ZPY_NB_CLIENT_TEAM_MAX");
    char *team_names = getenv("ZPY_TEAM_NAMES");

    if (!port || !width || !height || !speed || !nb_client_team || !team_names)
        return false;

    if (!check_port(port)                ||
        !check_dimension(width)          ||
        !check_dimension(height)         ||
        !check_freq(speed)               ||
        !check_clients_nb(nb_client_team))
            return false;

    char **teams = tokenize(team_names, ":");
    if (!teams)
        return false;
    for (size_t i = 0; teams[i]; i++)
        if (check_team(teams[i]) == false)
            return false;

    args->team_names = teams;
    args->port = strtol(port, NULL, 10);
    args->width = strtol(width, NULL, 10);
    args->height = strtol(height, NULL, 10);
    args->freq = strtof(speed, NULL);
    args->clients_nb = strtol(nb_client_team, NULL, 10);
    return true;
}
