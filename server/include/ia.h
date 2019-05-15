/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** ia
*/

#pragma once

#include <stdlib.h>

typedef struct s_buffer_cmd buffer_cmd_t;
typedef buffer_cmd_t *list_t;

typedef struct ia_s {
    size_t x;
    size_t y;
    list_t list_head;
} ia_t;
