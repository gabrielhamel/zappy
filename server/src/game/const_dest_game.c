/*
** EPITECH PROJECT, 2019
** const_dest_game.c
** File description:
** constuctor and destructor of a game
*/

#include "game.h"

void initialize_game_args(game_t* game, zarg_t *zarg)
{
    size_t i;

    game->nb_teams = array_lenght(zarg->team_names);
    game->teams = malloc(sizeof(team_t *) * game->nb_teams);
    for (i = 0; i < game->nb_teams; i++) {
        game->teams[i] = malloc(sizeof(team_t));
        game->teams[i]->sock = NULL;
        game->teams[i]->nb_clients = zarg->clients_nb;
    }
    init_map(&game->map, zarg->width, zarg->height);
}

void *init_game(const sock_t *cli)
{
    game_t *data = malloc(sizeof(game_t));

    (void)cli;
    memset(data, 0, sizeof(game_t));
    return (data);
}

void delete_game(const sock_t *cli, void *data)
{
    (void)cli;
    (void)data;
    // destroy_array();
}
