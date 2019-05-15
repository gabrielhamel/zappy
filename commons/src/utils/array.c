/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** ioutils
*/

#include <stdlib.h>

void destroy_array(char **tab)
{
    for (size_t i = 0; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
}

size_t array_lenght(char **tab)
{
    size_t i = 0;

    if (tab == NULL)
        return (0);
    for (; tab[i] != NULL; i++);
    return (i);
}