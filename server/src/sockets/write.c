/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** write
*/

#include <stdio.h>
#include <stdarg.h>
#include "socket.h"

int sock_write(const sock_t *sock, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int res;

    res = vdprintf(sock->fd, format, ap);
    fflush(fdopen(sock->fd, "r"));
    va_end(ap);
    return res;
}
