/*
** EPITECH PROJECT, 2019
** sfml
** File description:
** Render
*/

#include "Render.hpp"
#include <iostream>

Render::Render()
{
    this->_grass.setPosition(0, 0);
    this->_scale = 1;
    this->_camera.x = 1;
    this->_camera.y = 1;
}

void Render::SetSize(const std::array<unsigned int, 2> &size)
{
    this->_size.x = size[0];
    this->_size.y = size[1];
    this->_grass.setSize(sf::Vector2f(TILE_SIZE * this->_scale, TILE_SIZE * this->_scale));
    this->_grass.setFillColor(sf::Color::Green);
}

void Render::Draw(sf::RenderWindow &win)
{
    auto size = this->_grass.getSize();

    for (unsigned int y = 0; y < this->_size.y; y++)
        for (unsigned int x = 0; x < this->_size.x; x++) {
            this->_grass.setPosition(size.x * x + x + this->_camera.x, size.y * y + y + this->_camera.y);
            win.draw(this->_grass);
        }
}

void Render::SetScale(float scale)
{
    if (scale < 0)
        return;
    this->_scale = scale;
    this->_grass.setSize(sf::Vector2f(TILE_SIZE * this->_scale, TILE_SIZE * this->_scale));
}

float Render::GetScale(void) const
{
    return (this->_scale);
}

void Render::SetCamera(const sf::Vector2f &pos)
{
    this->_camera = pos;
}

const sf::Vector2f &Render::GetCamera() const
{
    return (this->_camera);
}

void Render::MoveCamera(const sf::Vector2f &move)
{
    this->_camera.x += move.x;
    this->_camera.y += move.y;
}