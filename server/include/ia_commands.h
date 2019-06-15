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
void update_time_cmd(sock_t *cli, unsigned int new);
void insert_cmd_ia(sock_t *cli, char **arg, zarg_t *zarg);
void init_player(ia_t *ia, sock_list_t *list, team_t *team, int id);
void disconnect_player(sock_t *cli, sock_list_t *list);

void cmd_ia_fork(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg);
void cmd_ia_forward(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg);
void cmd_ia_left(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg);
void cmd_ia_right(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg);
void cmd_ia_cnt_nbr(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg);

#endif
