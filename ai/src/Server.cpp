/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Server
*/

#include <sys/select.h>
#include "Server.hpp"

zpy::Server::Server(const std::string &hostname, const std::string &port)
{
    auto hosts = gethostbyname(hostname.c_str());

    if (hosts == nullptr)
        throw SocketError("Invalid hostname");
    if (!hosts->h_addr_list || !hosts->h_addr_list[0])
        throw SocketError("Cannot find addresses");
    memset(this->addr.sin_zero, 0, 8);
    this->addr.sin_family = AF_INET;
    memcpy(&this->addr.sin_addr.s_addr, hosts->h_addr_list[0], 4);
    this->addr.sin_port = htons(strtol(port.c_str(), nullptr, 10));
    this->_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_fd == -1)
        throw SocketError("Cannot create socket");
    if (connect(this->_fd, (struct sockaddr *)&this->addr, (socklen_t)sizeof(struct sockaddr_in)) == -1)
        throw SocketError("Cannot connect");
}

zpy::Server::~Server()
{
    close(this->_fd);
}

void zpy::Server::Write(const std::string &text)
{
    write(this->_fd, text.c_str(), text.length());
}

std::string zpy::Server::Read()
{
    std::string str;
    ssize_t res;
    char buff[READ_SIZE] = {0};

    res = read(this->_fd, buff, READ_SIZE);
    if (res == 0)
        throw SocketError("Server disconnected");
    str.append(buff);
    return str;
}

bool zpy::Server::HasData()
{
    fd_set rfds;
    struct timeval tv = {0, 0};
    int retval;

    FD_ZERO(&rfds);
    FD_SET(this->_fd, &rfds);
    tv.tv_usec = 10000;
    retval = select(FD_SETSIZE, &rfds, NULL, NULL, &tv);
    if (retval)
        return true;
    return false;
}

void zpy::Server::WaitData()
{
    fd_set rfds;

    FD_ZERO(&rfds);
    FD_SET(this->_fd, &rfds);
    select(FD_SETSIZE, &rfds, NULL, NULL, NULL);
}