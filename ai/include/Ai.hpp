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
    };

}
