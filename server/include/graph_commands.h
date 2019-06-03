/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** graph_commands
*/

#ifndef GRAPH_COMMANDS_H
#define GRAPH_COMMANDS_H

#include "server.h"

void exec_graph_cmd(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg);

// Liste des commandes graphiques
void cmd_graph_msz(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg);

#endif