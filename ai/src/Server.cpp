/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Server
*/

#include <sys/select.h>
#include <unistd.h>
#include <sys/timeb.h>
#include "Server.hpp"

zpy::Server::Server(const std::string &hostname, const std::string &port)
: _refreshTime(1000), _ellapsed(0)
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

void zpy::Server::writeData(const std::string &text)
{
    write(this->_fd, text.c_str(), text.length());
}

std::string zpy::Server::readData()
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

void zpy::Server::setRefreshTime(float millisec)
{
    this->_refreshTime = millisec * 1000.0f;
}

bool zpy::Server::hasData()
{
    struct timeb start = {0, 0, 0, 0};
    ftime(&start);
    struct timeb end = {0, 0, 0, 0};
    fd_set rfds;
    struct timeval tv = {0, this->_refreshTime};
    int retval;
    FD_ZERO(&rfds);
    FD_SET(this->_fd, &rfds);
    retval = select(FD_SETSIZE, &rfds, NULL, NULL, &tv);
    ftime(&end);
    this->_ellapsed = 1000 * (end.time - start.time) + (end.millitm - start.millitm);
    if (retval)
        return true;
    return false;
}

unsigned int zpy::Server::getEllapsedTime() const
{
    return this->_ellapsed;
}

void zpy::Server::waitData()
{
    struct timeb start = {0, 0, 0, 0};
    ftime(&start);
    fd_set rfds;
    struct timeb end = {0, 0, 0, 0};
    FD_ZERO(&rfds);
    FD_SET(this->_fd, &rfds);
    select(FD_SETSIZE, &rfds, NULL, NULL, NULL);
    ftime(&end);
    this->_ellapsed = 1000 * (end.time - start.time) + (end.millitm - start.millitm);
}