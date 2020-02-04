/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** parsing
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>

static size_t get_short_len(void)
{
    size_t len = 1;
    __uint16_t nb = __UINT16_MAX__;

    while (nb > 9) {
        nb /= 10;
        len++;
    }
    return (len);
}

bool check_port(const char *port)
{
    size_t offset = 0;
    size_t len;

    if (!strlen(port))
        return (false);
    for (size_t idx = 0; port[idx] != '\0'; idx++)
        if (isdigit(port[idx]) == false)
            return (false);
    for (; port[offset] == '0'; offset++);
    len = strlen(port + offset);
    if (len == 0 || len > get_short_len() ||
    strtol(port, NULL, 10) > __UINT16_MAX__)
        return (false);
    return (true);
}

bool check_dimension(const char *dim)
{
    int tmp;

    for (size_t i = 0; dim[i] != '\0'; i++)
        if (dim[i] < '0' || dim[i] > '9')
            return (false);
    tmp = strtol(dim, NULL, 10);
    if (tmp == 0)
        return (false);
    return (true);
}

bool check_clients_nb(const char *nb)
{
    int tmp;

    for (size_t i = 0; nb[i] != '\0'; i++)
        if (nb[i] < '0' || nb[i] > '9')
            return (false);
    tmp = strtol(nb, NULL, 10);
    if (tmp == 0)
        return (false);
    return (true);
}

bool check_freq(const char *freq)
{
    int tmp;

    for (size_t i = 0; freq[i] != '\0'; i++)
        if (freq[i] < '0' || freq[i] > '9')
            return (false);
    tmp = strtol(freq, NULL, 10);
    if (tmp == 0)
        return (false);
    return (true);
}
