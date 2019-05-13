/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** commands
*/

#include "server.h"

command_t commands_g[] = {
    {"PING", command_ping}
};

static size_t commands_lenght(void)
{
    return (ARRAY_SIZE(commands_g));
}

void exec_command(sock_t *cli, sock_list_t *list, char **arg)
{
    for (size_t i = 0; i < commands_lenght() && arg[0]; i++) {
        if (!strcasecmp(commands_g[i].name, arg[0]) && commands_g[i].func) {
            commands_g[i].func(cli, list, arg);
            return;
        }
    }
    dprintf(cli->fd, "Commande invalide (a changer)\n");
}