/*
** EPITECH PROJECT, 2019
** check_team_names.c
** File description:
** checking the team names
*/

#include "game.h"
#include "buffer_cmd.h"

bool check_team_names(char **arg, game_t *game, sock_t *cli, zarg_t *zarg)
{
    size_t i;
    int nb_ia;
    team_t *team;

    for (i = 0; i < game->nb_teams; i++)
        if (!strcmp(arg[0], game->teams[i]->name))
            break;
    if (i == game->nb_teams)
        return false;
    team = game->teams[i];
    nb_ia = team->nb_clients;
    if ((unsigned int)nb_ia == zarg->clients_nb)
        return false;
    for (i = 0; team->sock[i] != NULL; i++)
        i++;
    team->sock[i] = cli;
    team->nb_clients++;
    printf("New IA %d\n", cli->fd);
    return true;
}
