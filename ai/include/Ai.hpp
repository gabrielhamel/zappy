/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Ia
*/

#pragma once

#include "Client.hpp"

namespace zpy {

    class Ia {
        public:
            Ia(std::shared_ptr<zpy::Client> cli);
        private:
            std::shared_ptr<zpy::Client> _cli;
            void run();
            void randomForward();
            void getObject(const zpy::Client::Object &object);
            bool haveObject(const zpy::Client::Tile *tile, const zpy::Client::Object &object);
            zpy::Client::Tile *getTileWithObject(const std::vector <zpy::Client::Tile *> &arr, const zpy::Client::Object &object);
            void takeObject(const zpy::Client::Object &object, std::size_t nb = 1);
            void setObject(const zpy::Client::Object &object, std::size_t nb = 1);
            bool prepareNextIncantation();
            void incantation();
            void prepareTile();
        private:
            zpy::Client::Inventory _inv;
            int _level;
            bool _readyIncant;
    };

}
