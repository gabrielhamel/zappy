/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Ia
*/

#include <algorithm>
#include <iterator>
#include <cmath>
#include "Ai.hpp"

static const int incantations[7][7] = {
    1, 1, 0, 0, 0, 0, 0,
    2, 1, 1, 1, 0, 0, 0,
    2, 2, 0, 1, 0, 2, 0,
    4, 1, 1, 2, 0, 1, 0,
    4, 1, 2, 1, 3, 0, 0,
    6, 1, 2, 3, 0, 1, 0,
    6, 2, 2, 2, 2, 2, 1
};

zpy::Ia::Ia(std::shared_ptr<zpy::Client> cli)
: _cli(cli), _inv(9, 0, 0, 0, 0, 0, 0), _level(1), _readyIncant(false)
{
    this->run();
}

void zpy::Ia::randomForward()
{
    int direction = rand() % 4 - 1;

    if (direction == -1)
        this->_cli->left();
    else
        for (int i = 0; i < direction; i++)
            this->_cli->right();
    this->_cli->forward();
}

bool zpy::Ia::haveObject(const zpy::Client::Tile *tile, const zpy::Client::Object &object)
{
    auto str = object.str();

    if (str == "player")
        return tile->player ? true : false;
    else if (str == "food")
        return tile->food ? true : false;
    else if (str == "linemate")
        return tile->linemate ? true : false;
    else if (str == "deraumere")
        return tile->deraumere ? true : false;
    else if (str == "sibur")
        return tile->sibur ? true : false;
    else if (str == "mendiane")
        return tile->mendiane ? true : false;
    else if (str == "phiras")
        return tile->phiras ? true : false;
    else if (str == "thystame")
        return tile->thystame ? true : false;
    return false;
}

zpy::Client::Tile *zpy::Ia::getTileWithObject(const std::vector <zpy::Client::Tile *> &arr, const zpy::Client::Object &object)
{
    for (size_t i = 0; i < arr.size(); i++)
        if (this->haveObject(arr[i], object))
            return arr[i];
    return nullptr;
}

void zpy::Ia::getObject(const zpy::Client::Object &object)
{
    zpy::Client::Tile *ptr = nullptr;
    int v;

    while (ptr == nullptr) {
        this->_cli->resfresh();
        auto look = this->_cli->look();
        ptr = getTileWithObject(look, object);
        if (ptr == nullptr)
            this->randomForward();
        auto it = std::find(look.begin(), look.end(), ptr);
        v = std::distance(look.begin(), it);
    }
    int y = std::sqrt(v);
    int x = -1 * y * y - y + v;
    for (int i = 0; i < y; i++)
        this->_cli->forward();
    if (x < 0) {
        this->_cli->left();
        x *= -1;
    }
    else if (x > 0)
        this->_cli->right();
    for (int i = 0; i < x; i++)
        this->_cli->forward();
    this->_cli->take(object);
    this->_inv = this->_cli->inventory();
}

void zpy::Ia::takeObject(const zpy::Client::Object &object, std::size_t nb)
{
    for (std::size_t i = 0; i < nb; i++) {
        this->_cli->resfresh();
        this->getObject(object);
    }
}

void zpy::Ia::prepareNextIncantation()
{
    if (this->_inv.linemate < incantations[this->_level - 1][1])
        this->takeObject(zpy::Client::Linemate(), incantations[this->_level - 1][1] - this->_inv.linemate);
    if (this->_inv.deraumere < incantations[this->_level - 1][2])
        this->takeObject(zpy::Client::Deraumere(), incantations[this->_level - 1][2] - this->_inv.deraumere);
    if (this->_inv.sibur < incantations[this->_level - 1][3])
        this->takeObject(zpy::Client::Sibur(), incantations[this->_level - 1][3] - this->_inv.sibur);
    if (this->_inv.mendiane < incantations[this->_level - 1][4])
        this->takeObject(zpy::Client::Mendiane(), incantations[this->_level - 1][4] - this->_inv.mendiane);
    if (this->_inv.phiras < incantations[this->_level - 1][5])
        this->takeObject(zpy::Client::Phiras(), incantations[this->_level - 1][5] - this->_inv.phiras);
    if (this->_inv.thystame < incantations[this->_level - 1][6])
        this->takeObject(zpy::Client::Thystame(), incantations[this->_level - 1][6] - this->_inv.thystame);
    this->_readyIncant = true;
}

void zpy::Ia::incantation()
{
    if (this->_cli->incantation()) {
        this->_level++;
        this->_readyIncant = false;
    }
}

void zpy::Ia::run()
{
    usleep(50000);
    while (1) {
        this->_cli->resfresh();
        while (this->_cli->haveBroadcast())
            std::cout << this->_cli->getBroadcast().msg << std::endl;
        if (_readyIncant == false)
            prepareNextIncantation();
        else
            incantation();
    }
}
