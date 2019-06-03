/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Client
*/

#include "Client.hpp"

zpy::Client::Client(const std::string &hostname, const std::string &port, const std::string &team)
: _hostname(hostname),
_port(port),
_team(team),
_server(std::unique_ptr<zpy::Server>(new zpy::Server(hostname, port)))
{

}

zpy::Client::~Client()
{

}