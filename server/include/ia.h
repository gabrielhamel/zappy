/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** ia
*/

#pragma once

#include <stdlib.h>

#include "sys/queue.h"

typedef struct ia_s {
    size_t x;
    size_t y;
    STAILQ_HEAD(, buffer_cmd_s) list_head;
} ia_t;
