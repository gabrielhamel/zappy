/*
** EPITECH PROJECT, 2019
** sfml
** File description:
** Render
*/

#include "Render.hpp"
#include <iostream>

static const std::array<sf::Vector2f, 7> hept = {
    sf::Vector2f(0.50f, 0.90f),
    sf::Vector2f(0.81f, 0.75f),
    sf::Vector2f(0.89f, 0.42f),
    sf::Vector2f(0.68f, 0.14f),
    sf::Vector2f(0.34f, 0.19f),
    sf::Vector2f(0.11f, 0.40f),
    sf::Vector2f(0.18f, 0.74f)
};

static const std::array<std::string, 7> file_food = {
    "assets/baked_potato.png",
    "assets/beetroot.png",
    "assets/carrot.png",
    "assets/golden_carrot.png",
    "assets/poisonous_potato.png",
    "assets/redstone.png",
    "assets/wheat.png"
};

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
    this->_grass.setScale(this->_scale, this->_scale);
    this->_texsize = this->_tex_grass.getSize();
    for (int i = 0; i < 7; i++) {
        this->_texfood.push_back(new sf::Texture());
        this->_sprfood.push_back(sf::Sprite());
        this->_texfood[i]->loadFromFile(file_food[i]);
        this->_sprfood[i].setTexture(*this->_texfood[i], true);
        this->_sprfood[i].setScale(this->_scale / 3.5f, this->_scale / 3.5f);
    }
}

void Render::SetMap(std::vector<std::vector<std::array<unsigned int, 7>>> *map)
{
    this->_map = map;
}

void Render::SetSize(const std::array<unsigned int, 2> &size)
{
    this->_size.x = size[0];
    this->_size.y = size[1];
    this->_grass.setScale(this->_scale, this->_scale);
    for (int i = 0; i < 7; i++)
        this->_sprfood[i].setScale(this->_scale / 3.5f, this->_scale / 3.5f);
}

void Render::Draw(sf::RenderWindow &win)
{
    for (unsigned int y = 0; y < this->_size.y; y++)
        for (unsigned int x = 0; x < this->_size.x; x++) {
            this->_grass.setPosition(this->_texsize.x * x * this->_scale + this->_camera.x, this->_texsize.y * y * this->_scale + this->_camera.y);
            win.draw(this->_grass);
            for (int i = 0; i < 7; i++) {
                auto &map = *this->_map;
                if (map[y][x][i]) {
                    this->_sprfood[i].setPosition(this->_texsize.x * x * this->_scale + this->_camera.x + this->_texsize.x * hept[i].x * this->_scale / 1.7f,
                    this->_texsize.y * y * this->_scale + this->_camera.y + this->_texsize.y * hept[i].y * this->_scale / 1.7f);
                    win.draw(this->_sprfood[i]);
                }
            }
        }
}

void Render::SetScale(float scale)
{
    if (scale < 0)
        return;
    this->_scale = scale;
    this->_grass.setScale(this->_scale, this->_scale);
    for (int i = 0; i < 7; i++)
        this->_sprfood[i].setScale(this->_scale / 3.5f, this->_scale / 3.5f);
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