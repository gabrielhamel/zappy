/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** parser
*/

#pragma once

#include "socket.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*x))
#define BUFF_CMD(x) ((zappy_client_t *)x->data)->cmd_buff

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
bool check_port(const char *port);
bool check_dimension(const char *dim);
bool check_clients_nb(const char *nb);
bool check_freq(const char *freq);
bool check_team(const char *dim);
