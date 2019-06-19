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

Test(incantation, get_level)
{
    int res = inc_get_level(2, 0);

    cr_assert_eq(res, 1);
}

Test(incantation, test_incantation)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *fat = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    sock_t **res;
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "20", "12", team, "1", "1"};
    egg_t *egg = malloc(sizeof(egg_t));
    ia_t **incantables;

    memset(egg, 0, sizeof(egg_t));
    egg->state = HATCHED;
    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fat);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    res = socket_list_get_event(list);
    manage_event(list, res, &zarg);
    cmd_ia_fork(list->start->next->socket, list, NULL, &zarg);
    GET_GAME(list)->teams[0]->eggs.lh_first->state = HATCHED;
    sendto(fat->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    res = socket_list_get_event(list);
    manage_event(list, res, &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, IA);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->next->socket)->cli_type, IA);
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->inventory[LINEMATE] = 1;
    incantables = get_players_incantable(GET_GAME(list), ZAPPY_CLIENT(list->start->next->socket)->client.ia, 2);
    cr_assert_eq(incantables[0], ZAPPY_CLIENT(list->start->next->socket)->client.ia);
    cr_assert_eq(incantables[1], NULL);
}

Test(incantation, test_incantation_invalid_level)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *fat = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    sock_t **res;
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "20", "12", team, "1", "1"};
    egg_t *egg = malloc(sizeof(egg_t));
    ia_t **incantables;

    memset(egg, 0, sizeof(egg_t));
    egg->state = HATCHED;
    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fat);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    res = socket_list_get_event(list);
    manage_event(list, res, &zarg);
    cmd_ia_fork(list->start->next->socket, list, NULL, &zarg);
    GET_GAME(list)->teams[0]->eggs.lh_first->state = HATCHED;
    sendto(fat->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    res = socket_list_get_event(list);
    manage_event(list, res, &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, IA);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->next->socket)->cli_type, IA);
    incantables = get_players_incantable(GET_GAME(list), ZAPPY_CLIENT(list->start->next->socket)->client.ia, 0);
    cr_assert_eq(incantables, NULL);
}

Test(incantation, test_incantation_invalid_me_level)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *fat = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    sock_t **res;
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "20", "12", team, "1", "1"};
    egg_t *egg = malloc(sizeof(egg_t));
    ia_t **incantables;

    memset(egg, 0, sizeof(egg_t));
    egg->state = HATCHED;
    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fat);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    res = socket_list_get_event(list);
    manage_event(list, res, &zarg);
    cmd_ia_fork(list->start->next->socket, list, NULL, &zarg);
    GET_GAME(list)->teams[0]->eggs.lh_first->state = HATCHED;
    sendto(fat->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    res = socket_list_get_event(list);
    manage_event(list, res, &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, IA);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->next->socket)->cli_type, IA);
    incantables = get_players_incantable(GET_GAME(list), ZAPPY_CLIENT(list->start->next->socket)->client.ia, 3);
    cr_assert_eq(incantables, NULL);
}

Test(incantation, test_incantation_invalid_no_enought_player)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *fat = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    sock_t **res;
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "20", "12", team, "1", "1"};
    egg_t *egg = malloc(sizeof(egg_t));
    ia_t **incantables;

    memset(egg, 0, sizeof(egg_t));
    egg->state = HATCHED;
    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fat);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    res = socket_list_get_event(list);
    manage_event(list, res, &zarg);
    cmd_ia_fork(list->start->next->socket, list, NULL, &zarg);
    GET_GAME(list)->teams[0]->eggs.lh_first->state = HATCHED;
    sendto(fat->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    res = socket_list_get_event(list);
    manage_event(list, res, &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, IA);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->next->socket)->cli_type, IA);
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->level = 2;
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->inventory[1] = 1;
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->inventory[2] = 1;
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->inventory[3] = 1;
    incantables = get_players_incantable(GET_GAME(list), ZAPPY_CLIENT(list->start->next->socket)->client.ia, 3);
    cr_assert_eq(incantables, NULL);
}

Test(incantation, test_incantation_invalid_player_pos)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *fat = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};
    egg_t *egg = malloc(sizeof(egg_t));
    ia_t **incantables;

    memset(egg, 0, sizeof(egg_t));
    egg->state = HATCHED;
    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fat);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    sendto(fat->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, IA);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->next->socket)->cli_type, IA);
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->level = 2;
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->x = 0;
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->inventory[1] = 1;
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->inventory[2] = 1;
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->inventory[3] = 1;
    ZAPPY_CLIENT(list->start->next->next->socket)->client.ia->level = 2;
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->x = 1;
    ZAPPY_CLIENT(list->start->next->next->socket)->client.ia->inventory[1] = 1;
    ZAPPY_CLIENT(list->start->next->next->socket)->client.ia->inventory[2] = 1;
    ZAPPY_CLIENT(list->start->next->next->socket)->client.ia->inventory[3] = 1;
    incantables = get_players_incantable(GET_GAME(list), ZAPPY_CLIENT(list->start->next->socket)->client.ia, 3);
    cr_assert_eq(incantables, NULL);
}

Test(win, not_level_8)
{
    ia_t ia = {0};
    bool res;

    ia.level = 1;
    res = check_win_ia(NULL, &ia);
    cr_assert_eq(res, false);
}

Test(win, valid)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};
    egg_t *egg = malloc(sizeof(egg_t));
    bool res;

    memset(egg, 0, sizeof(egg_t));
    egg->state = HATCHED;
    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, IA);
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->level = 8;
    res = check_win_ia(list, ZAPPY_CLIENT(list->start->next->socket)->client.ia);
    cr_assert_eq(res, true);
}
