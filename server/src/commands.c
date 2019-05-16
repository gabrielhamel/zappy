/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** commands
*/

#include <sys/queue.h>
#include <stdbool.h>
#include "server.h"
#include "buffer_cmd.h"
#include "player.h"

bool init_zappy_cli(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    if (!strcasecmp("GRAPHIC", arg[0])) {
        ZAPPY_CLIENT(cli)->cli_type = GRAPHICAL;
        ZAPPY_CLIENT(cli)->client.graphic = malloc(sizeof(player_t));
        memset(ZAPPY_CLIENT(cli)->client.graphic, 0, sizeof(player_t));
    }
    else {
        ZAPPY_CLIENT(cli)->cli_type = IA;
        ZAPPY_CLIENT(cli)->client.ia = malloc(sizeof(ia_t));
        memset(ZAPPY_CLIENT(cli)->client.ia, 0, sizeof(ia_t));
        STAILQ_INIT(LIST_CMD(cli));
    }
    return (true);
}

void add_cmd_to_cli(sock_t *cli, char **arg)
{
    ai_cmd_t *cmd = get_ai_cmd(arg);

    if (cmd == NULL) {
        dprintf(cli->fd, "ko\n");
        destroy_array(arg);
        return;
    }
    list_insert(LIST_CMD(cli), arg);
    dprintf(cli->fd, "Time: %d\n", cmd->time);
}

void exec_command(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    if (ZAPPY_CLIENT(cli)->cli_type == UNDEFINED) {
        if (init_zappy_cli(cli, list, arg, zarg) == false)
            socket_list_remove(list, cli);
        destroy_array(arg);
    } else if (ZAPPY_CLIENT(cli)->cli_type == IA) {
        add_cmd_to_cli(cli, arg);
    } else {
        dprintf(cli->fd, "Graphicals commands is not available\n");
        destroy_array(arg);
    }
}