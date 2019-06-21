/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Application
*/

#include <iostream>
#include "Ai.hpp"
#include "Application.hpp"

zpy::Application::Application(int ac, char **av)
: _parser(std::unique_ptr<zpy::Parser>(new zpy::Parser(ac, av)))
{
    if (this->_parser->hasHelp() == true)
        std::cout << zpy::Application::usage(av[0]) << std::endl;
    else {
        this->_client = std::shared_ptr<zpy::Client>(new zpy::Client(this->_parser->getHostname(),
                                                                this->_parser->getPort(),
                                                                this->_parser->getTeam()));
        this->run();
    }
}

zpy::Application::~Application()
{

}

std::string zpy::Application::usage(const std::string &progName)
{
    std::string str;

    str.append("USAGE: " +  progName + " -p port -n name -h machine\n");
    str.append("\tport\tis the port number\n");
    str.append("\tname\tis the name of the team\n");
    str.append("\tmachine\tis the name of the machine; localhost by default");
    return str;
}

void zpy::Application::run()
{
    auto ia = zpy::Ia(this->_client);
}
