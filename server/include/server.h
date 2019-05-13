/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** server
*/

#ifndef SERVER_H
#define SERVER_H

#include "socket.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFF_CMD(x) ((zappy_client_t *)x->data)->cmd_buff

typedef struct {
    const char *name;
    void (*func)(sock_t *, sock_list_t *, char **);
} command_t;

typedef struct {
    char *cmd_buff;
} zappy_client_t;

extern command_t commands_g[];

void launch_zappy(uint16_t port);
char *read_line(sock_t *socket);
void manage_event(sock_list_t *list, sock_t **evt_socks);
void exec_command(sock_t *cli, sock_list_t *list, char **arg);
void *init_client(const sock_t *cli);
void end_client(const sock_t *cli, void *data);

void command_ping(sock_t *cli, sock_list_t *list, char **arg);

#endif