/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** incant
*/

#include "graph_commands.h"
#include "ia_commands.h"
#include "server.h"

void cmd_ia_incant(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    ia_t *ia = ZAPPY_CLIENT(cli)->client.ia;
    ia_t **ias = get_players_incantable(GET_GAME(list), ia, ia->level + 1);

    (void)zarg;
    (void)arg;
    if (ias == NULL) {
        dprintf(cli->fd, "ko\n");
        return;
    }
    printf("OUI\n");
    free(ias);
}
