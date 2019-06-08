/*
** EPITECH PROJECT, 2019
** Calculatrice
** File description:
** Main
*/

#include <memory>
#include "App.hpp"

std::string usage(const std::string &progName)
{
    std::string str;

    str.append("USAGE:\n");
    str.append("\t" + progName + " hostname port");
    return str;
}

int main(int ac, char **av)
{
    if (ac < 3) {
        std::cerr << usage(av[0]) << std::endl;
        return 84;
    }
    try {
        auto app = std::unique_ptr<Application>(new Application(1500, 960, "Zappy", av[1], av[2]));
        app->Run();
    } catch (const SocketError &e) {
        std::cerr << usage(av[0]) << std::endl;
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return EXIT_SUCCESS;
}