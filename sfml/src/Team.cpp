/*
** EPITECH PROJECT, 2019
** sfml
** File description:
** Team
*/

#include <iostream>
#include "Team.hpp"

Team::Team(const std::string &name)
: _name(name)
{

}

void Team::AddPlayer(int id, int pos_x, int pos_y, Player::Orientation ori, int level)
{
    this->_players.push_back(Player(id, pos_x, pos_y, ori, level));
}

const std::string &Team::getName()
{
    return (this->_name);
}

const std::vector<Player> &Team::getPlayers()
{
    return (this->_players);
}