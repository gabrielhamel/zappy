/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** client
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

sock_t *socket_cli_init(uint16_t port, uint32_t ip, ctor_t ctor, dtor_t dtor)
{
    sock_t *socket = socket_init(ctor, dtor);

    socket->info.sin_port = htons(port);
    socket->info.sin_family = AF_INET;
    socket->info.sin_addr.s_addr = ip;
    if (connect(socket->fd, (struct sockaddr *)&socket->info,
    sizeof(struct sockaddr_in)) == -1) {
        socket_destroy(socket);
        return (NULL);
    }
    return (socket);
}