/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** commands
*/

#include <sys/queue.h>
#include <stdbool.h>
#include "ia_commands.h"
#include "graph_commands.h"
#include "game.h"
#include "buffer_cmd.h"
#include "player.h"

static bool init_zappy_cli(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    (void)zarg;
    (void)list;
    if (!strcasecmp("GRAPHIC", arg[0])) {
        ZAPPY_CLIENT(cli)->cli_type = GRAPHICAL;
        ZAPPY_CLIENT(cli)->client.graphic = malloc(sizeof(player_t));
        memset(ZAPPY_CLIENT(cli)->client.graphic, 0, sizeof(player_t));
        return (true);
    }
    else if (strcasecmp("GRAPHIC", arg[0]) && check_team_names(arg, zarg, cli)) {
        ZAPPY_CLIENT(cli)->cli_type = IA;
        ZAPPY_CLIENT(cli)->client.ia = malloc(sizeof(ia_t));
        memset(ZAPPY_CLIENT(cli)->client.ia, 0, sizeof(ia_t));
        STAILQ_INIT(LIST_CMD(cli));
        return (true);
    }
    return (false);
}

void exec_command(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    if (ZAPPY_CLIENT(cli)->cli_type == UNDEFINED) {
        if (init_zappy_cli(cli, list, arg, zarg) == false)
            socket_list_remove(list, cli);
        destroy_array(arg);
    } else if (ZAPPY_CLIENT(cli)->cli_type == IA) {
        insert_cmd_ia(cli, arg);
    } else {
        exec_graph_cmd(cli, list, arg, zarg);
        destroy_array(arg);
    }
}