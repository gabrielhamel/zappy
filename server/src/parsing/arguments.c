/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** arguments
*/

#include "server.h"

static argument_t flags[] = {
    {"-p", false, offsetof(arg_t, port), check_port},
    {"-x", false, offsetof(arg_t, width), check_dimension},
    {"-y", false, offsetof(arg_t, height), check_dimension},
    {"-n", true, offsetof(arg_t, team_names), check_team},
    {"-c", false, offsetof(arg_t, clients_nb), check_clients_nb},
    {"-f", false, offsetof(arg_t, freq), check_freq}
};

static argument_t *get_flag(char *str)
{
    size_t idx = 0;

    for (; idx < ARRAY_SIZE(flags) &&
        strcmp(str, flags[idx].flag); idx++);
    if (idx == ARRAY_SIZE(flags))
        return (NULL);
    return (&flags[idx]);
}

int count_nb_arg(int ac, char **av, int i)
{
    int j = 0;

    while (i < ac && get_flag(av[i]) == NULL) {
        j++;
        i++;
    }
    return (j);
}

static void fill_arg(arg_t *arg, argument_t *flag, void *data)
{
    char **str = (void *)arg + flag->offset;

    *str = data;
}

bool parsing(arg_t *arg, int ac, char **av)
{
    argument_t *flag;
    void *state;

    for (int i = 1; i < ac; i++) {
        flag = get_flag(av[i]);
        if (flag && flag->infinity == false)
            state = parse_single_arg(ac, av, flag, &i);
        else if (flag && flag->infinity)
            state = parse_infinity_arg(ac, av, flag, &i);
        else
            state = NULL;
        if (state == NULL)
            return (false);
        fill_arg(arg, flag, state);
    }
    if (arg->clients_nb && arg->freq && arg->height
    && arg->port && arg->team_names && arg->width)
        return (true);
    return (false);
}