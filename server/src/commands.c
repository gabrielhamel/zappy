/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** commands
*/

#include "server.h"
#include "buffer_cmd.h"

static void list_dump(list_t list)
{
    while (list != NULL) {
        printf("%s\n", list->cmd[0]);
        list = list->next;
    }
}

static int list_add_elem_at_front(list_t *front_ptr , char **cmd)
{
    buffer_cmd_t *new_elem = malloc(sizeof(buffer_cmd_t));

    if (new_elem == NULL)
        return (1);
    new_elem->cmd = cmd;
    new_elem->next = *front_ptr;
    *front_ptr = new_elem;
    return (0);
}

static void test_lists(sock_t *cli)
{
    char *arg_1[1] = { "a" };
    char *arg_2[1] = { "b" };
    char *arg_3[1] = { "c" };
    char *arg_4[1] = { "d" };

    list_add_elem_at_front(&(ZAPPY_CLIENT(cli)->client.graphic->list_head), arg_1);
    list_add_elem_at_front(&(ZAPPY_CLIENT(cli)->client.graphic->list_head), arg_2);
    list_add_elem_at_front(&(ZAPPY_CLIENT(cli)->client.graphic->list_head), arg_3);
    list_add_elem_at_front(&(ZAPPY_CLIENT(cli)->client.graphic->list_head), arg_4);
    list_dump(ZAPPY_CLIENT(cli)->client.graphic->list_head);
}

void exec_command(sock_t *cli, sock_list_t *list, char **arg)
{
    (void)cli;
    (void)list;
    (void)arg;

    sock_t client;
    zappy_client_t *test = malloc(sizeof(zappy_client_t));

    test->client.graphic = malloc(sizeof(graphic_client_t));
    test->client.graphic->list_head = NULL;

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