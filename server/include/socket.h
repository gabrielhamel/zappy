/*
** EPITECH PROJECT, 2019
** bootstrap
** File description:
** socket
*/

#ifndef SOCKET_H
#define SOCKET_H

#include <netinet/in.h>
#include <sys/select.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum sock_type_t {
    SERVER,
    CLIENT
} sock_type_t;

typedef struct sock_t {
    int fd;
    struct sockaddr_in info;
    sock_type_t type;
    void *data;
    void *(*ctor)(const struct sock_t *);
    void (*dtor)(const struct sock_t *, void *);
} sock_t;

typedef void *(*ctor_t)(const struct sock_t *);
typedef void (*dtor_t)(const struct sock_t *, void *);

typedef struct sock_node_t {
    sock_t *socket;
    struct sock_node_t *next;
} sock_node_t;

typedef struct sock_list_t {
    fd_set fdlist;
    sock_node_t *start;
    sock_t **tab;
} sock_list_t;

sock_list_t *socket_list_init(void);
int socket_list_remove_no_close(sock_list_t *list, sock_t *socket);
int socket_list_add(sock_list_t *list, sock_t *socket);
int socket_list_remove(sock_list_t *list, sock_t *socket);
int socket_list_destroy(sock_list_t *list);
sock_t *socket_list_get_socket(sock_list_t *list, int fd);
sock_t **socket_list_get_event(sock_list_t *list);
int socket_list_destroy_no_close(sock_list_t *list);
sock_t *socket_init(ctor_t ctor, dtor_t dtor);
sock_t *socket_cli_init(uint16_t port, uint32_t ip, ctor_t ctor, dtor_t dtor);
sock_t *socket_serv_init(uint16_t port, ctor_t ctor, dtor_t dtor);
sock_t *socket_serv_accept_cli(sock_t *serv, ctor_t ctor, dtor_t dtor);
int socket_destroy(sock_t *socket);
int socket_destroy_no_close(sock_t *socket);

#endif