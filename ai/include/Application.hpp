/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Application
*/

#pragma once

#include <string>
#include "Client.hpp"
#include "Parser.hpp"

namespace zpy {

    class Application {
        public:
            Application(int ac, char **av);
            ~Application();
            static std::string usage(const std::string &progName);
        private:
            void run();
            std::unique_ptr<zpy::Parser> _parser;
            std::unique_ptr<zpy::Client> _client;
    };

}