/*
** EPITECH PROJECT, 2019
** sfml
** File description:
** Player
*/

#pragma once

#include <array>

class Player {
    public:
        enum Orientation {
            N = 1,
            E,
            S,
            W
        };
        Player(int id, int pos_x, int pos_y, Player::Orientation ori, int level);
        Player::Orientation getOrientation() const;
        void setOrientation(Player::Orientation ori);
        const std::array<int, 2> &getPosition() const;
        std::string getStrOrientation() const;
        int getId() const;
        void setPosition(int x, int y);
        void setLevel(int level);
        int getLevel() const;
        std::array<unsigned int, 7> _inventory;
    private:
        int _id;
        std::array<int, 2> _pos;
        Player::Orientation _ori;
        int _level;
};

bool operator==(const Player &a, const Player &b);