/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** ia
*/

#include <criterion/criterion.h>
#include "graph_commands.h"
#include "ia_commands.h"
#include "unistd.h"

Test(ia, ia_egg)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *graph = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "20", "12", team, "1", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(graph->fd, "GRAPHIC\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cmd_ia_fork(list->start->next->socket, list, NULL, &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, IA);
    refresh_cmd(list, &zarg, 1000000);
    send_all_eggs(list->start->next->next->socket, list);
}

Test(ia, ia_egg_dead)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *graph = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "20", "12", team, "1", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(graph->fd, "GRAPHIC\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cmd_ia_fork(list->start->next->socket, list, NULL, &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, IA);
    refresh_cmd(list, &zarg, 1000000000);
    send_all_eggs(list->start->next->next->socket, list);
}

Test(ia, movemment)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    ia_move(list, ZAPPY_CLIENT(list->start->next->socket)->client.ia, NORTH);
    ia_move(list, ZAPPY_CLIENT(list->start->next->socket)->client.ia, SOUTH);
    ia_move(list, ZAPPY_CLIENT(list->start->next->socket)->client.ia, WEAST);
}

Test(ia, test_take)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    char *take[] = {"Take", "food", NULL};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->x = 0;
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->y = 0;
    GET_TILE(GET_GAME(list), 0, 0)->items[FOOD] = 1;
    cmd_ia_take(list->start->next->socket, list, take, &zarg);
}

Test(ia, test_take_no_food)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    char *take[] = {"Take", "food", NULL};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->x = 0;
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->y = 0;
    GET_TILE(GET_GAME(list), 0, 0)->items[FOOD] = 0;
    cmd_ia_take(list->start->next->socket, list, take, &zarg);
}

Test(ia, test_take_no_arg)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    char *take[] = {"Take", NULL};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cmd_ia_take(list->start->next->socket, list, take, &zarg);
}

Test(ia, test_take_invalid_arg)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    char *take[] = {"Take", "issou", NULL};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cmd_ia_take(list->start->next->socket, list, take, &zarg);
}

Test(ia, test_set_invalid)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    char *take[] = {"Set", "issou", NULL};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cmd_ia_set(list->start->next->socket, list, take, &zarg);
}

Test(ia, test_set_invalid_arg)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    char *take[] = {"Set", "food", NULL};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cmd_ia_set(list->start->next->socket, list, take, &zarg);
}

Test(ia, right)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cmd_ia_right(list->start->next->socket, list, NULL, &zarg);
}

Test(ia, left)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cmd_ia_left(list->start->next->socket, list, NULL, &zarg);
    cmd_ia_left(list->start->next->socket, list, NULL, &zarg);
    cmd_ia_left(list->start->next->socket, list, NULL, &zarg);
    cmd_ia_left(list->start->next->socket, list, NULL, &zarg);
}

Test(ia, inventory)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cmd_ia_inv(list->start->next->socket, list, NULL, &zarg);
}

Test(ia, connect_nbr)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cmd_ia_fork(list->start->next->socket, list, NULL, &zarg);
    GET_GAME(list)->teams[0]->eggs.lh_first->state = HATCHED;
    cmd_ia_cnt_nbr(list->start->next->socket, list, NULL, &zarg);
}

Test(ia, connect_nbr_egg)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cmd_ia_fork(list->start->next->socket, list, NULL, &zarg);
    cmd_ia_cnt_nbr(list->start->next->socket, list, NULL, &zarg);
}

Test(ia, broadcast_basic_invalid)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    char *broadcast[3] = {"Broadcast", NULL};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cmd_ia_broad(list->start->next->socket, list, broadcast, &zarg);
}

Test(ia, broadcast_basic)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *fat = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    char *broadcast[3] = {"Broadcast", "salut", NULL};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    sendto(fat->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cmd_ia_broad(list->start->next->socket, list, broadcast, &zarg);
}

Test(ia, broadcast_special_pos_x)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *fat = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    char *broadcast[3] = {"Broadcast", "salut", NULL};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    sendto(fat->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->x = 0;
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->y = 2;
    ZAPPY_CLIENT(list->start->next->next->socket)->client.ia->x = 2;
    ZAPPY_CLIENT(list->start->next->next->socket)->client.ia->y = 2;
    cmd_ia_broad(list->start->next->socket, list, broadcast, &zarg);
}

Test(ia, broadcast_special_pos_y)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *fat = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    char *broadcast[3] = {"Broadcast", "salut", NULL};
    arg_t arg = {"8080", "3", "7", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    sendto(fat->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->x = 2;
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->y = 0;
    ZAPPY_CLIENT(list->start->next->next->socket)->client.ia->x = 2;
    ZAPPY_CLIENT(list->start->next->next->socket)->client.ia->y = 2;
    cmd_ia_broad(list->start->next->socket, list, broadcast, &zarg);
}

Test(ia, broadcast_special_pos_alpha)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *fat = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    char *broadcast[3] = {"Broadcast", "salut", NULL};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    sendto(fat->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->x = 2;
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->y = 0;
    ZAPPY_CLIENT(list->start->next->next->socket)->client.ia->x = 2;
    ZAPPY_CLIENT(list->start->next->next->socket)->client.ia->y = 2;
    cmd_ia_broad(list->start->next->socket, list, broadcast, &zarg);
}

Test(cmd, update_time_invalid)
{
    sock_t cli = {0};
    ia_t ia = {0};
    zappy_client_t zpy = {0};

    STAILQ_INIT(&ia.list_head);
    cli.data = &zpy;
    zpy.client.ia = &ia;
    update_time_cmd(&cli, 5);
}

Test(cmd, update_time_valid)
{
    sock_t cli = {0};
    char *cmd[2] = {"Take", NULL};
    ia_t ia = {0};
    zappy_client_t zpy = {0};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", NULL, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    STAILQ_INIT(&ia.list_head);
    cli.data = &zpy;
    zpy.client.ia = &ia;
    insert_cmd_ia(&cli, cmd, &zarg);
    get_time_cmd(&cli);
    update_time_cmd(&cli, 5);
}

Test(cmd, exec_cmd_valid)
{
    sock_t cli = {0};
    ia_t ia = {0};
    zappy_client_t zpy = {0};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", NULL, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    STAILQ_INIT(&ia.list_head);
    cli.data = &zpy;
    zpy.client.ia = &ia;
    get_time_cmd(&cli);
    exec_ia_cmd(&cli, NULL, &zarg);
}

Test(cmd, insert_cmd_error)
{
    sock_t cli = {0};
    char **cmd = alloc_array(2, sizeof(char *));
    ia_t ia = {0};
    zappy_client_t zpy = {0};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", NULL, "2", "1"};

    cmd[0] = strdup("Invalid");
    cmd[1] = NULL;
    arg_to_zarg(&arg, &zarg);
    STAILQ_INIT(&ia.list_head);
    cli.data = &zpy;
    zpy.client.ia = &ia;
    insert_cmd_ia(&cli, cmd, &zarg);
}

Test(ia, look_basic)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *fat = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    char *broadcast[3] = {"Broadcast", "salut", NULL};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    sendto(fat->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cmd_ia_look(list->start->next->socket, list, broadcast, &zarg);
    cmd_ia_left(list->start->next->socket, list, broadcast, &zarg);
    cmd_ia_look(list->start->next->socket, list, broadcast, &zarg);
}

Test(ia, incantation_error)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *fat = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    char *broadcast[3] = {"Broadcast", "salut", NULL};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    sendto(fat->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cmd_ia_incant(list->start->next->socket, list, broadcast, &zarg);
}

Test(ia, incantation_level_one)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *fat = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    char *broadcast[3] = {"Broadcast", "salut", NULL};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    sendto(fat->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->x = 1;
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->y = 1;
    ZAPPY_CLIENT(list->start->next->next->socket)->client.ia->x = 1;
    ZAPPY_CLIENT(list->start->next->next->socket)->client.ia->y = 1;
    GET_GAME(list)->map.graph[1][1].items[LINEMATE] = 1;
    GET_GAME(list)->map.graph[1][1].items[THYSTAME] = 0;
    GET_GAME(list)->map.graph[1][1].items[PHIRAS] = 0;
    GET_GAME(list)->map.graph[1][1].items[DERAUMERE] = 0;
    GET_GAME(list)->map.graph[1][1].items[MENDIANE] = 0;
    GET_GAME(list)->map.graph[1][1].items[SIBUR] = 0;
    cmd_ia_incant(list->start->next->socket, list, broadcast, &zarg);
    GET_GAME(list)->incantations.lh_first->ia[0] = NULL;
    destroy_incantation(list, GET_GAME(list)->incantations.lh_first, true);
}

Test(ia, incantation_player_death)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *fat = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    char *broadcast[3] = {"Broadcast", "salut", NULL};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    sendto(fat->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->x = 1;
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->y = 1;
    ZAPPY_CLIENT(list->start->next->next->socket)->client.ia->x = 1;
    ZAPPY_CLIENT(list->start->next->next->socket)->client.ia->y = 1;
    GET_GAME(list)->map.graph[1][1].items[LINEMATE] = 1;
    GET_GAME(list)->map.graph[1][1].items[THYSTAME] = 0;
    GET_GAME(list)->map.graph[1][1].items[PHIRAS] = 0;
    GET_GAME(list)->map.graph[1][1].items[DERAUMERE] = 0;
    GET_GAME(list)->map.graph[1][1].items[MENDIANE] = 0;
    GET_GAME(list)->map.graph[1][1].items[SIBUR] = 0;
    cmd_ia_incant(list->start->next->socket, list, broadcast, &zarg);
    incantation_player_death(list, ZAPPY_CLIENT(list->start->next->socket)->client.ia);
    refresh_incantation(list, 10);
    refresh_incantation(list, 100000);
}

Test(ia, incantation_player_death_end)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *fat = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    char *broadcast[3] = {"Broadcast", "salut", NULL};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    sendto(fat->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->x = 1;
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->y = 1;
    ZAPPY_CLIENT(list->start->next->next->socket)->client.ia->x = 1;
    ZAPPY_CLIENT(list->start->next->next->socket)->client.ia->y = 1;
    GET_GAME(list)->map.graph[1][1].items[LINEMATE] = 1;
    GET_GAME(list)->map.graph[1][1].items[THYSTAME] = 0;
    GET_GAME(list)->map.graph[1][1].items[PHIRAS] = 0;
    GET_GAME(list)->map.graph[1][1].items[DERAUMERE] = 0;
    GET_GAME(list)->map.graph[1][1].items[MENDIANE] = 0;
    GET_GAME(list)->map.graph[1][1].items[SIBUR] = 0;
    cmd_ia_incant(list->start->next->socket, list, broadcast, &zarg);
    incantation_player_death(list, ZAPPY_CLIENT(list->start->next->socket)->client.ia);
    incantation_player_death(list, ZAPPY_CLIENT(list->start->next->next->socket)->client.ia);
}

Test(ia, player_eject)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *fat = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    char *broadcast[3] = {"Broadcast", "salut", NULL};
    arg_t arg = {"8080", "1", "1", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    sendto(fat->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cmd_ia_eject(list->start->next->socket, list, broadcast, &zarg);
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->ori = EAST;
    cmd_ia_eject(list->start->next->socket, list, broadcast, &zarg);
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->ori = SOUTH;
    cmd_ia_eject(list->start->next->socket, list, broadcast, &zarg);
}

Test(ia, player_eject_no_player)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    char *broadcast[3] = {"Broadcast", "salut", NULL};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cmd_ia_eject(list->start->next->socket, list, broadcast, &zarg);
}

Test(ia, player_eject_incantation)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *fat = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    char *broadcast[3] = {"Broadcast", "salut", NULL};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    sendto(fat->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->x = 1;
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->y = 1;
    ZAPPY_CLIENT(list->start->next->next->socket)->client.ia->x = 1;
    ZAPPY_CLIENT(list->start->next->next->socket)->client.ia->y = 1;
    GET_GAME(list)->map.graph[1][1].items[LINEMATE] = 1;
    GET_GAME(list)->map.graph[1][1].items[THYSTAME] = 0;
    GET_GAME(list)->map.graph[1][1].items[PHIRAS] = 0;
    GET_GAME(list)->map.graph[1][1].items[DERAUMERE] = 0;
    GET_GAME(list)->map.graph[1][1].items[MENDIANE] = 0;
    GET_GAME(list)->map.graph[1][1].items[SIBUR] = 0;
    cmd_ia_incant(list->start->next->socket, list, broadcast, &zarg);
    GET_GAME(list)->incantations.lh_first->nb_valid = 0;
    cmd_ia_eject(list->start->next->socket, list, broadcast, &zarg);
}
