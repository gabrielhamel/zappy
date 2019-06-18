/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** socket
*/

#include <criterion/criterion.h>
#include <unistd.h>
#include "parser.h"
#include "server.h"

static void *start(const struct sock_t *cli)
{
    (void)cli;
    return NULL;
}

static void end(const struct sock_t *cli, void *data)
{
    (void)cli;
    (void)data;
}

Test(socket, client_init_failed)
{
    sock_t *res = socket_cli_init(0, 0, NULL, NULL);

    cr_assert_null(res);
}

Test(socket, client_success)
{
    sock_t *serv = socket_serv_init(0, start, end);
    sock_t *cli;

    cr_assert_not_null(serv);
    cli = socket_cli_init(ntohs(serv->info.sin_port), 0, start, end);
    cr_assert_not_null(cli);
}

Test(socket, bind_fail)
{
    sock_t *serv1 = socket_serv_init(0, start, end);
    sock_t *serv2 = socket_serv_init(ntohs(serv1->info.sin_port), start, end);

    cr_assert_not_null(serv1);
    cr_assert_null(serv2);
}

Test(socket, accept_cli)
{
    sock_t *serv = socket_serv_init(0, start, end);
    sock_t *fake = socket_cli_init(ntohs(serv->info.sin_port), 0, NULL, NULL);
    sock_t *cli;

    cr_assert_not_null(serv);
    cr_assert_not_null(fake);
    cli = socket_serv_accept_cli(serv, start, end);
    cr_assert_not_null(cli);
}

Test(socket, get_sock_by_fd)
{
    sock_list_t *list = socket_list_init();
    sock_t sock = {0};
    sock_t *res;

    sock.fd = 42;
    cr_assert_eq(socket_list_add(list, &sock), 0);
    res = socket_list_get_socket(list, 42);
    cr_assert_eq(&sock, res);
    cr_assert_eq(sock.fd, res->fd);
}

Test(socket, get_sock_by_fd_empy)
{
    sock_list_t *list = socket_list_init();
    sock_t *res = socket_list_get_socket(list, 42);

    cr_assert_eq(res, NULL);
}

Test(socket, get_sock_not_found)
{
    sock_list_t *list = socket_list_init();
    sock_t sock = {0};
    sock_t *res;

    sock.fd = 42;
    cr_assert_eq(socket_list_add(list, &sock), 0);
    res = socket_list_get_socket(list, 666);
    cr_assert_eq(res, NULL);
}

Test(socket, get_sock_event_none)
{
    sock_list_t *list = socket_list_init();
    sock_t sock = {0};
    sock_t **res;

    sock.fd = 42;
    cr_assert_eq(socket_list_add(list, &sock), 0);
    res = socket_list_get_event(list);
    cr_assert_eq(res, NULL);
}

Test(socket, get_sock_event_write)
{
    sock_list_t *list = socket_list_init();
    sock_t sock = {0};
    sock_t **res;
    int fd[2] = {0};

    cr_assert(pipe(fd) != -1);
    sock.fd = fd[0];
    cr_assert_eq(socket_list_add(list, &sock), 0);
    write(fd[1], "salut", 5);
    res = socket_list_get_event(list);
    cr_assert_eq(res[0], &sock);
    cr_assert_eq(res[1], NULL);
}

Test(socket, sock_list_destroy)
{
    sock_list_t *list = socket_list_init();
    sock_t *sock = socket_init(NULL, NULL);

    cr_assert_eq(socket_list_add(list, sock), 0);
    cr_assert_eq(socket_list_destroy(list), 0);
}

Test(socket, sock_list_add_many)
{
    sock_list_t *list = socket_list_init();
    sock_t *sock1 = socket_init(NULL, NULL);
    sock_t *sock2 = socket_init(NULL, NULL);

    cr_assert_eq(socket_list_add(list, sock1), 0);
    cr_assert_eq(list->start->socket, sock1);
    cr_assert_eq(socket_list_add(list, sock2), 0);
    cr_assert_eq(list->start->next->socket, sock2);
}

Test(socket, sock_list_remove_first)
{
    sock_list_t *list = socket_list_init();
    sock_t *sock1 = socket_init(NULL, NULL);
    sock_t *sock2 = socket_init(NULL, NULL);

    cr_assert_eq(socket_list_add(list, sock1), 0);
    cr_assert_eq(list->start->socket, sock1);
    cr_assert_eq(socket_list_add(list, sock2), 0);
    cr_assert_eq(list->start->next->socket, sock2);
    cr_assert_eq(socket_list_remove(list, sock1), 0);
}

Test(socket, sock_list_remove_empty)
{
    sock_list_t *list = socket_list_init();
    sock_t *sock = socket_init(NULL, NULL);

    cr_assert_eq(socket_list_remove(list, sock), -1);
}

Test(socket, sock_list_remove_last)
{
    sock_list_t *list = socket_list_init();
    sock_t *sock1 = socket_init(NULL, NULL);
    sock_t *sock2 = socket_init(NULL, NULL);
    sock_t *sock3 = socket_init(NULL, NULL);

    cr_assert_eq(socket_list_add(list, sock1), 0);
    cr_assert_eq(list->start->socket, sock1);
    cr_assert_eq(socket_list_add(list, sock2), 0);
    cr_assert_eq(list->start->next->socket, sock2);
    cr_assert_eq(socket_list_add(list, sock3), 0);
    cr_assert_eq(list->start->next->next->socket, sock3);
    cr_assert_eq(socket_list_remove(list, sock3), 0);
}

Test(socket, sock_list_remove_last_not_exist)
{
    sock_list_t *list = socket_list_init();
    sock_t *sock1 = socket_init(NULL, NULL);
    sock_t *sock2 = socket_init(NULL, NULL);
    sock_t *sock3 = socket_init(NULL, NULL);
    sock_t *sock4 = socket_init(NULL, NULL);

    cr_assert_neq(sock4, NULL);
    cr_assert_eq(socket_list_add(list, sock1), 0);
    cr_assert_eq(list->start->socket, sock1);
    cr_assert_eq(socket_list_add(list, sock2), 0);
    cr_assert_eq(list->start->next->socket, sock2);
    cr_assert_eq(socket_list_add(list, sock3), 0);
    cr_assert_eq(list->start->next->next->socket, sock3);
    cr_assert_eq(socket_list_remove(list, sock4), -1);
}