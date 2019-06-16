/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** direction
*/

#include "ia.h"

static int directions[4][8] = {
    {1, 8, 7, 6, 5, 4, 3, 2},
    {3, 2, 1, 8, 7, 6, 5, 4},
    {5, 4, 3, 2, 1, 8, 7, 6},
    {7, 6, 5, 4, 3, 2, 1, 8},
};

int get_direction(ia_t *ia, direction_t x, direction_t y)
{
    int *dir = directions[ia->ori - 1];

    if (x == ZERO && y == POSITIVE)
        return dir[0];
    if (x == NEGATIVE && y == POSITIVE)
        return dir[7];
    if (x == NEGATIVE && y == ZERO)
        return dir[6];
    if (x == NEGATIVE && y == NEGATIVE)
        return dir[5];
    if (x == ZERO && y == NEGATIVE)
        return dir[4];
    if (x == POSITIVE && y == NEGATIVE)
        return dir[3];
    if (x == POSITIVE && y == ZERO)
        return dir[2];
    if (x == POSITIVE && y == POSITIVE)
        return dir[1];
    return 0;
}

int eject(sock_list_t *list, ia_t *ejecter, ia_t *ejected)
{
    int k = 0;

    ia_move(list, ejected, ejecter->ori);
    if (ejecter->ori == NORTH)
        k = get_direction(ejected, ZERO, NEGATIVE);
    if (ejecter->ori == EAST)
        k = get_direction(ejected, NEGATIVE, ZERO);
    if (ejecter->ori == SOUTH)
        k = get_direction(ejected, ZERO, POSITIVE);
    if (ejecter->ori == WEAST)
        k = get_direction(ejected, POSITIVE, ZERO);
    dprintf(ejected->id, "eject: %d\n", k);
}
