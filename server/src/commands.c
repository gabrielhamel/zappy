/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** commands
*/

#include <sys/queue.h>
#include <stdbool.h>

#include "server.h"
#include "buffer_cmd.h"
#include "player.h"

static void list_dump(void *p_list)
{
    struct buffer_cmd_s *p;
    STAILQ_HEAD(, buffer_cmd_s) *list = p_list;

    STAILQ_FOREACH(p, list, next) {
        printf("%s\n", p->cmd[0]);
    }
}

static bool list_add_elem_at_back(void *p_list, char **cmd)
{
    buffer_cmd_t *new_elem = malloc(sizeof(buffer_cmd_t));

    STAILQ_HEAD(, buffer_cmd_s) *list = p_list;

    if (new_elem == NULL)
        return (true);
    new_elem->cmd = cmd;

    STAILQ_INSERT_TAIL(list, new_elem, next);
    return (0);
}


static buffer_cmd_t* list_get_elem_at_front(void *p_list)
{
    STAILQ_HEAD(, buffer_cmd_s) *list = p_list;

    return (STAILQ_FIRST(list));
}


static void test_lists(sock_t *cli)
{
    char *arg_1[1] = { "a" };
    char *arg_2[1] = { "b" };
    char *arg_3[1] = { "c" };
    char *arg_4[1] = { "d" };

    list_add_elem_at_back(&(ZAPPY_CLIENT(cli)->client.graphic->list_head), arg_1);
    list_add_elem_at_back(&(ZAPPY_CLIENT(cli)->client.graphic->list_head), arg_2);
    list_add_elem_at_back(&(ZAPPY_CLIENT(cli)->client.graphic->list_head), arg_3);
    list_add_elem_at_back(&(ZAPPY_CLIENT(cli)->client.graphic->list_head), arg_4);
    list_dump(&(ZAPPY_CLIENT(cli)->client.graphic->list_head));
    printf("------\nfirst one: %s\n", list_get_elem_at_front(&(ZAPPY_CLIENT(cli)->client.graphic->list_head))->cmd[0]);
}

void exec_command(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    (void)cli;
    (void)list;
    (void)arg;

    sock_t client;
    zappy_client_t *test = malloc(sizeof(zappy_client_t));

    test->client.graphic = malloc(sizeof(player_t));
    // test->client.graphic->list_head = NULL;
    STAILQ_INIT(&test->client.graphic->list_head);

    client.data = test;
    test_lists(&client);

    // if (ZAPPY_CLIENT(cli)->cli_type == UNDEFINED) {
    //     if (!strcmp("GRAPHIC", arg[0])) {
    //         ZAPPY_CLIENT(cli)->cli_type = GRAPHICAL;
    //         ZAPPY_CLIENT(cli)->client.graphic = malloc(sizeof(graphic_client_t));
    //         ZAPPY_CLIENT(cli)->client.graphic->list_head = NULL;
    //     } else {
    //         // Comparaison du TEAM-NAME avec les arguments lors de l'exécution
    //         ZAPPY_CLIENT(cli)->cli_type = IA;
    //         ZAPPY_CLIENT(cli)->client.IA = malloc(sizeof(IA_client_t));
    //         ZAPPY_CLIENT(cli)->client.IA->list_head = NULL;
    //     }
    // } else {
    //     if (ZAPPY_CLIENT(cli)->cli_type == GRAPHICAL) {
    //         list_add_elem_at_front(&(ZAPPY_CLIENT(cli)->client.graphic->list_head), arg);
    //     } else {
    //         list_add_elem_at_front(&(ZAPPY_CLIENT(cli)->client.IA->list_head), arg);
    //     }
    // }
}
