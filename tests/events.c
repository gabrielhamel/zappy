/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** events
*/

#include <criterion/criterion.h>
#include <unistd.h>
#include "parser.h"
#include "ia_commands.h"
#include "server.h"

Test(events, new_cli)
{
    sock_t *serv = socket_serv_init(0, NULL, NULL);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();

    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), NULL);
    cr_assert_neq(list->start->next, NULL);
}

Test(events, cli_disconnect)
{
    sock_t *serv = socket_serv_init(0, NULL, NULL);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    sock_t **res;

    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), NULL);
    cr_assert_neq(list->start->next, NULL);
    sendto(fake->fd, "", 1, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    res = socket_list_get_event(list);
    manage_event(list, res, NULL);
}

Test(events, cli_ia_connexion)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    sock_t **res;
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "20", "12", team, "2", "100"};

    arg_to_zarg(&arg, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_neq(list->start->next, NULL);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    res = socket_list_get_event(list);
    manage_event(list, res, &zarg);
}

Test(events, cli_ia_disconnexion)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    sock_t **res;
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "20", "12", team, "2", "100"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_neq(list->start->next, NULL);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    res = socket_list_get_event(list);
    manage_event(list, res, &zarg);
    close(fake->fd);
    res = socket_list_get_event(list);
    cr_assert_neq(res, NULL);
}

Test(events, cli_ia_empty_cmd)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    sock_t **res;
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "20", "12", team, "2", "100"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_neq(list->start->next, NULL);
    sendto(fake->fd, "\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    res = socket_list_get_event(list);
    manage_event(list, res, &zarg);
}

Test(events, cli_ia_no_place)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *fat = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    sock_t **res;
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "20", "12", team, "1", "100"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fat);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    sendto(fat->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    res = socket_list_get_event(list);
    manage_event(list, res, &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, IA);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->next->socket)->cli_type, UNDEFINED);
}

Test(events, cli_ia_egg)
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
}

Test(events, cli_ia_egg_not_ready)
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
    sendto(fat->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    res = socket_list_get_event(list);
    manage_event(list, res, &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, IA);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->next->socket)->cli_type, UNDEFINED);
}
