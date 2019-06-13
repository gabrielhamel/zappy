/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** fct_cli
*/

#include "server.h"
#include "graph_commands.h"

void disconnect_player(sock_t *cli, sock_list_t *list)
{
    ia_t *ia = ZAPPY_CLIENT(cli)->client.ia;
    size_t i = 0;
    char buffer[4096] = {0};

    for (; ia->team->sock[i] != cli; i++);
    ia->team->sock[i] = NULL;
    ia->team->nb_clients--;
    sprintf(buffer, "pdi %d\n", ia->id);
    send_all_graphics(list, buffer);
    printf("IA %d disconnected\n", cli->fd);
}

void *init_client(const sock_t *cli)
{
    zappy_client_t *data = malloc(sizeof(zappy_client_t));

    memset(data, 0, sizeof(zappy_client_t));
    dprintf(cli->fd, "WELCOME\n");
    data->cmd_buff = strdup("");
    data->cli_type = UNDEFINED;
    return (data);
}

void end_client(const sock_t *cli, void *data)
{
    STAILQ_HEAD(, buffer_cmd_s) *list = (void *)LIST_CMD(cli);
    zappy_client_t *zcli = data;
    buffer_cmd_t *tmp;
    buffer_cmd_t *tmp2;
    client_type_t type = zcli->cli_type;

    if (data == NULL)
        return;
    if (type == IA) {
        tmp = list->stqh_first;
        while (tmp != NULL) {
            destroy_array(tmp->cmd);
            tmp2 = tmp;
            tmp = tmp->next.stqe_next;
            free(tmp2);
        }
        free(ZAPPY_CLIENT(cli)->client.ia);
    } else if (type == GRAPHICAL)
        free(ZAPPY_CLIENT(cli)->client.graphic);
    free(BUFF_CMD(cli));
    free(data);
}
