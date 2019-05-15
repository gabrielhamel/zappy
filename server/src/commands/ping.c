/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** ping
*/

#include "server.h"

void command_ping(sock_t *cli, sock_list_t *list, char **arg)
{
    (void)list;
    (void)arg;
    dprintf(cli->fd, "pong\n");
}
