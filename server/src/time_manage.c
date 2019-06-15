/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** time_manage
*/

#include "ia_commands.h"
#include "graph_commands.h"
#include "server.h"

static buffer_cmd_t *get_head(sock_t *sock)
{
    zappy_client_t *cli;

    if (sock == NULL)
        return (NULL);
    if (sock->type != CLIENT)
        return (NULL);
    cli = sock->data;
    if (cli->cli_type != IA)
        return (NULL);
    return (list_head(LIST_CMD(sock)));
}

static void refresh_egg(egg_t *egg, sock_list_t *list, zarg_t *zarg)
{
    char buff[4096] = {0};

    if (egg->time > 0)
        return;
    if (egg->time <= (-10000.f / zarg->freq)) {
        egg->state = DEAD;
        sprintf(buff, "edi %d\n", egg->id);
        send_all_graphics(list, buff);
        return;
    }
    if (egg->state == HATCHED)
        return;
    egg->state = HATCHED;
    sprintf(buff, "eth %d\n", egg->id);
    send_all_graphics(list, buff);
}

static void refresh_eggs(sock_list_t *list, float ellapsed, zarg_t *zarg)
{
    game_t *game = GET_GAME(list);
    team_t *team;
    egg_t *egg;

    for (size_t i = 0; i < game->nb_teams; i++) {
        team = game->teams[i];
        LIST_FOREACH(egg, &team->eggs, next) {
            if (egg->state == DEAD)
                continue;
            egg->time -= ellapsed;
            refresh_egg(egg, list, zarg);
        }
    }
}

void refresh_cmd(sock_list_t *list, zarg_t *zarg, long int ellapsed)
{
    buffer_cmd_t *tmp;
    sock_node_t *i = list->start;
    sock_node_t *next;

    while (i) {
        refresh_eggs(list, (float)ellapsed / 1000.f, zarg);
        tmp = get_head(i->socket);
        if (tmp == NULL) {
            i = i->next;
            continue;
        }
        next = i->next;
        tmp->time -= (float)ellapsed / 1000.f;
        if (tmp->time <= 0)
            exec_ia_cmd(i->socket, list, zarg);
        i = next;
    }
}
