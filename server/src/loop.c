/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** loop
*/

#include <signal.h>
#include "server.h"

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

static void zappy_loop(sock_list_t *list)
{
    sock_t **tab;

    while (*loop()) {
        tab = socket_list_get_event(list);
        list->tab = tab;
        if (tab == NULL)
            continue;
        manage_event(list, tab);
        free(tab);
    }
}

void launch_zappy(uint16_t port)
{
    sock_list_t *list = socket_list_init();
    sock_t *tmp;

    list->tab = NULL;
    tmp = socket_serv_init(port, NULL, NULL);
    socket_list_add(list, tmp);
    signal(SIGINT, forcequit);
    zappy_loop(list);
    socket_list_destroy(list);
}