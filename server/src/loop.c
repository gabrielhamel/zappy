/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** loop
*/

#include <signal.h>
#include <time.h>
#include <sys/timeb.h>
#include "server.h"
#include "game.h"
#include "graph_commands.h"

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
    struct timeb start = {0};
    struct timeb end = {0};

    while (*loop()) {
        ftime(&start);
        tab = socket_list_get_event(list);
        list->tab = tab;
        if (tab != NULL) {
            manage_event(list, tab, zarg);
            free(tab);
        }
        ftime(&end);
        refresh_cmd(list, zarg, 1000 * (end.time - start.time) +
        (end.millitm - start.millitm));
    }
}

int launch_zappy(zarg_t *zarg)
{
    sock_list_t *list = socket_list_init();
    sock_t *tmp;

    list->tab = NULL;
    tmp = socket_serv_init(zarg->port, init_game, delete_game);
    if (tmp == NULL) {
        socket_list_destroy(list);
        return 84;
    }
    initialize_game_args(tmp->data, zarg);
    if (tmp == NULL)
        return (84);
    socket_list_add(list, tmp);
    signal(SIGINT, forcequit);
    zappy_loop(list, zarg);
    socket_list_destroy(list);
    return (0);
}
