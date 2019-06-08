/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** SocketError
*/

#ifndef SOCKETERROR_HPP
#define SOCKETERROR_HPP

#include <exception>
#include <string>

class SocketError : public std::exception {
    public:
        SocketError(const char *msg) : _msg(msg) {};
        SocketError(const std::string &msg) : _msg(msg.c_str()) {};
        const char* what() const throw () { return (_msg); }
    private:
        const char *_msg;
};

#endif