/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** map
*/

#include <criterion/criterion.h>
#include <unistd.h>
#include "parser.h"
#include "ia_commands.h"
#include "server.h"

Test(map, destroy_map)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    sock_t **res;
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "20", "12", team, "1", "1"};
    egg_t *egg = malloc(sizeof(egg_t));

    memset(egg, 0, sizeof(egg_t));
    egg->state = HATCHED;
    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    res = socket_list_get_event(list);
    manage_event(list, res, &zarg);
    cmd_ia_fork(list->start->next->socket, list, NULL, &zarg);
    GET_GAME(list)->teams[0]->eggs.lh_first->state = HATCHED;
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, IA);
    delete_game(list->start->socket, list->start->socket->data);
}
