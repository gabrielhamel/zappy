/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** ParsingError
*/

#pragma once

#include <exception>
#include <string>

namespace zpy {

    class ParsingError : public std::exception {
        public:
            ParsingError(const char *msg) : _msg(msg) {};
            ParsingError(const std::string &msg) : _msg(msg.c_str()) {};
            const char *what() const throw () { return (_msg); }
        private:
            const char *_msg;
    };

}