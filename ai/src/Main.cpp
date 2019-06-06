/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** main
*/

#include <iostream>
#include "Application.hpp"
#include "ParsingError.hpp"
#include "SocketError.hpp"

int main(int ac, char **av)
{
    try {
        zpy::Application app(ac, av);
    } catch (const zpy::SocketError &e) {
        std::cout << e.what() << std::endl;
        return 84;
    } catch (const zpy::ParsingError &e) {
        std::cout << e.what() << std::endl;
        std::cerr << zpy::Application::usage(av[0]) << std::endl;
        return 84;
    }
    return 0;
}