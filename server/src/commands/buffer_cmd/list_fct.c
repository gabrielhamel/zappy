/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** list_fct
*/

#include <sys/queue.h>
#include <stdbool.h>
#include "server.h"
#include "buffer_cmd.h"
#include "player.h"

void list_dump(void *p_list)
{
    struct buffer_cmd_s *p;
    int i = 0;
    STAILQ_HEAD(, buffer_cmd_s) *list = p_list;

    printf("-------------------Command buffer-----------------\n");
    STAILQ_FOREACH(p, list, next) {
        printf("%d: ", ++i);
        array_dump((const char **)p->cmd, " ");
    }
    printf("--------------------------------------------------\n");
}

void list_insert(void *p_list, char **cmd)
{
    buffer_cmd_t *new_elem = malloc(sizeof(buffer_cmd_t));
    STAILQ_HEAD(, buffer_cmd_s) *list = p_list;

    new_elem->cmd = cmd;
    STAILQ_INSERT_TAIL(list, new_elem, next);
}

buffer_cmd_t *list_head(void *p_list)
{
    STAILQ_HEAD(, buffer_cmd_s) *list = p_list;
    buffer_cmd_t *first = STAILQ_FIRST(list);

    return (first);
}

void list_pop(void *p_list)
{
    STAILQ_HEAD(, buffer_cmd_s) *list = p_list;
    buffer_cmd_t *first = STAILQ_FIRST(list);

    if (first == NULL)
        return;
    STAILQ_REMOVE_HEAD(list, next);
}

void list_elem_destroy(buffer_cmd_t *elem)
{
    destroy_array(elem->cmd);
    free(elem);
}