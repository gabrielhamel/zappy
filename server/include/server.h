/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** server
*/

#pragma once

#include "socket.h"
#include "utils.h"
#include "buffer_cmd.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define REFRESH_USEC 10000

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*x))
#define BUFF_CMD(x) ((zappy_client_t *)x->data)->cmd_buff

typedef enum {
    IA,
    GRAPHICAL,
    UNDEFINED
} client_type_t;

typedef struct {
    const char *name;
    void (*func)(sock_t *, sock_list_t *, char **);
} command_t;

typedef struct {
    char *cmd_buff;
    client_type_t cli_type;
    un_cli_t client;
} zappy_client_t;

extern command_t commands_g[];

// Constructeur et destructeur du client
void *init_client(const sock_t *cli);
void end_client(const sock_t *cli, void *data);

// Section parsing

typedef struct {
    char *port;
    char *width;
    char *height;
    char **team_names;
    char *clients_nb;
    char *freq;
} arg_t;

typedef struct {
    uint16_t port;
    unsigned int width;
    unsigned int height;
    char **team_names;
    unsigned int clients_nb;
    float freq;
} zarg_t;

typedef struct {
    char *flag;
    bool infinity;
    size_t offset;
    bool (*check)(const char *);
} argument_t;

bool parsing(arg_t *arg, int ac, char **av);
void *parse_single_arg(int ac, char **av, argument_t *flag, int *i);
void *parse_infinity_arg(int ac, char **av, argument_t *flag, int *i);
int count_nb_arg(int ac, char **av, int i);
void arg_to_zarg(arg_t *arg, zarg_t *zarg);
bool check_port(const char *port);
bool check_dimension(const char *dim);
bool check_clients_nb(const char *nb);
bool check_freq(const char *freq);
bool check_team(const char *team);

// Fonctions socket
int launch_zappy(zarg_t *zarg);
void manage_event(sock_list_t *list, sock_t **evt_socks, zarg_t *zarg);
char *read_line(sock_t *socket);
void exec_command(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg);

// Section des commandes de client
void refresh_cmd(sock_list_t *list, zarg_t *zarg, long int ellapsed);

// Commandes des IA

typedef struct {
    const char *name;
    float time;
    void (*func)(sock_t *, sock_list_t *, char **, zarg_t *);
} ai_cmd_t;

// Commandes graphics

typedef struct {
    const char *name;
    void (*func)(sock_t *, sock_list_t *, char **, zarg_t *);
} graph_cmd_t;