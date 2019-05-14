/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** types
*/

#include "server.h"

void *parse_single_arg(int ac, char **av, argument_t *flag, int *i)
{
    if (*i + 1 == ac || flag->check(av[++(*i)]) == false)
        return (NULL);
    return (av[*i]);
}

void *parse_infinity_arg(int ac, char **av, argument_t *flag, int *i)
{
    int nb = count_nb_arg(ac, av, ++(*i));
    char **tab = alloc_array(nb, sizeof(char *));

    if (nb == 0) {
        free(tab);
        return (NULL);
    }
    for (int u = *i; u < *i + nb; u++) {
        tab[u - *i] = av[u];
        if (flag->check(av[u]) == false) {
            free(tab);
            return (NULL);
        }
    }
    *i = *i + nb - 1;
    return (tab);
}