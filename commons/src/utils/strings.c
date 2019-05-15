/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** strings
*/

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

static int check_end(char *buffer)
{
    int size = -1;

    if (buffer == NULL)
        size = 0;
    else
        while (buffer[++size] != '\0');
    return (size);
}

static char *add_str(char *base, char *to_add)
{
    char *end = NULL;
    int counter = -1;
    int size_b = check_end(base);
    int size_a = check_end(to_add);

    end = malloc(sizeof(char) * (size_a + size_b + 1));
    if (!end)
        return (NULL);
    end[size_a + size_b] = '\0';
    while (++counter < size_b)
        end[counter] = base[counter];
    if (base != NULL)
        free(base);
    counter = -1;
    while (++counter < size_a)
        end[size_b + counter] = to_add[counter];
    free(to_add);
    return (end);
}

char *str_add(int nb, ...)
{
    va_list liste;
    char *final = NULL;
    char *str = NULL;

    if (nb <= 0)
        return (NULL);
    va_start(liste, nb);
    for (int i = 0; i < nb; i++) {
        str = va_arg(liste, char *);
        final = add_str(final, strdup(str));
    }
    va_end(liste);
    return (final);
}