/*
** EPITECH PROJECT, 2019
** check_team_names.c
** File description:
** checking the team names
*/

#include "game.h"

bool check_team_names(char **arg, zarg_t *zarg)
{
    size_t i;

    for (i = 0; zarg->team_names[i] != NULL; i++) {
        if (!strcmp(arg[0], zarg->team_names[i])) {
            return (true);
        }
    }
    return (false);
}