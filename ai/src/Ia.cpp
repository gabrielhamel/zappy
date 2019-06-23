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
: _cli(cli)
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
}

void zpy::Ia::run()
{
    usleep(50000);
    while (1) {
        this->_cli->resfresh();
        while (this->_cli->haveBroadcast())
            std::cout << this->_cli->getBroadcast().msg << std::endl;
        this->getObject(zpy::Client::Thystame());
    }
}
