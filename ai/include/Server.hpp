/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Server
*/

#pragma once

#define READ_SIZE 100000

#include <netdb.h>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <string>
#include "SocketError.hpp"

namespace zpy {

    class Server {
        public:
            Server(const std::string &hostname, const std::string &port);
            ~Server();
            void setRefreshTime(float millisec);
            unsigned int getEllapsedTime() const;
            void writeData(const std::string &text);
            std::string readData();
            bool hasData();
            void waitData();
        private:
            struct sockaddr_in addr;
            int _fd;
            unsigned int _refreshTime;
            unsigned int _ellapsed;
    };

}