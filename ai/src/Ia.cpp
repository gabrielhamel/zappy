/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Ia
*/

#include "Ai.hpp"

zpy::Ia::Ia(std::shared_ptr<zpy::Client> cli)
: _cli(cli)
{
    this->run();
}

void zpy::Ia::run()
{
    usleep(50000);
    this->_cli->left();
    while (1) {
        this->_cli->resfresh();
        while (this->_cli->haveBroadcast())
            std::cout << this->_cli->getBroadcast().msg << std::endl;
        this->_cli->forward();
        // this->_cli->connectNbr();
        // this->_cli->right();
        this->_cli->inventory();
        std::vector <zpy::Client::Tile *> tiles = this->_cli->look();

        std::cout << "****test tiles 1 : " << tiles[0]->food << std::endl;
        std::cout << "****test tiles 2 : " << tiles[1]->food << std::endl;
        //this->_cli->take(zpy::Client::Food());
        // auto inv = this->_cli->inventory();
        // std::cout << this->_cli->getRemainingPlayer() << std::endl;
    }
}
