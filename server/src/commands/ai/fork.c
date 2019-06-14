/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Fork
*/

#include "graph_commands.h"
#include "server.h"

void send_all_eggs(sock_t *graph, sock_list_t *list)
{
    game_t *game = GET_GAME(list);
    team_t *team;
    egg_t *egg;

    for (size_t i = 0; i < game->nb_teams; i++) {
        team = game->teams[i];
        LIST_FOREACH(egg, &team->eggs, next)
            dprintf(graph->fd, "enw %d %d %ld %ld\n", egg->id, egg->player, egg->x, egg->y);
    }
}

void cmd_ia_fork(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    static int id = 0;
    char buff[4096] = {0};
    egg_t *egg = malloc(sizeof(egg_t));
    ia_t *ia = ZAPPY_CLIENT(cli)->client.ia;
    team_t *team = ia->team;

    (void)arg;
    memset(egg, 0, sizeof(egg_t));
    egg->id = id++;
    egg->player = cli->fd;
    egg->state = HATCHING;
    egg->x = ia->x;
    egg->y = ia->y;
    egg->time = 600.f / zarg->freq; 
    LIST_INSERT_HEAD(&team->eggs, egg, next);
    sprintf(buff, "enw %d %d %ld %ld\n", egg->id, cli->fd, egg->x, egg->y);
    send_all_graphics(list, buff);
    dprintf(cli->fd, "ok\n");
}
