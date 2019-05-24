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
    auto app = std::unique_ptr<Zappy::Application>(new Zappy::Application(960, 960, "Zappy"));

    app->Run();
    return (EXIT_SUCCESS);
}