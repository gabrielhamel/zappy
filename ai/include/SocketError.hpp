/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** SocketError
*/

#pragma once

#include <exception>
#include <string>

namespace zpy {

    class SocketError : public std::exception {
        public:
            SocketError(const char *msg) : _msg(msg) {};
            SocketError(const std::string &msg) : _msg(msg.c_str()) {};
            const char *what() const throw () { return (_msg); }
        private:
            const char *_msg;
    };

}