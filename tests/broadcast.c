/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** broadcast
*/

#include <criterion/criterion.h>
#include <unistd.h>
#include "parser.h"
#include "ia_commands.h"
#include "server.h"

Test(broadcast, get_direction)
{
    int res;
    ia_t ia = {0};

    ia.ori = NORTH;

    res = get_direction(&ia, ZERO, POSITIVE);
    cr_assert_eq(res, 1);

    res = get_direction(&ia, NEGATIVE, POSITIVE);
    cr_assert_eq(res, 2);

    res = get_direction(&ia, NEGATIVE, ZERO);
    cr_assert_eq(res, 3);

    res = get_direction(&ia, NEGATIVE, NEGATIVE);
    cr_assert_eq(res, 4);

    res = get_direction(&ia, ZERO, NEGATIVE);
    cr_assert_eq(res, 5);

    res = get_direction(&ia, POSITIVE, NEGATIVE);
    cr_assert_eq(res, 6);

    res = get_direction(&ia, POSITIVE, ZERO);
    cr_assert_eq(res, 7);

    res = get_direction(&ia, POSITIVE, POSITIVE);
    cr_assert_eq(res, 8);

    res = get_direction(&ia, ZERO, ZERO);
    cr_assert_eq(res, 0);
}
