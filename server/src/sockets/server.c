/*
** EPITECH PROJECT, 2019
** bootstrap
** File description:
** socket
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "socket.h"

sock_t *socket_init(ctor_t ctor, dtor_t dtor)
{
    sock_t *sock = malloc(sizeof(sock_t));
    int option = 1;

    memset(sock, 0, sizeof(sock_t));
    sock->fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(sock->fd, SOL_SOCKET, SO_REUSEADDR, &option,
    sizeof(int));
    sock->ctor = ctor;
    sock->dtor = dtor;
    if (sock->ctor != NULL)
        sock->data = sock->ctor(sock);
    return (sock);
}

sock_t *socket_serv_init(uint16_t port, ctor_t ctor, dtor_t dtor)
{
    sock_t *socket = socket_init(ctor, dtor);
    socklen_t len = sizeof(struct sockaddr_in);

    socket->info.sin_port = htons(port);
    socket->info.sin_family = AF_INET;
    socket->info.sin_addr.s_addr = INADDR_ANY;
    if (bind(socket->fd, (struct sockaddr *)&socket->info,
    sizeof(struct sockaddr_in)) == -1) {
        socket_destroy(socket);
        return (NULL);
    }
    listen(socket->fd, SOMAXCONN);
    socket->type = SERVER;
    getsockname(socket->fd, (struct sockaddr *)&socket->info, &len);
    return (socket);
}

int socket_destroy(sock_t *socket)
{
    if (socket->dtor != NULL)
        socket->dtor(socket, socket->data);
    shutdown(socket->fd, SHUT_RDWR);
    close(socket->fd);
    free(socket);
    return (0);
}

sock_t *socket_serv_accept_cli(sock_t *server, ctor_t ctor, dtor_t dtor)
{
    sock_t *client = malloc(sizeof(sock_t));
    int fd = -1;
    socklen_t size = sizeof(struct sockaddr_in);

    memset(client, 0, sizeof(sock_t));
    fd = accept(server->fd, (struct sockaddr *)&client->info, &size);
    client->fd = fd;
    client->type = CLIENT;
    client->ctor = ctor;
    client->dtor = dtor;
    if (client->ctor != NULL)
        client->data = client->ctor(client);
    return (client);
}
