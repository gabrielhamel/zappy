/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** loop
*/

#include <signal.h>
#include "game.h"

static bool *loop(void)
{
    static bool loop = true;

    return (&loop);
}

static void forcequit(int sig)
{
    bool *test = loop();

    (void)sig;
    *test = false;
}

static void zappy_loop(sock_list_t *list, zarg_t *zarg)
{
    sock_t **tab;

    while (*loop()) {
        tab = socket_list_get_event(list, NULL);
        list->tab = tab;
        if (tab == NULL)
            continue;
        manage_event(list, tab, zarg);
        free(tab);
    }
}

int launch_zappy(zarg_t *zarg)
{
    sock_list_t *list = socket_list_init();
    sock_t *tmp;

    list->tab = NULL;
    tmp = socket_serv_init(zarg->port, init_game, delete_game);
    tmp->data = initialize_teams(zarg);
    if (tmp == NULL)
        return (84);
    socket_list_add(list, tmp);
    signal(SIGINT, forcequit);
    zappy_loop(list, zarg);
    socket_list_destroy(list);
    return (0);
}