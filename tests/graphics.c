/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** graphics
*/

#include <criterion/criterion.h>
#include "graph_commands.h"
#include "unistd.h"

Test(graphics, tna)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    char buff[4096] = {0};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "GRAPHIC\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "tna\n", 4, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, GRAPHICAL);
    read(fake->fd, buff, 4096);
    cmd_graph_tna(list->start->next->socket, list, NULL, &zarg);
    memset(buff, 0, 4096);
    read(fake->fd, buff, 4096);
    cr_assert_str_eq(buff, "tna team1\ntna team2\ntna team1\ntna team2\n");
}

Test(graphics, send_all_graphic)
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
    list->start->socket->data = NULL;
    list->start->next->socket->data = NULL;
    send_all_graphics(list, "salut\n");
}

Test(graphics, send_all_player)
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
    list->start->socket->data = NULL;
    list->start->next->socket->data = NULL;
    send_all_players(list->start->socket, list);
}

Test(graphics, sst)
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
    sendto(fake->fd, "GRAPHIC\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "sst 22\n", 7, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, GRAPHICAL);
    cr_assert_eq(zarg.freq, 22);
}

Test(graphics, sst_invalid_arg)
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
    sendto(fake->fd, "GRAPHIC\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "sst\n", 4, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, GRAPHICAL);
}

Test(graphics, sst_invalid_arg2)
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
    sendto(fake->fd, "GRAPHIC\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "sst 0\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, GRAPHICAL);
}

Test(graphics, ppo)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    char buff[4096] = {0};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "GRAPHIC\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sprintf(buff, "ppo %d\n", list->start->next->socket->fd);
    sendto(fake->fd, buff, strlen(buff), 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, GRAPHICAL);
}

Test(graphics, ppo_invalid_arg)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *ai = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    char buff[4096] = {0};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_not_null(ai);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "GRAPHIC\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(ai->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sprintf(buff, "ppo\n");
    sendto(fake->fd, buff, strlen(buff), 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, GRAPHICAL);
}

Test(graphics, ppo_ia_valid)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *ai = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    char buff[4096] = {0};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_not_null(ai);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "GRAPHIC\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(ai->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sprintf(buff, "ppo %d\n", list->start->next->next->socket->fd);
    sendto(fake->fd, buff, strlen(buff), 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, GRAPHICAL);
}

Test(graphics, get_player_id)
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
    list->start->next->socket->data = NULL;
    get_player_by_id(list->start->next->socket->fd, list);
}

Test(graphics, plv)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *ai = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    char buff[4096] = {0};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_not_null(ai);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "GRAPHIC\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(ai->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sprintf(buff, "plv %d\n", list->start->next->next->socket->fd);
    sendto(fake->fd, buff, strlen(buff), 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, GRAPHICAL);
}

Test(graphics, plv_invalid_arg)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *ai = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    char buff[4096] = {0};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_not_null(ai);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "GRAPHIC\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(ai->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sprintf(buff, "plv 0\n");
    sendto(fake->fd, buff, strlen(buff), 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, GRAPHICAL);
}

Test(graphics, plv_invalid_nb_arg)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *ai = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    char buff[4096] = {0};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_not_null(ai);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "GRAPHIC\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(ai->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sprintf(buff, "plv\n");
    sendto(fake->fd, buff, strlen(buff), 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, GRAPHICAL);
}

Test(graphics, ia_plv)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *ai = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    char buff[4096] = {0};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_not_null(ai);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "GRAPHIC\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(ai->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    sendto(fake->fd, buff, strlen(buff), 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, GRAPHICAL);
    graph_send_ia_plv(list, ZAPPY_CLIENT(list->start->next->next->socket)->client.ia);
}

Test(graphics, command_error)
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
    sendto(fake->fd, "GRAPHIC\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(ai->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    sendto(fake->fd, "issou\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
}

Test(graphics, command_pin)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *ai = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    char buff[4096] = {0};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_not_null(ai);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "GRAPHIC\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(ai->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sprintf(buff, "pin %d\n", list->start->next->next->socket->fd);
    sendto(fake->fd, buff, strlen(buff), 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, GRAPHICAL);
}

Test(graphics, pin_no_arg)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *ai = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    char buff[4096] = {0};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_not_null(ai);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "GRAPHIC\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(ai->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sprintf(buff, "pin\n");
    sendto(fake->fd, buff, strlen(buff), 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, GRAPHICAL);
}

Test(graphics, pin_no_fd)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *ai = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    char buff[4096] = {0};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_not_null(ai);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "GRAPHIC\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(ai->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sprintf(buff, "pin 0\n");
    sendto(fake->fd, buff, strlen(buff), 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, GRAPHICAL);
}

Test(graphics, bct)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *ai = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    char buff[4096] = {0};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_not_null(ai);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "GRAPHIC\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(ai->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sprintf(buff, "bct 0 0\n");
    sendto(fake->fd, buff, strlen(buff), 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, GRAPHICAL);
}

Test(graphics, bct_bad_nb_arg)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *ai = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    char buff[4096] = {0};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_not_null(ai);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "GRAPHIC\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(ai->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sprintf(buff, "bct 0\n");
    sendto(fake->fd, buff, strlen(buff), 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, GRAPHICAL);
}

Test(graphics, bct_invalid_arg)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *ai = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    char buff[4096] = {0};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_not_null(ai);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "GRAPHIC\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(ai->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sprintf(buff, "bct salut bonsoir\n");
    sendto(fake->fd, buff, strlen(buff), 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, GRAPHICAL);
}

Test(graphics, mct)
{
    sock_t *serv = socket_serv_init(0, init_game, delete_game);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *ai = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_list_t *list = socket_list_init();
    char *team[3] = {"team1", "team2", NULL};
    char buff[4096] = {0};
    zarg_t zarg = {0};
    arg_t arg = {"8080", "3", "3", team, "2", "1"};

    arg_to_zarg(&arg, &zarg);
    initialize_game_args(serv->data, &zarg);
    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cr_assert_not_null(ai);
    cr_assert_eq(socket_list_add(list, serv), 0);
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(fake->fd, "GRAPHIC\n", 8, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sendto(ai->fd, "team1\n", 6, 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    sprintf(buff, "mct\n");
    sendto(fake->fd, buff, strlen(buff), 0, (struct sockaddr *)&serv->info, sizeof(struct sockaddr_in));
    manage_event(list, socket_list_get_event(list), &zarg);
    cr_assert_eq(ZAPPY_CLIENT(list->start->next->socket)->cli_type, GRAPHICAL);
}
