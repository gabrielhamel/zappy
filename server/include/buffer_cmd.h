/*
** EPITECH PROJECT, 2019
** buffer_cmd.h
** File description:
** buffer_cmd header
*/

#ifndef BUFFER_CMD_H_
#define BUFFER_CMD_H_

#define ZAPPY_CLIENT(x) ((zappy_client_t *)(x->data))

#include "ia.h"
#include "player.h"

typedef struct s_buffer_cmd {
    char **cmd;
    struct s_buffer_cmd *next;
} buffer_cmd_t;

typedef buffer_cmd_t *list_t;

typedef union {
    ia_t *IA;
    player_t *graphic;
} un_cli_t;

// void list_dump(list_t list);
// int list_add_elem_at_front(list_t *front_ptr, char **cmd);
// void test_lists(sock_t *cli);

#endif /* !BUFFER_CMD_H_ */
