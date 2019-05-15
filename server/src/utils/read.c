/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** read
*/

#include "utils.h"
#include <server.h>
#include <unistd.h>

static char *cleanup(char *str)
{
    char *ptr = strchr(str, '\n');

    if (ptr)
        *ptr = '\0';
    if (ptr && *(str + 1) && *(ptr - 1) == '\r')
        *(ptr - 1) = '\0';
    return (str);
}

static char *get_buff(sock_t *socket)
{
    char *tmp = BUFF_CMD(socket);

    BUFF_CMD(socket) = strdup("");
    return (tmp);
}

static char *concat_buff(sock_t *socket, char *buff)
{
    char *tmp = BUFF_CMD(socket);

    BUFF_CMD(socket) = str_add(2, tmp, buff);
    free(tmp);
    return (BUFF_CMD(socket));
}

char *read_line(sock_t *socket)
{
    char buff[READ_SIZE] = {0};
    char *tmp;

    if (!read(socket->fd, buff, READ_SIZE)) {
        tmp = BUFF_CMD(socket);
        if (!strcmp("", tmp))
            return (NULL);
        return (get_buff(socket));
    }
    tmp = concat_buff(socket, buff);
    if (!strcmp("", tmp))
        return (NULL);
    if (strchr(tmp, '\n'))
        return (cleanup(get_buff(socket)));
    return (strdup(""));
}