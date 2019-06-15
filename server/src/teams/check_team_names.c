/*
** EPITECH PROJECT, 2019
** check_team_names.c
** File description:
** checking the team names
*/

#include "game.h"
#include "buffer_cmd.h"

static bool have_available_egg(team_t *team)
{
    egg_t *egg;

    LIST_FOREACH(egg, &team->eggs, next)
        if (egg->state == HATCHED)
            return true;
    return false;
}

static void increase_team_size(team_t *team)
{
    team->sock = realloc(team->sock, sizeof(sock_t *) * (team->nb_clients + 1));
    team->sock[team->nb_clients] = NULL;
}

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
    if (!have_available_egg(team) && (unsigned int)nb_ia >= zarg->clients_nb)
        return false;
    if ((unsigned int)nb_ia >= zarg->clients_nb)
        increase_team_size(team);
    for (i = 0; team->sock[i] != NULL; i++);
    team->sock[i] = cli;
    team->nb_clients++;
    return true;
}
