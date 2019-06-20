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
    game_t *game = GET_GAME(list);
    ia_t *ia;

    cmd_graph_msz(cli, list, NULL, zarg);
    cmd_send_sgt(cli, zarg);
    cmd_graph_bct_all(cli, list);
    cmd_tna_all_team(cli, zarg);
    send_all_players(cli, list);
    send_all_eggs(cli, list);
    for (size_t i = 0; i < game->nb_teams; i++)
        for (size_t j = 0; j < game->teams[i]->nb_clients; j++) {
            ia = ZAPPY_CLIENT(game->teams[i]->sock[j])->client.ia;
            graph_send_ia_pin(list, ia);
        }
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
    int nb_remaining;

    add_random_food(list, &game->map);
    for (; strcmp(game->teams[i]->name, team); i++);
    init_player(ia, list, game->teams[i], cli->fd);
    ia->live = 126.f / zarg->freq;
    nb_remaining = zarg->clients_nb - ia->team->nb_clients +
    get_nb_hatcheg_egg(ia->team);
    nb_remaining = nb_remaining < 0 ? 0 : nb_remaining;
    sock_write(cli, "%d\n%d %d\n",
    nb_remaining, zarg->width, zarg->height);
    sprintf(buff, "pnw %d %ld %ld %d %d %s\n",
    ia->id, ia->x, ia->y, ia->ori, ia->level, team);
    send_all_graphics(list, buff);
    graph_send_ia_pin(list, ia);
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
    char buff[4096] = {0};

    if (ZAPPY_CLIENT(cli)->cli_type == UNDEFINED) {
        if (init_zappy_cli(cli, list, arg, zarg) == false)
            sock_write(cli, "ko\n");
        destroy_array(arg);
    }
    else if (ZAPPY_CLIENT(cli)->cli_type == IA) {
        if (arg[0] && !strcmp(arg[0], "Fork")) {
            sprintf(buff, "pfk %d\n", cli->fd);
            send_all_graphics(list, buff);
        }
        insert_cmd_ia(cli, arg, zarg);
    }
    else {
        exec_graph_cmd(cli, list, arg, zarg);
        destroy_array(arg);
    }
}
