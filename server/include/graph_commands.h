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

ia_t *get_player_by_id(int id, sock_list_t *list);

// Liste des commandes graphiques
void cmd_graph_msz(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg);
void cmd_graph_bct(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg);
void cmd_graph_mct(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg);
void cmd_graph_tna(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg);
void cmd_graph_ppo(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg);
void cmd_graph_plv(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg);
void cmd_graph_pin(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg);
void cmd_graph_sgt(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg);
void cmd_graph_sst(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg);
void cmd_graph_pin(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg);

// Commande passives
void cmd_graph_bct_all(sock_t *cli, sock_list_t *list);
void cmd_send_sgt(sock_t *cli, zarg_t *zarg);
void cmd_tna_all_team(sock_t *cli, zarg_t *zarg);
void send_all_graphics(sock_list_t *list, const char *s);
void send_all_players(sock_t *graph, sock_list_t *list);
void send_all_eggs(sock_t *graph, sock_list_t *list);

// Commande envoyés indirectement
void graph_send_ia_ppo(sock_list_t *list, ia_t *ia);
void graph_send_ia_plv(sock_list_t *list, ia_t *ia);
void graph_send_ia_pin(sock_list_t *list, ia_t *ia);
void graph_send_tile_bct(sock_list_t *list, tile_t *tile);

int cmd_ia_settake_parser(sock_t *cli, char **arg);

#endif
