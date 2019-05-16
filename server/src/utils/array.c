/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** ioutils
*/

#include <stdio.h>
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

char **alloc_array(size_t nbmemb, size_t sizememb)
{
    char **tab = malloc(sizememb * (nbmemb + 1));

    for (size_t i = 0; i < nbmemb + 1; i++)
        tab[i] = NULL;
    return (tab);
}

void array_dump(const char **tab, const char *delim)
{
    for (size_t i = 0; tab[i] != NULL; i++)
        printf("%s%s", tab[i], delim);
    printf("\n");
}