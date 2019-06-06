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
#include "Utils.hpp"
#include "Server.hpp"

namespace zpy {

    class Client {
        public:
            /*
            ** Connect the player, select the team and get size of map
            */
            Client(const std::string &hostname, const std::string &port, const std::string &team);
            ~Client();
            /*
            ** Set the refresh rate in milliseconds for getting data from server
            */
            void setRefreshTime(float millisec);
            /*
            ** Get the ellapsed time in milliseconds of the last command
            */
            unsigned int getEllapsedTime() const;
            void forward();
            void right();
            void left();
        private:
            void commandStart();
            std::vector<std::vector<std::string>> commandEnd();
            void parseCommand(const std::vector<std::string> &toks);
            void parseRemainingClient(const std::vector<std::string> &toks);
            void parseMapSize(const std::vector<std::string> &toks);
            std::string _hostname;
            std::string _port;
            std::string _team;
            std::unique_ptr<zpy::Server> _server;
            std::array<unsigned int, 2> _mapSize;
            unsigned int _line;
            unsigned int _remainingPlayer;
    };

}