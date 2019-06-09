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

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*x))
#define READ_SIZE 1024

char **alloc_array(size_t nbmemb, size_t sizememb);
char *str_add(int nb, ...);
char **tokenize(char *str, char *delim);
size_t array_lenght(char **tab);
void destroy_array(char **tab);
void array_dump(const char **tab, const char *delim);

#endif
