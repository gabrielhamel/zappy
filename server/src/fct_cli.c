/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** fct_cli
*/

#include "server.h"

void *init_client(const sock_t *cli)
{
    zappy_client_t *data = malloc(sizeof(zappy_client_t));

    memset(data, 0, sizeof(zappy_client_t));
    dprintf(cli->fd, "Bonjour client ! (a changer)\n");
    data->cmd_buff = strdup("");
    return (data);
}

void end_client(const sock_t *cli, void *data)
{
    if (data != NULL) {
        free(BUFF_CMD(cli));
        free(data);
    }
}