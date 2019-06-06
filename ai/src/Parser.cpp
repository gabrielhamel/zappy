/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Parser
*/

#include <getopt.h>
#include <exception>
#include <iostream>
#include "ParsingError.hpp"
#include "Parser.hpp"

static const struct option options[] = {
    {"help", no_argument, nullptr, zpy::Parser::HELP},
    {"port", required_argument, nullptr, zpy::Parser::PORT},
    {"name", required_argument, nullptr, zpy::Parser::NAME},
    {"machine", required_argument, nullptr, zpy::Parser::MACHINE},
    {nullptr, 0, nullptr, 0}
};

zpy::Parser::Parser(int ac, char **av)
: _help(false), _port(""), _name(""), _machine("localhost")
{
    int opt;
    int idx = 0;

    while ((opt = getopt_long(ac, av, "Hp:n:h:", options, &idx)) != -1) {
        switch (opt) {
            case HELP:
                this->_help = true;
                break;
            break;
            case PORT:
                this->_port = optarg;
            break;
            case NAME:
                this->_name = optarg;
            break;
            case MACHINE:
                this->_machine = optarg;
            break;
            default:
                throw zpy::ParsingError("Invalid parameters");
        }
    }
    checkParameters();
}

zpy::Parser::~Parser()
{

}

void zpy::Parser::checkParameters() const
{
    if (this->_help == true)
        return;
    if (this->_port == "" or
        this->_name == "" or
        this->_machine == "")
        throw zpy::ParsingError("Missing parameters");
}

bool zpy::Parser::hasHelp() const
{
    return this->_help;
}

std::string zpy::Parser::getHostname() const
{
    return this->_machine;
}

std::string zpy::Parser::getPort() const
{
    return this->_port;
}

std::string zpy::Parser::getTeam() const
{
    return this->_name;
}