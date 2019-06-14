/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** team_name
*/

#include "parser.h"

bool check_team(const char *dim)
{
    static char *buff[4096] = {0};
    static size_t i = 0;

    if (strlen(dim) == 0)
        return false;
    if (!strcmp("GRAPHIC", dim))
        return false;
    for (size_t u = 0; buff[u]; u++)
        if (!strcmp(buff[u], dim))
            return false;
    buff[i++] = (char *)dim;
    return true;
}
