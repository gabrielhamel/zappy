/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Broadcast
*/

#include <math.h>
#include "graph_commands.h"
#include "server.h"

static const int interval[8][4] = {
    {18.5, 71.5, NEGATIVE, NEGATIVE},
    {71.5, 108.5, ZERO, NEGATIVE},
    {108.5, 161.5, POSITIVE, NEGATIVE},
    {161.5, 198.5, POSITIVE, ZERO},
    {198.5, 251.5, POSITIVE, POSITIVE},
    {251.5, 288.5, ZERO, POSITIVE},
    {288.5, 341.5, NEGATIVE, POSITIVE},
    {341.5, 18.5, NEGATIVE, ZERO},
};

static int get_min_x(map_t *map, ia_t *sender, ia_t *receiver)
{
    int right = 0;
    int left = 0;
    tile_t *tmp;

    for (tmp = &map->graph[sender->y][sender->x];
    tmp->x != receiver->x; tmp = tmp->right)
        right++;
    for (tmp = &map->graph[sender->y][sender->x];
    tmp->x != receiver->x; tmp = tmp->left)
        left--;
    if (abs(left) < abs(right))
        return left;
    return right;
}

static int get_min_y(map_t *map, ia_t *sender, ia_t *receiver)
{
    int top = 0;
    int bottom = 0;
    tile_t *tmp;

    for (tmp = &map->graph[sender->y][sender->x];
    tmp->y != receiver->y; tmp = tmp->top)
        top--;
    for (tmp = &map->graph[sender->y][sender->x];
    tmp->y != receiver->y; tmp = tmp->bottom)
        bottom++;
    if (abs(bottom) < abs(top))
        return bottom;
    return top;
}

void graph_send_broadcast(sock_list_t *list, ia_t *ia, const char *str)
{
    char buff[4096] = {0};

    sprintf(buff, "pbc %d %s\n", ia->id, str);
    send_all_graphics(list, buff);
}

static void broadcast(map_t *map, ia_t *sender, ia_t *receiver, const char *s)
{
    int dir;
    float x = (float)get_min_x(map, sender, receiver);
    float y = (float)get_min_y(map, sender, receiver);
    float alpha = atan2f(y, x) * (180.f / M_PI);

    if (alpha < 0)
        alpha += 360;
    for (dir = 0; dir < 8; dir++) {
        if (alpha >= interval[dir][0] && alpha < interval[dir][1])
            break;
    }
    if (dir == 8)
        dir = 7;
    dir = get_direction(receiver, interval[dir][2], interval[dir][3]);
    if (sender->x == receiver->x && sender->y == receiver->y)
        dir = 0;
    dprintf(receiver->id, "message %d, %s\n", dir, s);
}

void cmd_ia_broad(sock_t *cli, sock_list_t *list, char **arg, zarg_t *zarg)
{
    ia_t *me = ZAPPY_CLIENT(cli)->client.ia;
    ia_t *ia;
    zappy_client_t *client;

    (void)zarg;
    if (array_lenght(arg) < 2) {
        sock_write(cli, "ok\n");
        return;
    }
    for (sock_node_t *node = list->start; node != NULL; node = node->next) {
        client = node->socket->data;
        if (node->socket->type != CLIENT || client == NULL ||
        client->cli_type != IA)
            continue;
        ia = client->client.ia;
        if (ia == me)
            continue;
        broadcast(&GET_GAME(list)->map, me, ia, arg[1]);
    }
    graph_send_broadcast(list, me, arg[1]);
    sock_write(cli, "ok\n");
}
