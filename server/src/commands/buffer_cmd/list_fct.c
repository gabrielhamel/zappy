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

void list_insert(void *p_list, char **cmd, float time)
{
    buffer_cmd_t *new_elem = malloc(sizeof(buffer_cmd_t));
    STAILQ_HEAD(, buffer_cmd_s) *list = p_list;

    new_elem->cmd = cmd;
    new_elem->time = time;
    STAILQ_INSERT_TAIL(list, new_elem, next);
}

buffer_cmd_t *list_head(void *p_list)
{
    STAILQ_HEAD(, buffer_cmd_s) *list = p_list;
    buffer_cmd_t *first = STAILQ_FIRST(list);

    return (first);
}

char **list_pop(void *p_list)
{
    STAILQ_HEAD(, buffer_cmd_s) *list = p_list;
    buffer_cmd_t *first = STAILQ_FIRST(list);
    char **tmp;

    if (first == NULL)
        return (NULL);
    STAILQ_REMOVE_HEAD(list, next);
    tmp = first->cmd;
    free(first);
    return (tmp);
}

void list_elem_destroy(buffer_cmd_t *elem)
{
    destroy_array(elem->cmd);
    free(elem);
}