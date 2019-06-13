/*
** EPITECH PROJECT, 2019
** sfml
** File description:
** Team
*/

#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Ia.hpp"

class Team {
    public:
        Team(const std::string &name);
        ~Team();
        Player &AddPlayer(int id, int pos_x, int pos_y, Player::Orientation ori, int level);
        const std::string &getName();
        std::vector<Player> &getPlayers();
        const sf::Color &getColor() const;
        void setScale(float scale);
        sf::Sprite _spr;
        void setTexture(sf::Texture *tex);
        bool set;
    private:
        sf::Color _color;
        std::string _name;
        std::vector<Player> _players;
        sf::Texture *_tex;

};
