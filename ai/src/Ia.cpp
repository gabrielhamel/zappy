/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Ia
*/

#include "Ia.hpp"

zpy::Ia::Ia(std::shared_ptr<zpy::Client> cli)
: _cli(cli)
{
    this->run();
}

void zpy::Ia::run()
{
    while (1) {
        this->_cli->resfresh();
        this->_cli->forward();
    }
}
