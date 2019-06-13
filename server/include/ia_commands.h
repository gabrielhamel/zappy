/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** ia_commands
*/

#ifndef IA_COMMANDS_H
#define IA_COMMANDS_H

#include "server.h"

void exec_ia_cmd(sock_t *cli, sock_list_t *list, zarg_t *zarg);
int get_time_cmd(sock_t *cli);
void update_time_cmd(sock_t *cli, int new);
void insert_cmd_ia(sock_t *cli, char **arg, zarg_t *zarg);
void disconnect_player(sock_t *cli, sock_list_t *list);

#endif
