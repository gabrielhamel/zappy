/*
** EPITECH PROJECT, 2019
** sfml
** File description:
** Player
*/

#include <iostream>
#include "Ia.hpp"

Player::Player(int id, int pos_x, int pos_y, Player::Orientation ori, int level)
: _id(id), _pos({pos_x, pos_y}), _ori(ori), _level(level)
{
    this->_inventory[0] = 0;
    this->_inventory[1] = 0;
    this->_inventory[2] = 0;
    this->_inventory[3] = 0;
    this->_inventory[4] = 0;
    this->_inventory[5] = 0;
    this->_inventory[6] = 0;
}

Player::Orientation Player::getOrientation() const
{
    return (this->_ori);
}

std::string Player::getStrOrientation() const
{
    switch (this->_ori) {
        case N:
            return "North";
        case E:
            return "East";
        case S:
            return "South";
        case W:
            return "Weast";
    }
    return "";
}

void Player::setOrientation(Player::Orientation ori)
{
    this->_ori = ori;
}

const std::array<int, 2> &Player::getPosition() const
{
    return (this->_pos);
}

int Player::getId() const
{
    return (this->_id);
}

void Player::setPosition(int x, int y)
{
    this->_pos[0] = x;
    this->_pos[1] = y;
}

void Player::setLevel(int level)
{
    this->_level = level;
}

int Player::getLevel() const
{
    return this->_level;
}

bool operator==(const Player &a, const Player &b)
{
    return a.getId() == b.getId();
}