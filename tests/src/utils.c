/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** utils
*/

#include <criterion/criterion.h>
#include "utils.h"

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
