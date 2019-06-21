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
    if (this->_server->hasData()) {
        auto buff = Utils::extract(this->_server->readData());
        for (auto &cmd : buff)
            this->parseCommand(cmd);
    }
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
    else if (toks[0] == "message")
        this->_broadcast.push_back(Message(toks[2], std::stoi(toks[1])));
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

std::vector<std::string> zpy::Client::commandEnd()
{
    std::vector<std::string> res;
    do {
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
        res = this->selectGoodAnswer(buff);
    } while (res.size() == 0);
    return res;
}

void zpy::Client::setRefreshTime(float millisec)
{
    this->_server->setRefreshTime(millisec);
}

unsigned int zpy::Client::getEllapsedTime() const
{
    return this->_server->getEllapsedTime();
}

std::vector<std::string> zpy::Client::selectGoodAnswer(const std::vector<std::vector<std::string>> &cmd)
{
    for (auto line : cmd)
        if (line[0] != "message" && line[0] != "dead" && line[0] != "eject")
            return line;
    return std::vector<std::string>();
}

void zpy::Client::forward()
{
    auto command = "Forward\n";
    std::cout << "client: " << command;

    this->commandStart();
    this->_server->writeData(command);
    this->commandEnd();
}

void zpy::Client::right()
{
    auto command = "Right\n";
    std::cout << "client: " << command;

    this->commandStart();
    this->_server->writeData(command);
    this->commandEnd();
}

void zpy::Client::left()
{
    auto command = "Left\n";
    std::cout << "client: " << command;

    this->commandStart();
    this->_server->writeData(command);
    this->commandEnd();
}

zpy::Client::Response zpy::Client::take(const zpy::Client::Object &object)
{
    auto command = "Take " + object.str() + "\n";
    std::cout << "client: " << command;

    this->commandStart();
    this->_server->writeData(command);
    auto buff = this->commandEnd();
    if (buff[0] == "ok")
        return zpy::Client::Response::OK;
    return zpy::Client::Response::KO;
}

zpy::Client::Response zpy::Client::set(const zpy::Client::Object &object)
{
    auto command = "Set " + object.str() + "\n";
    std::cout << "client: " << command;

    this->commandStart();
    this->_server->writeData(command);
    auto buff = this->commandEnd();
    if (buff[0] == "ok")
        return zpy::Client::Response::OK;
    return zpy::Client::Response::KO;
}

zpy::Client::Inventory zpy::Client::inventory()
{
    auto command = "Inventory\n";
    std::cout << "client: " << command;

    this->commandStart();
    this->_server->writeData(command);
    auto buff = this->commandEnd();
    zpy::Client::Inventory inv(
        std::stoi(buff[2]),
        std::stoi(buff[4]),
        std::stoi(buff[6]),
        std::stoi(buff[8]),
        std::stoi(buff[10]),
        std::stoi(buff[12]),
        std::stoi(buff[14]));
    return inv;
}

std::vector <zpy::Client::Tile *> zpy::Client::look(void)
{
    auto command = "Look\n";
    std::cout << "client: " << command;
    std::vector <zpy::Client::Tile *> tiles;
    std::vector <std::string>::iterator buffIt;
    std::vector <zpy::Client::Tile *>::iterator tileIt;

    this->commandStart();
    this->_server->writeData(command);
    auto buff = this->commandEnd();
    tiles.push_back(new Tile(false, false, false, false, false, false, false, false));
    for (buffIt = buff.begin(); buffIt != buff.end(); buffIt++) {
        if ((*buffIt).find("player") != std::string::npos)
            (*tileIt)->player = true;
        if ((*buffIt).find("food") != std::string::npos)
            (*tileIt)->food = true;
        if ((*buffIt).find("linemate") != std::string::npos)
            (*tileIt)->linemate = true;
        if ((*buffIt).find("deraumere") != std::string::npos)
            (*tileIt)->deraumere = true;
        if ((*buffIt).find("sibur") != std::string::npos)
            (*tileIt)->sibur = true;
        if ((*buffIt).find("mendiane") != std::string::npos)
            (*tileIt)->mendiane = true;
        if ((*buffIt).find("phiras") != std::string::npos)
            (*tileIt)->phiras = true;
        if ((*buffIt).find("thystame") != std::string::npos)
            (*tileIt)->thystame = true;
        if ((*buffIt).find(",") != std::string::npos) {
            tiles.push_back(new Tile(false, false, false, false, false, false, false, false));
            tileIt++;
        }
    }
    return (tiles);
}

void zpy::Client::broadcast(const std::string &msg)
{
    auto command = "Broadcast " + msg + "\n";
    std::cout << "client: " << command;

    this->commandStart();
    this->_server->writeData(command);
    this->commandEnd();
}

bool zpy::Client::haveBroadcast()
{
    if (this->_broadcast.size() != 0)
        return true;
    return false;
}

zpy::Client::Message zpy::Client::getBroadcast()
{
    auto msg = this->_broadcast.front();

    this->_broadcast.pop_front();
    return msg;
}

void zpy::Client::resfresh()
{
    this->commandStart();
}


void zpy::Client::connectNbr()
{
    auto command = "Connect_nbr \n";
    std::cout << "client: " << command;

    this->commandStart();
    this->_server->writeData(command);
    auto buff = this->commandEnd();
    this->_remainingPlayer = std::stoul(buff[0], nullptr, 10);
}
