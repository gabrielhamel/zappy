/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Client
*/

#include <algorithm>
#include <iostream>
#include "Client.hpp"
#include "Utils.hpp"

Client::Client(const std::string &hostname, const std::string &port)
: _server(hostname, port)
{
    this->_time = 0;
    this->_mapSize[0] = 0;
    this->_mapSize[1] = 0;
    this->_server.ReadLine();
    this->_server.Write("GRAPHIC\n");
    // std::cout << this->_server.Read();
}

void Client::parseCommand(const std::vector<std::string> &toks)
{
    if (toks[0] == "msz")
        this->parseMsz(toks);
    else if (toks[0] == "sgt")
        this->parseSgt(toks);
    else if (toks[0] == "bct")
        this->parseBct(toks);
    else if (toks[0] == "tna")
        this->parseTna(toks);
}

void Client::parseMsz(const std::vector<std::string> &toks)
{
    this->_mapSize[0] = std::stoi(toks[1]);
    this->_mapSize[1] = std::stoi(toks[2]);
    this->_map = std::vector<std::vector<std::array<unsigned int, 7>>>(this->_mapSize[1]);
    for (unsigned int i = 0; i < this->_mapSize[1]; i++)
        this->_map[i] = std::vector<std::array<unsigned int, 7>>(this->_mapSize[0]);
}

void Client::parseSgt(const std::vector<std::string> &toks)
{
    this->_time = std::stoi(toks[1]);
}

void Client::parseBct(const std::vector<std::string> &toks)
{
    for (int i = 3; i < 10; i++)
        this->_map[std::stoi(toks[2]) - 1][std::stoi(toks[1]) - 1][0] = std::stoi(toks[i]);
}

void Client::parseTna(const std::vector<std::string> &toks)
{
    auto it = std::find(this->_teamsNames.begin(), this->_teamsNames.end(), toks[1]);

    if (it == this->_teamsNames.end())
        this->_teamsNames.push_back(toks[1]);
}