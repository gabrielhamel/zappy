/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** commands
*/

#include <sys/queue.h>
#include <stdbool.h>
#include <stdio.h>
#include "ia_commands.h"
#include "graph_commands.h"
#include "game.h"
#include "buffer_cmd.h"
#include "graphic.h"

static void send_graphics_informations(sock_t *cli, sock_list_t *list,
zarg_t *zarg)
{
    cmd_graph_msz(cli, list, NULL, zarg);
    cmd_send_sgt(cli, zarg);
    cmd_graph_bct_all(cli, list);
    cmd_tna_all_team(cli, zarg);
    send_all_players(cli, list);
    send_all_eggs(cli, list);
}

egg_t *available_egg(team_t *team)
{
    egg_t *egg;

    LIST_FOREACH(egg, &team->eggs, next) {
        if (egg->state == HATCHED) {
            LIST_REMOVE(egg, next);
            return egg;
        }
    }
    return NULL;
}

static void new_player_connection(sock_t *cli, char *team,
zarg_t *zarg, sock_list_t *list)
{
    game_t *game = GET_GAME(list);
    ia_t *ia = ZAPPY_CLIENT(cli)->client.ia;
    char buff[4096] = {0};
    size_t i = 0;

    for (; strcmp(game->teams[i]->name, team); i++);
    init_player(ia, list, game->teams[i], cli->fd);
    dprintf(cli->fd, "%ld\n%d %d\n",
    zarg->clients_nb - ia->team->nb_clients, zarg->width, zarg->height);
    sprintf(buff, "pnw %d %ld %ld %d %d %s\n",
    ia->id, ia->x, ia->y, ia->ori, ia->level, team);
    send_all_graphics(list, buff);
}

static bool init_zappy_cli(sock_t *cli, sock_list_t *list,
char **arg, zarg_t *zarg)
{
    (void)zarg;
    (void)list;
    if (arg[0] && !strcmp("GRAPHIC", arg[0])) {
        ZAPPY_CLIENT(cli)->cli_type = GRAPHICAL;
        ZAPPY_CLIENT(cli)->client.graphic = malloc(sizeof(graphic_t));
        memset(ZAPPY_CLIENT(cli)->client.graphic, 0, sizeof(graphic_t));
        send_graphics_informations(cli, list, zarg);
        return (true);
    }
    else if (arg[0] && strcmp("GRAPHIC", arg[0]) && check_team_names(arg,
        GET_GAME(list), cli, zarg)) {
        ZAPPY_CLIENT(cli)->cli_type = IA;
        ZAPPY_CLIENT(cli)->client.ia = malloc(sizeof(ia_t));
        memset(ZAPPY_CLIENT(cli)->client.ia, 0, sizeof(ia_t));
        STAILQ_INIT(LIST_CMD(cli));
        new_player_connection(cli, arg[0], zarg, list);
        return (true);
    }
    return (false);
}

void exec_command(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    if (ZAPPY_CLIENT(cli)->cli_type == UNDEFINED) {
        if (init_zappy_cli(cli, list, arg, zarg) == false)
            dprintf(cli->fd, "ko\n");
        destroy_array(arg);
    }
    else if (ZAPPY_CLIENT(cli)->cli_type == IA)
        insert_cmd_ia(cli, arg, zarg);
    else {
        exec_graph_cmd(cli, list, arg, zarg);
        destroy_array(arg);
    }
}
