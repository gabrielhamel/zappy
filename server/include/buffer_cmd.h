/*
** EPITECH PROJECT, 2019
** buffer_cmd.h
** File description:
** buffer_cmd header
*/

#ifndef BUFFER_CMD_H_
#define BUFFER_CMD_H_

#define ZAPPY_CLIENT(x) ((zappy_client_t *)(x->data))
#define LIST_CMD(x) &(ZAPPY_CLIENT(x)->client.ia->list_head)

#include "graphic.h"
#include "ia.h"

typedef struct buffer_cmd_s {
    char **cmd;
    float time;
    STAILQ_ENTRY(buffer_cmd_s) next;
} buffer_cmd_t;

typedef union un_cli_s {
    struct ia_s *ia;
    graphic_t *graphic;
} un_cli_t;

void list_dump(void *p_list);
char **list_pop(void *p_list);
buffer_cmd_t *list_head(void *p_list);
void list_insert(void *p_list, char **cmd, float time);
void list_elem_destroy(buffer_cmd_t *elem);

#endif
