/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Client
*/

#pragma once

#include <string>
#include <memory>
#include <vector>
#include "Server.hpp"

namespace zpy {

    class Client {
        public:
            Client(const std::string &hostname, const std::string &port, const std::string &team);
            ~Client();
        private:
            void login() const;
            std::string _hostname;
            std::string _port;
            std::string _team;
            std::unique_ptr<zpy::Server> _server;
    };

}