/*
** EPITECH PROJECT, 2019
** check_team_names.c
** File description:
** checking the team names
*/

#include "game.h"
#include "buffer_cmd.h"

bool check_team_names(char **arg, zarg_t *zarg, sock_t *cli)
{
    size_t i;

    for (i = 0; zarg->team_names[i] != NULL; i++) {
        if (!strcmp(arg[0], zarg->team_names[i])) {
            return (true);
        }
    }
    // ZAPPY_CLIENT(cli)->client.ia->team->nb_clients;
    // Regarder le nombre de clients (si plein ou non dans la team)
    return (false);
}