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