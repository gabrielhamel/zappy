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
    usleep(50000);
    while (1) {
        this->_cli->resfresh();
        while (this->_cli->haveBroadcast())
            std::cout << this->_cli->getBroadcast().msg << std::endl;
        this->_cli->left();
        this->_cli->connectNbr();
        this->_cli->right();
        // std::cout << this->_cli->getRemainingPlayer() << std::endl;
    }
}
