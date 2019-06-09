/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Message
*/

#include "Client.hpp"

zpy::Client::Message::Message(const std::string &msg, unsigned int direction)
: msg(msg), direction(direction)
{

}

zpy::Client::Message::Message(const zpy::Client::Message &copy)
: msg(copy.msg), direction(copy.direction)
{

}

zpy::Client::Message &zpy::Client::Message::operator=(const zpy::Client::Message &src)
{
    this->msg = src.msg;
    this->direction = src.direction;
    return *this;
}