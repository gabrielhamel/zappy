/*
** EPITECH PROJECT, 2019
** game.h
** File description:
** game header
*/

#pragma once

#include "server.h"
#include "parser.h"
#include "map.h"

#define GET_GAME(x) ((game_t *)(x->start->socket->data))

typedef struct team_t {
    sock_t **sock;
    size_t nb_clients;
    char *name;
} team_t;

typedef struct s_game {
    team_t **teams;
    size_t nb_teams;
    map_t map;
} game_t;

// Constructeur et destructeur du game
void *init_game(const sock_t *cli);
void delete_game(const sock_t *cli, void *data);
void initialize_game_args(game_t* game, zarg_t *zarg);
bool check_team_names(char **arg, game_t *game, sock_t *cli, zarg_t *zarg);
