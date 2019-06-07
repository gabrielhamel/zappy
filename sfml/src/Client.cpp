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
    this->_server.WaitData();
    this->_server.Read();
    this->_server.Write("GRAPHIC\n");
    this->_server.WaitData();
    this->Refresh();
}

void Client::Refresh()
{
    if (this->_server.HasData() == false)
        return;
    auto buff = Utils::extract(this->_server.Read());
    for (auto &cmd : buff)
        this->parseCommand(cmd);
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
    else if (toks[0] == "pnw")
        this->parsePnw(toks);
    else if (toks[0] == "pex")
        this->parsePex(toks);
    else if (toks[0] == "pdi")
        this->parsePdi(toks);
    else if (toks[0] == "ppo")
        this->parsePpo(toks);
    else if (toks[0] == "plv")
        this->parsePlv(toks);
}

const std::array<unsigned int, 2> &Client::GetMapSize() const
{
    return (this->_mapSize);
}

std::vector<std::vector<std::array<unsigned int, 7>>> *Client::GetMap()
{
    return (&this->_map);
}

std::vector<Team *> &Client::getTeams()
{
    return (this->_teams);
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
        this->_map[std::stoi(toks[2])][std::stoi(toks[1])][i - 3] = std::stoi(toks[i]);
}

void Client::parseTna(const std::vector<std::string> &toks)
{
    this->_teams.push_back(new Team(toks[1]));
}

void Client::parsePnw(const std::vector<std::string> &toks)
{
    for (auto &i : this->_teams)
        if (i->getName() == toks[6])
            i->AddPlayer(std::stoi(toks[1]), std::stoi(toks[2]), std::stoi(toks[3]), (Player::Orientation)std::stoi(toks[4]), std::stoi(toks[5]));
}

void Client::parsePex(const std::vector<std::string> &toks) // Pas sûr du comportement
{
    auto id = std::stoi(toks[1]);

    for (auto &i : this->_teams) {
        auto &players = i->getPlayers();
        for (auto player = players.begin(); player != players.end(); player++)
            if (player->getId() == id) {
                players.erase(player);
                return;
            }
    }
}

void Client::parsePdi(const std::vector<std::string> &toks)
{
    auto id = std::stoi(toks[1]);

    for (auto &i : this->_teams) {
        auto &players = i->getPlayers();
        for (auto player = players.begin(); player != players.end(); player++)
            if (player->getId() == id) {
                players.erase(player);
                return;
            }
    }
}

void Client::parsePpo(const std::vector<std::string> &toks)
{
    auto id = std::stoi(toks[1]);

    for (auto &i : this->_teams) {
        auto &players = i->getPlayers();
        for (auto player = players.begin(); player != players.end(); player++)
            if (player->getId() == id) {
                player->setPosition(std::stoi(toks[2]), std::stoi(toks[3]));
                player->setOrientation((Player::Orientation)std::stoi(toks[4]));
                return;
            }
    }
}

void Client::parsePlv(const std::vector<std::string> &toks)
{
    auto id = std::stoi(toks[1]);

    for (auto &i : this->_teams) {
        auto &players = i->getPlayers();
        for (auto player = players.begin(); player != players.end(); player++)
            if (player->getId() == id) {
                player->setLevel(std::stoi(toks[2]));
                return;
            }
    }
}
