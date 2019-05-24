/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Client
*/

#pragma once

#include <array>
#include <functional>
#include <unordered_map>
#include <vector>
#include "Server.hpp"

class Client {
	public:
		Client(const std::string &hostname, const std::string &port);
	private:
        Server _server;
        std::array<unsigned int, 2> _mapSize;
        unsigned int _time;
        std::vector<std::vector<std::array<unsigned int, 7>>> _map;
        std::vector<std::string> _teamsNames;
        void parseCommand(const std::vector<std::string> &toks);
        void parseMsz(const std::vector<std::string> &toks);
        void parseSgt(const std::vector<std::string> &toks);
        void parseBct(const std::vector<std::string> &toks);
        void parseTna(const std::vector<std::string> &toks);
};
