/*
** EPITECH PROJECT, 2019
** const_dest_game.c
** File description:
** constuctor and destructor of a game
*/

#include "game.h"

void *initialize_teams(zarg_t *zarg)
{
    size_t i;
    team_t **teams;
    size_t nb_teams = array_lenght(zarg->team_names);

    teams = malloc(sizeof(team_t *));
    for (i = 0; i < nb_teams; i++) {
        teams[i] = malloc(sizeof(team_t));
        teams[i]->sock = NULL;
        teams[i]->nb_clients = zarg->clients_nb;
    }
    return (teams);
}

void *init_game(const sock_t *cli)
{
    game_t *data = malloc(sizeof(game_t));

    (void)cli;
    memset(data, 0, sizeof(game_t));
    // init_map(&core->map, w, h);
    return (data);
}

void delete_game(const sock_t *cli, void *data)
{
    (void)cli;
    (void)data;
    // destroy_array();
}