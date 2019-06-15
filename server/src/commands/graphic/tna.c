/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** tna
*/

#include "graph_commands.h"
#include "game.h"

void cmd_tna_all_team(sock_t *cli, zarg_t *zarg)
{
    for (size_t i = 0; zarg->team_names[i] != NULL; i++)
        dprintf(cli->fd, "tna %s\n", zarg->team_names[i]);
}

void cmd_graph_tna(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    game_t *game = GET_GAME(list);

    (void)arg;
    (void)zarg;

    for (size_t i = 0; game->teams[i]; i++)
        dprintf(cli->fd, "tna %s\n", game->teams[i]->name);
}
