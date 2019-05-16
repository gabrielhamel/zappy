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

static size_t commands_lenght(void)
{
    return (ARRAY_SIZE(cmd_g));
}

ai_cmd_t *get_ai_cmd(char **cmd)
{
    for (size_t i = 0; i < commands_lenght() && cmd[0]; i++)
        if (!strcasecmp(cmd_g[i].name, cmd[0]))
            return (&cmd_g[i]);
    return (NULL);
}