/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** geter
*/

#include "ia_commands.h"
#include "server.h"

sock_t *ia_get_sock(sock_t *sock, ia_t *ia)
{
    sock->fd = ia->id;
    return sock;
}
