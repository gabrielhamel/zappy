/*
** EPITECH PROJECT, 2019
** buffer_cmd.c
** File description:
** buffer_cmd source
*/

#include "buffer_cmd.h"

void list_dump(list_t list)
{
    while (list != NULL) {
        printf("%s\n", list->cmd[0]);
        list = list->next;
    }
}

int list_add_elem_at_front(list_t *front_ptr , char **cmd)
{
    buffer_cmd_t *new_elem = malloc(sizeof(buffer_cmd_t));

    if (new_elem == NULL)
        return (1);
    new_elem->cmd = cmd;
    new_elem->next = *front_ptr;
    *front_ptr = new_elem;
    return (0);
}

void test_lists(sock_t *cli)
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