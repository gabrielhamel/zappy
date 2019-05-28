/*
** EPITECH PROJECT, 2019
** sfml
** File description:
** Team
*/

#pragma once

#include <string>
#include <vector>
#include "Player.hpp"

class Team {
    public:
        Team(const std::string &name);
        void AddPlayer(int id, int pos_x, int pos_y, Player::Orientation ori, int level);
        const std::string &getName();
        const std::vector<Player> &getPlayers();
    private:
        std::string _name;
        std::vector<Player> _players;
};