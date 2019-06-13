/*
** EPITECH PROJECT, 2019
** sfml
** File description:
** Team
*/

#include <iostream>
#include "Team.hpp"
#include <ctime>

Team::Team(const std::string &name)
: _name(name)
{
    this->set = false;
}

Team::~Team()
{
    std::cout << "Team destroy or copied" << std::endl;
}

Player &Team::AddPlayer(int id, int pos_x, int pos_y, Player::Orientation ori, int level)
{
    this->_players.push_back(Player(id, pos_x, pos_y, ori, level));
    return this->_players.back();
}

void Team::setScale(float scale)
{
    this->_spr.setScale(scale / 1.5f, scale / 1.5f);
}

const std::string &Team::getName()
{
    return (this->_name);
}

std::vector<Player> &Team::getPlayers()
{
    return (this->_players);
}

const sf::Color &Team::getColor() const
{
    return (this->_color);
}

void Team::setTexture(sf::Texture *tex)
{
    this->_tex = tex;
    this->_color = sf::Color(rand() % 256, rand() % 256, rand() % 256);
    this->_spr.setTexture(*this->_tex, true);
    this->_spr.setTextureRect(sf::IntRect(sf::Vector2i(128, 0), sf::Vector2i(16, 16)));
    this->_spr.setScale(1.f / 1.5f, 1.f / 1.5f);
    this->_spr.setColor(this->_color);
    this->_spr.setOrigin(8, 8);
    this->set = true;
}
