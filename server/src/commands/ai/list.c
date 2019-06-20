/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** list
*/

#include "server.h"
#include "ia_commands.h"

static ai_cmd_t cmd_g[] = {
    {"Forward", 7, cmd_ia_forward},
    {"Right", 7, cmd_ia_right},
    {"Left", 7, cmd_ia_left},
    {"Look", 7, cmd_ia_look},
    {"Inventory", 1, cmd_ia_inv},
    {"Broadcast", 7, cmd_ia_broad},
    {"Connect_nbr", 0, cmd_ia_cnt_nbr},
    {"Fork", 42, cmd_ia_fork},
    {"Eject", 7, cmd_ia_eject},
    {"Take", 7, cmd_ia_take},
    {"Set", 7, cmd_ia_set},
    {"Incantation", 0, cmd_ia_incant}
};

static ai_cmd_t *check_ai_cmd(char **cmd)
{
    for (size_t i = 0; i < ARRAY_SIZE(cmd_g) && cmd[0]; i++)
        if (!strcmp(cmd_g[i].name, cmd[0]))
            return (&cmd_g[i]);
    return (NULL);
}

void insert_cmd_ia(sock_t *cli, char **arg, zarg_t *zarg)
{
    ai_cmd_t *tmp = check_ai_cmd(arg);

    if (tmp == NULL) {
        sock_write(cli, "ko\n");
        destroy_array(arg);
        return;
    }
    list_insert(LIST_CMD(cli), arg, tmp->time / zarg->freq);
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
    char **arg;

    if (cmd == NULL)
        return;
    for (size_t i = 0; i < ARRAY_SIZE(cmd_g); i++)
        if (!strcmp(cmd_g[i].name, cmd->cmd[0]) && cmd_g[i].func) {
            arg = list_pop(LIST_CMD(cli));
            cmd_g[i].func(cli, list, arg, zarg);
            destroy_array(arg);
            return;
        }
}

void update_time_cmd(sock_t *cli, unsigned int new)
{
    buffer_cmd_t *cmd = list_head(LIST_CMD(cli));

    if (cmd == NULL)
        return;
    cmd->time = new;
}
