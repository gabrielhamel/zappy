/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** utils
*/

#include <criterion/criterion.h>
#include "parser.h"

Test(parser, check_team_valid)
{
    bool res = check_team("team1");

    cr_expect(res);
}

Test(parser, check_team_invalid)
{
    bool res = check_team("");

    cr_expect_not(res);
}

Test(parser, check_team_double)
{
    check_team("team1");
    bool res = check_team("team1");

    cr_expect_not(res);
}

Test(parser, check_team_not_graphic)
{
    bool res = check_team("GRAPHIC");

    cr_expect_not(res);
}
