/*
** EPITECH PROJECT, 2019
** Calculatrice
** File description:
** Main
*/

#include <memory>
#include "Application.hpp"

int main(int ac, char **av)
{
    auto app = std::unique_ptr<Application>(new Application(1500, 960, "Zappy", av[1], av[2]));

    app->Run();
    return (EXIT_SUCCESS);
}