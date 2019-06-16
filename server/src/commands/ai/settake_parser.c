/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** settake_parser
*/

#include "graph_commands.h"
#include "server.h"

static int is_item(char *object_required)
{
    const char *array[] = {"food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};

    for (size_t i = 0; i < N_ITEMS; i++)
        if (!strcmp(array[i], object_required))
            return (i);
   return (-1); 
}

int cmd_ia_settake_parser(sock_t *cli, char **arg)
{
    int id_item;

    if (array_lenght(arg) < 2) {
        dprintf(cli->fd, "ko\n");
        return (-1);
    }
    id_item = is_item(arg[1]);
    if (id_item == -1) {
        dprintf(cli->fd, "ko\n");
    }
    return (id_item);
}
