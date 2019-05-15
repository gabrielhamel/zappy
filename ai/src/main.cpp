/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** main
*/

#include "Server.hpp"

int main(int ac, char **av)
{
    auto server = Server(av[1], av[2]);

    std::cout << server.Read();
    server.Write("issou\n");
    std::cout << server.Read();
    std::cout << server.Read();
    return (0);
}