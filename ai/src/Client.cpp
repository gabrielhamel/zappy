/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Client
*/

#include "Client.hpp"
#include "Utils.hpp"

zpy::Client::Client(const std::string &hostname, const std::string &port, const std::string &team)
: _hostname(hostname),
_port(port),
_team(team),
_server(std::unique_ptr<zpy::Server>(new zpy::Server(hostname, port))),
_mapSize({0, 0}),
_line(0)
{
    this->_server->writeData(this->_team + "\n");
    this->_server->waitData();
    auto buff = Utils::extract(this->_server->readData());
    for (auto &cmd : buff)
        this->parseCommand(cmd);
}

zpy::Client::~Client()
{

}

void zpy::Client::parseCommand(const std::vector<std::string> &toks)
{
    this->_line++;
    if (toks[0] == "dead")
        throw SocketError("Player death");
    else if (toks[0] == "ko" && this->_line == 2)
        throw SocketError("No available place");
    else if (this->_line == 2)
        this->parseRemainingClient(toks);
    else if (this->_line == 3)
        this->parseMapSize(toks);
}

void zpy::Client::parseRemainingClient(const std::vector<std::string> &toks)
{
    this->_remainingPlayer = std::stoi(toks[0]);
}

void zpy::Client::parseMapSize(const std::vector<std::string> &toks)
{
    this->_mapSize[0] = std::stoi(toks[0]);
    this->_mapSize[1] = std::stoi(toks[1]);
}

void zpy::Client::commandStart()
{
    if (this->_server->hasData() == false)
        return;
    auto buff = Utils::extract(this->_server->readData());
    for (auto &cmd : buff)
        this->parseCommand(cmd);
}

std::vector<std::vector<std::string>> zpy::Client::commandEnd()
{
    this->_server->waitData();
    auto data = this->_server->readData();
    auto buff = Utils::extract(data);
    for (auto &cmd : buff) {
        this->parseCommand(cmd);
        std::cout << "server:";
        for (auto &i : cmd)
            std::cout << " " << i;
        std::cout << std::endl;
    }
    return buff;
}

void zpy::Client::setRefreshTime(float millisec)
{
    this->_server->setRefreshTime(millisec);
}

unsigned int zpy::Client::getEllapsedTime() const
{
    return this->_server->getEllapsedTime();
}

void zpy::Client::forward()
{
    auto command = "Forward\n";
    std::cout << "client: " << command;

    this->commandStart();
    this->_server->writeData(command);
    auto buff = this->commandEnd();
}

void zpy::Client::right()
{
    auto command = "Right\n";
    std::cout << "client: " << command;

    this->commandStart();
    this->_server->writeData(command);
    auto buff = this->commandEnd();
}

void zpy::Client::left()
{
    auto command = "Left\n";
    std::cout << "client: " << command;

    this->commandStart();
    this->_server->writeData(command);
    auto buff = this->commandEnd();
}