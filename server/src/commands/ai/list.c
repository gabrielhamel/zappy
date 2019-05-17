/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** list
*/

#include "server.h"

static ai_cmd_t cmd_g[] = {
    {"Forward", 7, NULL},
    {"Right", 7, NULL},
    {"Left", 7, NULL},
    {"Look", 7, NULL},
    {"Inventory", 1, NULL},
    {"Broadcast", 7, NULL},
    {"Connect_nbr", 0, NULL},
    {"Fork", 42, NULL},
    {"Eject", 7, NULL},
    {"Take", 7, NULL},
    {"Set", 7, NULL},
    {"Incantation", 300, NULL}
};

static ai_cmd_t *check_ai_cmd(char **cmd)
{
    for (size_t i = 0; i < ARRAY_SIZE(cmd_g) && cmd[0]; i++)
        if (!strcasecmp(cmd_g[i].name, cmd[0]))
            return (&cmd_g[i]);
    return (NULL);
}

void insert_cmd_ia(sock_t *cli, char **arg)
{
    ai_cmd_t *tmp = check_ai_cmd(arg);

    if (tmp == NULL) {
        dprintf(cli->fd, "ko\n");
        destroy_array(arg);
        return;
    }
    list_insert(LIST_CMD(cli), arg, tmp->time);
}

int get_time_cmd(sock_t *cli)
{
    buffer_cmd_t *cmd = list_head(LIST_CMD(cli));

    if (cmd == NULL)
        return (-1);
    return (cmd->time);
}

void exec_ia_cmd(sock_t *cli, sock_list_t *list, zarg_t *zarg)
{
    buffer_cmd_t *cmd = list_head(LIST_CMD(cli));

    if (cmd == NULL)
        return;
    for (size_t i = 0; i < ARRAY_SIZE(cmd_g); i++)
        if (!strcasecmp(cmd_g[i].name, cmd->cmd[0]) && !cmd_g[i].func) {
            cmd_g[i].func(cli, list, cmd->cmd, zarg);
            list_pop(cmd);
            return;
        }
        else if (!strcasecmp(cmd_g[i].name, cmd->cmd[0]))
            dprintf(cli->fd, "Not implemented\n");
}

void update_time_cmd(sock_t *cli, unsigned int new)
{
    buffer_cmd_t *cmd = list_head(LIST_CMD(cli));

    if (cmd == NULL)
        return;
    cmd->time = new;
}