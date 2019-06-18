/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** utils
*/

#include <criterion/criterion.h>
#include "parser.h"
#include "server.h"

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

Test(parser, check_port_valid)
{
    bool res = check_port("8080");

    cr_expect(res);
}

Test(parser, check_port_invalid)
{
    bool res = check_port("");

    cr_expect_not(res);
}

Test(parser, check_port_invalid_alpha)
{
    bool res = check_port("aabb");

    cr_expect_not(res);
}

Test(parser, check_port_invalid_lenght)
{
    bool res = check_port("123456789");

    cr_expect_not(res);
}

Test(parser, check_dimension_valid)
{
    bool res = check_dimension("12");

    cr_expect(res);
}

Test(parser, check_dimension_invalid_alpha)
{
    bool res = check_dimension("12ab");

    cr_expect_not(res);
}

Test(parser, check_dimension_invalid_null)
{
    bool res = check_dimension("0");

    cr_expect_not(res);
}

Test(parser, check_freq_valid)
{
    bool res = check_freq("110");

    cr_expect(res);
}

Test(parser, check_freq_invalid_alpha)
{
    bool res = check_freq("a110");

    cr_expect_not(res);
}

Test(parser, check_freq_invalid_null)
{
    bool res = check_freq("0");

    cr_expect_not(res);
}

Test(parser, check_cli_nb_valid)
{
    bool res = check_clients_nb("110");

    cr_expect(res);
}

Test(parser, check_cli_nb_invalid_alpha)
{
    bool res = check_clients_nb("a110");

    cr_expect_not(res);
}

Test(parser, check_cli_nb_invalid_null)
{
    bool res = check_clients_nb("0");

    cr_expect_not(res);
}

Test(parser, arg_conversion)
{
    char *team[3] = {"team1", "team2", NULL};
    zarg_t zarg = {0};
    arg_t arg = {
        "8080",
        "20",
        "12",
        team,
        "2",
        "100"
    };

    arg_to_zarg(&arg, &zarg);
    cr_expect_str_eq(zarg.team_names[0], "team1");
    cr_expect_str_eq(zarg.team_names[1], "team2");
    cr_expect_eq(zarg.team_names[2], NULL);
    cr_expect_eq(zarg.port, 8080);
    cr_expect_eq(zarg.freq, 100);
    cr_expect_eq(zarg.clients_nb, 2);
    cr_expect_eq(zarg.width, 20);
    cr_expect_eq(zarg.height, 12);
}

Test(parser, parse_single_arg_valid)
{
    int ac = 2;
    char *av[2] = {"-p", "8080"};
    argument_t flag = {"z", false, 0, check_port};
    int i = 0;
    void *arg = parse_single_arg(ac, av, &flag, &i);

    cr_expect_str_eq(arg, "8080");
}

Test(parser, parse_single_arg_error_i)
{
    int ac = 1;
    char *av[1] = {"-p"};
    argument_t flag = {"z", false, 0, check_port};
    int i = 0;
    void *arg = parse_single_arg(ac, av, &flag, &i);

    cr_expect_eq(arg, NULL);
}

Test(parser, parse_single_arg_error_invalid_check)
{
    int ac = 2;
    char *av[2] = {"-p", "abc"};
    argument_t flag = {"p", false, 0, check_port};
    int i = 0;
    char *arg = parse_single_arg(ac, av, &flag, &i);

    cr_expect_eq(arg, NULL);
}

Test(parser, parse_infinity_arg_valid)
{
    int ac = 3;
    char *av[3] = {"-n", "team1", "team2"};
    argument_t flag = {"n", true, 0, check_team};
    int i = 0;
    char **arg = parse_infinity_arg(ac, av, &flag, &i);

    cr_expect_str_eq(arg[0], "team1");
    cr_expect_str_eq(arg[1], "team2");
    cr_expect_eq(arg[2], NULL);
}

Test(parser, parse_infinity_arg_nb_invalid)
{
    int ac = 1;
    char *av[3] = {"-n"};
    argument_t flag = {"n", true, 0, check_team};
    int i = 0;
    char **arg = parse_infinity_arg(ac, av, &flag, &i);

    cr_expect_eq(arg, NULL);
}

Test(parser, parse_infinity_arg_invalid_check)
{
    int ac = 3;
    char *av[3] = {"-n", "team1", "team1"};
    argument_t flag = {"n", true, 0, check_team};
    int i = 0;
    char **arg = parse_infinity_arg(ac, av, &flag, &i);

    cr_expect_eq(arg, NULL);
}

Test(parser, main_parsing)
{
    int ac = 14;
    arg_t arg = {0};
    char *av[] = {
        "./zappy_server",
        "-p", "8080",
        "-x", "50",
        "-y", "25",
        "-c", "2",
        "-n", "team1", "team2",
        "-f", "1"
    };
    bool res = parsing(&arg, ac, av);

    cr_expect(res);
    cr_expect_str_eq(arg.clients_nb, "2");
    cr_expect_str_eq(arg.freq, "1");
    cr_expect_str_eq(arg.height, "25");
    cr_expect_str_eq(arg.width, "50");
    cr_expect_str_eq(arg.port, "8080");
    cr_expect_str_eq(arg.team_names[0], "team1");
    cr_expect_str_eq(arg.team_names[1], "team2");
    cr_expect_eq(arg.team_names[2], NULL);
}

Test(parser, main_parsing_not_all_flag)
{
    int ac = 12;
    arg_t arg = {0};
    char *av[] = {
        "./zappy_server",
        "-p", "8080",
        "-x", "50",
        "-y", "25",
        "-c", "2",
        "-n", "team1", "team2",
    };
    bool res = parsing(&arg, ac, av);

    cr_expect_not(res);
}

Test(parser, main_parsing_error)
{
    int ac = 3;
    arg_t arg = {0};
    char *av[] = {
        "./zappy_server",
        "-z", "zizou"
    };
    bool res = parsing(&arg, ac, av);

    cr_expect_not(res);
}
