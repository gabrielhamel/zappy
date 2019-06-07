/*
** EPITECH PROJECT, 2019
** sfml
** File description:
** Player
*/

#include <iostream>
#include "Player.hpp"

Player::Player(int id, int pos_x, int pos_y, Player::Orientation ori, int level)
: _id(id), _pos({pos_x, pos_y}), _ori(ori), _level(level)
{

}

Player::Orientation Player::getOrientation() const
{
    return (this->_ori);
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
