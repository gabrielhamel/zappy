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
#include "Team.hpp"

class Client {
    public:
        Client(const std::string &hostname, const std::string &port);
        void Refresh();
        const std::array<unsigned int, 2> &GetMapSize() const;
        std::vector<std::vector<std::array<unsigned int, 7>>> *GetMap();
        std::vector<Team *> &getTeams();
    private:
        Server _server;
        std::array<unsigned int, 2> _mapSize;
        unsigned int _time;
        std::vector<std::vector<std::array<unsigned int, 7>>> _map;
        std::vector<Team *> _teams;
        void parseCommand(const std::vector<std::string> &toks);
        void parseMsz(const std::vector<std::string> &toks);
        void parseSgt(const std::vector<std::string> &toks);
        void parseBct(const std::vector<std::string> &toks);
        void parseTna(const std::vector<std::string> &toks);
        void parsePnw(const std::vector<std::string> &toks);
        void parsePex(const std::vector<std::string> &toks);
        void parsePdi(const std::vector<std::string> &toks);
        void parsePpo(const std::vector<std::string> &toks);
        void parsePlv(const std::vector<std::string> &toks);
};