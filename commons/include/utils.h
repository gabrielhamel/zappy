/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** utils
*/

#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

char *str_add(int nb, ...);
char **tokenize(char *str, char *delim);
size_t array_lenght(char **tab);
void destroy_array(char **tab);

#endif