/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** events
*/

#include "server.h"

static void server_event(sock_list_t *list, sock_t *server)
{
    sock_t *tmp = socket_serv_accept_cli(server, init_client, end_client);

    if (tmp != NULL)
        socket_list_add(list, tmp);
}

static void destroy_ftp_sock(sock_list_t *list, sock_t *cli)
{
    socket_list_remove(list, cli);
}

static void client_event(sock_list_t *list, sock_t *client)
{
    char *buff = read_line(client);
    char **toks;
    size_t len;

    if (buff == NULL)
        destroy_ftp_sock(list, client);
    else {
        toks = tokenize(buff, " ");
        len = strlen(buff);
        free(buff);
        if (toks != NULL && len)
            exec_command(client, list, toks);
        if (toks != NULL)
            destroy_array(toks);
    }
}

void manage_event(sock_list_t *list, sock_t **evt_socks)
{
    for (size_t i = 0; evt_socks[i] != NULL; i++)
        if (evt_socks[i]->type == SERVER)
            server_event(list, evt_socks[i]);
        else
            client_event(list, evt_socks[i]);
}