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
        const std::array<int, 2> &getPosition() const;
        int getId() const;
        void setPosition(int x, int y);
        void setLevel(int level);
    private:
        int _id;
        std::array<int, 2> _pos;
        Player::Orientation _ori;
        int _level;
};