/*
** EPITECH PROJECT, 2019
** const_dest_game.c
** File description:
** constuctor and destructor of a game
*/

#include "game.h"

static void destroy_map(map_t *map)
{
    for (size_t y = 0; y < map->h; y++)
        free(map->graph[y]);
    free(map->graph);
}

void initialize_game_args(game_t* game, zarg_t *zarg)
{
    size_t i;

    game->nb_teams = array_lenght(zarg->team_names);
    game->teams = malloc(sizeof(team_t *) * game->nb_teams);
    for (i = 0; i < game->nb_teams; i++) {
        game->teams[i] = malloc(sizeof(team_t));
        game->teams[i]->sock = NULL;
        game->teams[i]->nb_clients = 0;
        game->teams[i]->name = zarg->team_names[i];
        game->teams[i]->sock = malloc(sizeof(team_t *) * zarg->clients_nb);
        memset(game->teams[i]->sock, 0, sizeof(team_t *) * zarg->clients_nb);
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
    game_t *game = data;
    (void)cli;

    if (game->teams) {
        for (size_t i = 0; i < game->nb_teams; i++) {
            free(game->teams[i]->sock);
            free(game->teams[i]);
        }
        free(game->teams);
    }
    destroy_map(&game->map);
    free(data);
}
