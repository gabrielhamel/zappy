/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** utils
*/

#include <criterion/criterion.h>
#include <unistd.h>
#include "utils.h"
#include "server.h"

Test(utils, array_valid)
{
    char **tab = alloc_array(2, sizeof(char *));
    size_t len;

    tab[0] = strdup("salut");
    tab[1] = NULL;
    len = array_lenght(tab);
    cr_assert_eq(len, 1);
    destroy_array(tab);
}

Test(utils, array_invalid)
{
    size_t len = array_lenght(NULL);

    cr_assert_eq(len, 0);
}

Test(utils, tokenize_valid)
{
    char *str = "salut bonsoir lol";
    char **tab = tokenize(str, " ");

    cr_assert_str_eq(tab[0], "salut");
    cr_assert_str_eq(tab[1], "bonsoir");
    cr_assert_str_eq(tab[2], "lol");
    cr_assert_eq(tab[3], NULL);
}

Test(utils, tokenize_invalid)
{
    char *str = "";
    char **tab = tokenize(str, " ");

    cr_assert_eq(tab[0], NULL);
}

Test(utils, tokenize_broadcast_except)
{
    char *str = "Broadcast salut bonsoir";
    char **tab = tokenize(str, " ");

    cr_assert_str_eq(tab[0], "Broadcast");
    cr_assert_str_eq(tab[1], "Broadcast salut bonsoir");
    cr_assert_str_eq(tab[2], "bonsoir");
    cr_assert_eq(tab[3], NULL);
}

Test(utils, str_add_valid)
{
    char *str = str_add(3, "salut", "bonsoir", "lol");

    cr_assert_str_eq(str, "salutbonsoirlol");
}

Test(utils, str_add_invalid)
{
    char *str = str_add(0);

    cr_assert_eq(str, NULL);
}

Test(utils, is_num_valid)
{
    bool res = is_num("42");

    cr_assert(res);
}

Test(utils, is_num_invalid)
{
    bool res = is_num("abcde");

    cr_assert_not(res);
}

Test(utils, socket_readline)
{
    int fd[2] = {0};
    sock_t sock = {0};
    char *str;
 
    cr_assert(pipe(fd) != -1);
    sock.fd = fd[1];
    sock.data = init_client(&sock);
    sock.fd = fd[0];
    str = read_line(&sock);
    cr_assert_str_eq(str, "WELCOME");
    write(fd[1], "salut", 5);
    str = read_line(&sock);
    cr_assert_str_eq(str, "");
    write(fd[1], "bonsoir\n", 8);
    str = read_line(&sock);
    cr_assert_str_eq(str, "salutbonsoir");
}

Test(utils, socket_readline_crlf)
{
    int fd[2] = {0};
    sock_t sock = {0};
    char *str;
 
    cr_assert(pipe(fd) != -1);
    sock.fd = fd[1];
    sock.data = init_client(&sock);
    sock.fd = fd[0];
    str = read_line(&sock);
    cr_assert_str_eq(str, "WELCOME");
    write(fd[1], "salut\r\n", 7);
    str = read_line(&sock);
    cr_assert_str_eq(str, "salut");
}

Test(utils, socket_readline_no_data)
{
    int fd[2] = {0};
    sock_t sock = {0};
    char *str;
 
    cr_assert(pipe(fd) != -1);
    sock.fd = fd[1];
    sock.data = init_client(&sock);
    sock.fd = fd[0];
    str = read_line(&sock);
    cr_assert_str_eq(str, "WELCOME");
    write(fd[1], "", 1);
    str = read_line(&sock);
    cr_assert_eq(str, NULL);
}

Test(utils, socket_readline_no_data_but_buff)
{
    int fd[2] = {0};
    sock_t sock = {0};
    char *str;
 
    cr_assert(pipe(fd) != -1);
    sock.fd = fd[1];
    sock.data = init_client(&sock);
    sock.fd = fd[0];
    str = read_line(&sock);
    cr_assert_str_eq(str, "WELCOME");
    write(fd[1], "salut", 5);
    str = read_line(&sock);
    cr_assert_str_eq(str, "");
    close(fd[1]);
    str = read_line(&sock);
    cr_assert_str_eq(str, "salut");
}

Test(utils, socket_readline_no_data_but_buff_null)
{
    int fd[2] = {0};
    sock_t sock = {0};
    char *str;
 
    cr_assert(pipe(fd) != -1);
    sock.fd = fd[1];
    sock.data = init_client(&sock);
    sock.fd = fd[0];
    str = read_line(&sock);
    cr_assert_str_eq(str, "WELCOME");
    close(fd[1]);
    str = read_line(&sock);
    cr_assert_eq(str, NULL);
}