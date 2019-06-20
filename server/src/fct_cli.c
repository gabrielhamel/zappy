/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** fct_cli
*/

#include "server.h"
#include "game.h"
#include "graph_commands.h"

void disconnect_player(sock_t *cli, sock_list_t *list)
{
    ia_t *ia = ZAPPY_CLIENT(cli)->client.ia;
    size_t i = 0;
    char buffer[4096] = {0};

    for (; ia->team->sock[i] != cli; i++);
    incantation_player_death(list, ia);
    ia->team->sock[i] = NULL;
    ia->team->nb_clients--;
    sprintf(buffer, "pdi %d\n", ia->id);
    send_all_graphics(list, buffer);
}

void *init_client(const sock_t *cli)
{
    zappy_client_t *data = malloc(sizeof(zappy_client_t));

    memset(data, 0, sizeof(zappy_client_t));
    sock_write(cli, "WELCOME\n");
    data->cmd_buff = strdup("");
    data->cli_type = UNDEFINED;
    return (data);
}

void end_client(const sock_t *cli, void *data)
{
    STAILQ_HEAD(, buffer_cmd_s) *list = (void *)LIST_CMD(cli);
    zappy_client_t *zcli = data;
    buffer_cmd_t *tmp;
    buffer_cmd_t *tmp2;
    client_type_t type = zcli->cli_type;

    if (type == IA) {
        tmp = list->stqh_first;
        while (tmp != NULL) {
            destroy_array(tmp->cmd);
            tmp2 = tmp;
            tmp = tmp->next.stqe_next;
            free(tmp2);
        }
        free(ZAPPY_CLIENT(cli)->client.ia);
    } else if (type == GRAPHICAL)
        free(ZAPPY_CLIENT(cli)->client.graphic);
    free(BUFF_CMD(cli));
    free(data);
}

static void init_some_var(ia_t *ia)
{
    ia->inventory[FOOD] = 9;
    ia->inventory[LINEMATE] = 0;
    ia->inventory[DERAUMERE] = 0;
    ia->inventory[SIBUR] = 0;
    ia->inventory[MENDIANE] = 0;
    ia->inventory[PHIRAS] = 0;
    ia->inventory[THYSTAME] = 0;
    ia->fixed = false;
}

void init_player(ia_t *ia, sock_list_t *list, team_t *team, int id)
{
    char buff[4096] = {0};
    game_t *game = GET_GAME(list);
    egg_t *egg;

    ia->team = team;
    ia->ori = rand() % 4 + 1;
    ia->level = 1;
    ia->id = id;
    egg = available_egg(ia->team);
    if (egg == NULL) {
        ia->x = rand() % game->map.w;
        ia->y = rand() % game->map.h;
    }
    else {
        ia->x = egg->x;
        ia->y = egg->y;
        sprintf(buff, "ebo %d\n", egg->id);
        send_all_graphics(list, buff);
        free(egg);
    }
    init_some_var(ia);
}
