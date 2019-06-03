/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Parser
*/

#pragma once

#include <string>

namespace zpy {

    class Parser {
        public:
            enum Type {
                HELP = 'H',
                PORT = 'p',
                NAME = 'n',
                MACHINE = 'h'
            };
            Parser(int ac, char **av);
            ~Parser();
            bool hasHelp() const;
            std::string getHostname() const;
            std::string getPort() const;
            std::string getTeam() const;
        private:
            void checkParameters() const;
            bool _help;
            std::string _port;
            std::string _name;
            std::string _machine;
    };

}