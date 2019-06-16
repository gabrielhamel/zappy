/*
** EPITECH PROJECT, 2019
** game.h
** File description:
** game header
*/

#pragma once

#include <sys/queue.h>
#include "server.h"
#include "parser.h"
#include "map.h"

#define GET_GAME(x) ((game_t *)(x->start->socket->data))

typedef enum {
    HATCHING,
    HATCHED,
    DEAD,
} egg_state_t;

typedef struct egg_s {
    LIST_ENTRY(egg_s) next;
    int id;
    int player;
    size_t x;
    size_t y;
    float time;
    egg_state_t state;
} egg_t;

typedef struct incantation_s {
    LIST_ENTRY(incantation_s) next;
    struct ia_s **ia;
    size_t nb_ia;
    tile_t *tile;
    float time;
} incantation_t;

typedef struct team_t {
    LIST_HEAD(, egg_s) eggs;
    sock_t **sock;
    size_t nb_clients;
    char *name;
} team_t;

typedef struct s_game {
    team_t **teams;
    size_t nb_teams;
    map_t map;
    LIST_HEAD(, incantation_s) incantations;
} game_t;

// Constructeur et destructeur du game
void *init_game(const sock_t *cli);
void delete_game(const sock_t *cli, void *data);
void initialize_game_args(game_t *game, zarg_t *zarg);
bool check_team_names(char **arg, game_t *game, sock_t *cli, zarg_t *zarg);
egg_t *available_egg(team_t *team);
