/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** events
*/

#include "server.h"
#include "graph_commands.h"
#include "ia_commands.h"

void refresh_player_live(sock_list_t *list, sock_t *sock, zarg_t *zarg)
{
    ia_t *ia = ZAPPY_CLIENT(sock)->client.ia;

    if (ia->inventory[FOOD] == 0) {
        destroy_ftp_sock(list, sock);
        return;
    }
    ia->inventory[FOOD]--;
    graph_send_ia_pin(list, ia);
    ia->live = 126.f / zarg->freq;
}

static void server_event(sock_list_t *list, sock_t *server, zarg_t *zarg)
{
    sock_t *tmp = socket_serv_accept_cli(server, init_client, end_client);

    (void)zarg;
    if (tmp != NULL)
        socket_list_add(list, tmp);
}

void destroy_ftp_sock(sock_list_t *list, sock_t *cli)
{
    if (cli->type == CLIENT && ZAPPY_CLIENT(cli)->cli_type == IA)
        disconnect_player(cli, list);
    socket_list_remove(list, cli);
}

static void client_event(sock_list_t *list, sock_t *client, zarg_t *zarg)
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
            exec_command(client, list, toks, zarg);
        else if (toks)
            destroy_array(toks);
    }
}

void manage_event(sock_list_t *list, sock_t **evt_socks, zarg_t *zarg)
{
    for (size_t i = 0; evt_socks[i] != NULL; i++)
        if (evt_socks[i]->type == SERVER)
            server_event(list, evt_socks[i], zarg);
        else
            client_event(list, evt_socks[i], zarg);
}
