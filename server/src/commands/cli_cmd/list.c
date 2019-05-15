/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** list
*/

#include "server.h"

static const ai_cmd_t cmd_g[] = {
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

void exec_ia_cmd(sock_t *sock, sock_list_t *list, char **arg, zarg_t *zarg)
{
    for (size_t i = 0; i < commands_lenght() && arg[0]; i++) {
        if (!strcasecmp(commands_g[i].name, arg[0]) && commands_g[i].func) {
            cmd_g[i].func(sock, list, arg, zarg);
            return;
        }
    }
    dprintf(sock->fd, "Commande ia invalide (a changer)\n");
}