/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Client
*/

#pragma once

#include <memory>
#include <list>
#include "Utils.hpp"
#include "Server.hpp"

namespace zpy {

    class Client {
        public:
            /*
            ***
            */
            enum Response {
                KO,
                OK
            };
            /*
            ** Broadcast message
            */
            class Message {
                public:
                    Message(const std::string &msg, unsigned int direction);
                    Message(const zpy::Client::Message &copy);
                    zpy::Client::Message &operator=(const zpy::Client::Message &src);
                    std::string msg;
                    unsigned int direction;
            };
            /*
            ** Inventory
            */
            class Inventory {
                public:
                    Inventory(
                        int food,
                        int linemate,
                        int deraumere,
                        int sibur,
                        int mendiane,
                        int phiras,
                        int thystame);
                    int food;
                    int linemate;
                    int deraumere;
                    int sibur;
                    int mendiane;
                    int phiras;
                    int thystame;
            };
            /*
            ** Tile
            */
            class Tile {
                public:
                    Tile(
                        unsigned int player,
                        unsigned int food,
                        unsigned int linemate,
                        unsigned int deraumere,
                        unsigned int sibur,
                        unsigned int mendiane,
                        unsigned int phiras,
                        unsigned int thystame);
                    unsigned int player;
                    unsigned int food;
                    unsigned int linemate;
                    unsigned int deraumere;
                    unsigned int sibur;
                    unsigned int mendiane;
                    unsigned int phiras;
                    unsigned int thystame;
            };
            /*
            ** All objects
            */
            class Object {
                public:
                    virtual ~Object() = default;
                    virtual std::string str() const = 0;
                    virtual unsigned int order() const = 0;
            };

            class Food : public Object {
                public:
                    std::string str() const { return "food"; }
                    unsigned int order() const { return 0; }
            };

            class Linemate : public Object {
                public:
                    std::string str() const { return "linemate"; }
                    unsigned int order() const { return 1; }
            };

            class Deraumere : public Object {
                public:
                    std::string str() const { return "deraumere"; }
                    unsigned int order() const { return 2; }
            };

            class Sibur : public Object {
                public:
                    std::string str() const { return "sibur"; }
                    unsigned int order() const { return 3; }
            };

            class Mendiane : public Object {
                public:
                    std::string str() const { return "mendiane"; }
                    unsigned int order() const { return 4; }
            };

            class Phiras : public Object {
                public:
                    std::string str() const { return "phiras"; }
                    unsigned int order() const { return 5; }
            };

            class Thystame : public Object {
                public:
                    std::string str() const { return "thystame"; }
                    unsigned int order() const { return 6; }
            };

            class Player : public Object {
                public:
                    std::string str() const { return "player"; }
                    unsigned int order() const { return 666; }
            };
            /*
            ** Connect the player, select the team and get size of map
            */
            Client(const std::string &hostname, const std::string &port, const std::string &team);
            ~Client();
            /*
            ** Set the refresh rate in milliseconds for getting data from server
            */
            void setRefreshTime(float millisec);
            /*
            ** Get the ellapsed time in milliseconds of the last command
            */
            unsigned int getEllapsedTime() const;
            /*
            ** All commands of client
            */
            void forward();
            void right();
            void left();
            void resfresh();
            zpy::Client::Response take(const zpy::Client::Object &object);
            zpy::Client::Response set(const zpy::Client::Object &object);
            zpy::Client::Inventory inventory();
            std::vector <zpy::Client::Tile *> look();
            void broadcast(const std::string &msg);
            bool haveBroadcast();
            zpy::Client::Message getBroadcast();
            void connectNbr();
            unsigned int getRemainingPlayer() const { return _remainingPlayer; }
            bool incantation();
        private:
            std::vector<std::string> selectGoodAnswer(const std::vector<std::vector<std::string>> &cmd);
            void commandStart();
            std::vector<std::string> commandEnd();
            void parseCommand(const std::vector<std::string> &toks);
            void parseRemainingClient(const std::vector<std::string> &toks);
            void parseMapSize(const std::vector<std::string> &toks);
            std::string _hostname;
            std::string _port;
            std::string _team;
            std::unique_ptr<zpy::Server> _server;
            std::array<unsigned int, 2> _mapSize;
            unsigned int _line;
            unsigned short _lvl;
            unsigned int _remainingPlayer;
            std::list<zpy::Client::Message> _broadcast;
    };

}
