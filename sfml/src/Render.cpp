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
    this->_camera.x = 0;
    this->_camera.y = 0;
    auto img = sf::Image();
    img.loadFromFile("assets/grass_block_top.png");
    this->_tex_grass.loadFromImage(img);
    this->_grass.setTexture(this->_tex_grass, true);
    this->_grass.setColor(sf::Color(100, 170, 100));
    this->_texsize= this->_tex_grass.getSize();
}

void Render::SetSize(const std::array<unsigned int, 2> &size)
{
    this->_size.x = size[0];
    this->_size.y = size[1];
    this->_grass.setScale(this->_scale, this->_scale);
}

void Render::Draw(sf::RenderWindow &win)
{
    for (unsigned int y = 0; y < this->_size.y; y++)
        for (unsigned int x = 0; x < this->_size.x; x++) {
            this->_grass.setPosition(this->_texsize.x * x * this->_scale + this->_camera.x, this->_texsize.y * y * this->_scale + this->_camera.y);
            win.draw(this->_grass);
        }
}

void Render::SetScale(float scale)
{
    if (scale < 0)
        return;
    this->_scale = scale;
    this->_grass.setScale(this->_scale, this->_scale);
    this->_camera.x += scale;
    this->_camera.y += scale;
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
    this->_camera.x = this->_camera.x + move.x;
    this->_camera.y = this->_camera.y + move.y;
}