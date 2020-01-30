/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** refresh
*/

#include <criterion/criterion.h>
#include <unistd.h>
#include "parser.h"
#include "server.h"
#include "ia_commands.h"

Test(refresh, refresh_all_cmd)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *ai = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_not_null(ai);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(ai->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "GRAPHIC\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "sgt\n", 4 , 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, GRAPHICAL);
    refresh_cmd(list, &zarg, 0);
}

Test(refresh, refresh_all_egg)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "20", "12", team, "1", "1"};
    egg_t *egg = malloc(sizeof(egg_t));

    memset(egg, 0, sizeof(egg_t));
    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cmd_ia_fork(list->start->next->socket, list, NULL, &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, IA);
    refresh_cmd(list, &zarg, 0);
}

Test(refresh, refresh_all_egg_hatched)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
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
    cmd_ia_fork(list->start->next->socket, list, NULL, &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, IA);
    refresh_cmd(list, &zarg, 1000000);
}

Test(refresh, refresh_all_egg_dead)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
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
    cmd_ia_fork(list->start->next->socket, list, NULL, &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, IA);
    refresh_cmd(list, &zarg, 100000000);
}

Test(refresh, refresh_win)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
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
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, IA);
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->level = 8;
    refresh_cmd(list, &zarg, 1000);
}

Test(refresh, refresh_allready_hatched)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
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
    cmd_ia_fork(list->start->next->socket, list, NULL, &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, IA);
    refresh_cmd(list, &zarg, 1000000);
    refresh_cmd(list, &zarg, 1);
}

Test(refresh, refresh_allready_dead)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
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
    cmd_ia_fork(list->start->next->socket, list, NULL, &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, IA);
    refresh_cmd(list, &zarg, 100000000);
    refresh_cmd(list, &zarg, 1);
}

Test(refresh, refresh_cmd)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
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
    sendto(fake->fd, "Forward\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, IA);
    refresh_cmd(list, &zarg, 1);
}

Test(refresh, refresh_cmd_exec)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
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
    sendto(fake->fd, "Forward\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, IA);
    refresh_cmd(list, &zarg, 9000);
}

Test(refresh, refresh_player_dead)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
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
    sendto(fake->fd, "Forward\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, IA);
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->live = 0;
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->inventory[0] = 0;
    refresh_cmd(list, &zarg, 9);
}

Test(refresh, refresh_player_buff_end)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
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
    sendto(fake->fd, "Forward\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, IA);
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->live = 0;
    ZAPPY_CLIENT(list->start->next->socket)->client.ia->inventory[0] = 0;
    list_elem_destroy(ZAPPY_CLIENT(list->start->next->socket)->client.ia->list_head.stqh_first);
}

Test(refresh, refresh_player_buff_pop_null)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
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
    sendto(fake->fd, "Forward\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, IA);
    list_pop(ZAPPY_CLIENT(list->start->next->socket)->client.ia->list_head.stqh_first);
    list_pop(ZAPPY_CLIENT(list->start->next->socket)->client.ia->list_head.stqh_first);
}
