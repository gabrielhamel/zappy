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

static const std::array<sf::Vector2i, 9> file_food = {
    sf::Vector2i(0, 0),
    sf::Vector2i(16, 0),
    sf::Vector2i(32, 0),
    sf::Vector2i(48, 0),
    sf::Vector2i(96, 0),
    sf::Vector2i(112, 0),
    sf::Vector2i(128, 0),
    sf::Vector2i(64, 0),
    sf::Vector2i(80, 0)
};

Render::Render(std::vector<Team *> &teams)
: _teams(teams)
{
    this->_font.loadFromFile("assets/font.ttf");
    this->_grass.setPosition(0, 0);
    this->_scale = 1;
    this->_camera.x = 270;
    this->_camera.y = 0;
    this->_tex.loadFromFile("assets/all.png");
    this->_grass.setTexture(this->_tex);
    this->_grass.setTextureRect(sf::IntRect(file_food[7], sf::Vector2i(SPR_SIZE, SPR_SIZE)));
    this->_grass.setColor(sf::Color(100, 170, 100));
    this->_grass.setScale(this->_scale, this->_scale);
    for (int i = 0; i < 7; i++) {
        this->_sprfood.push_back(sf::Sprite());
        this->_sprfood[i].setTexture(this->_tex);
        this->_sprfood[i].setTextureRect(sf::IntRect(file_food[i], sf::Vector2i(SPR_SIZE, SPR_SIZE)));
        this->_sprfood[i].setScale(this->_scale / 3.5f, this->_scale / 3.5f);
    }
    for (auto &team : this->_teams) {
        team->setTexture(&this->_tex);
        team->setScale(this->_scale);
    }
    this->_background.setPosition(0, 0);
    this->_background.setSize(sf::Vector2f(270, 960));
    this->_background.setFillColor(sf::Color(80, 80, 80));
    this->_rendtex.create(1500, 960);
    this->_rendspr.setPosition(0, 0);
    this->_rendtex.clear();
    this->_rendspr.setTexture(this->_rendtex.getTexture(), true);
    this->_teamName.setPosition(0, 0);
    this->_teamName.setFillColor(sf::Color::White);
    this->_teamName.setFont(this->_font);
    this->_teamName.setCharacterSize(20);
}

void Render::SetMap(std::vector<std::vector<std::array<unsigned int, 7>>> *map)
{
    this->_map = map;
}

void Render::SetSize(const std::array<unsigned int, 2> &size)
{
    this->_size.x = size[0];
    this->_size.y = size[1];
    this->_scale = 960.f / ((this->_size.x > this->_size.y ? this->_size.x : this->_size.y) * SPR_SIZE);
    this->_camera.x += (960.f - this->_size.x * SPR_SIZE * this->_scale) / 2.0f;
    this->_camera.y -= (SPR_SIZE * this->_scale) * 2;
    this->_camera.y += this->_size.y * SPR_SIZE * this->_scale;
    this->_camera.y += (960.f - this->_camera.y) / 2;
    this->_grass.setScale(this->_scale, this->_scale);
    for (int i = 0; i < 7; i++)
        this->_sprfood[i].setScale(this->_scale / 3.5f, this->_scale / 3.5f);
    for (auto &team : this->_teams)
        team->setScale(this->_scale);
}

void Render::Draw(sf::RenderWindow &win)
{
    _rendtex.clear();
    for (unsigned int y = 0; y < this->_size.y; y++)
        for (unsigned int x = 0; x < this->_size.x; x++) {
            this->_grass.setPosition(SPR_SIZE * x * this->_scale + this->_camera.x,
            SPR_SIZE * -1 * y * this->_scale + this->_camera.y);
            this->_rendtex.draw(this->_grass);
            for (int i = 0; i < 7; i++) {
                auto &map = *this->_map;
                if (map[y][x][i]) {
                    this->_sprfood[i].setPosition(SPR_SIZE * x * this->_scale + this->_camera.x + SPR_SIZE * hept[i].x * this->_scale / 1.7f,
                    SPR_SIZE * -1 * y * this->_scale + this->_camera.y + SPR_SIZE * hept[i].y * this->_scale / 1.7f);
                    this->_rendtex.draw(this->_sprfood[i]);
                }
            }
        }
    for (auto &team : this->_teams) {
        auto players = team->getPlayers();
        for (auto &player : players) {
            auto pos = player.getPosition();
            team->_spr.setPosition((SPR_SIZE * pos[0] + 8) * this->_scale + this->_camera.x,
            (SPR_SIZE * -1 * pos[1] + 8) * this->_scale + this->_camera.y);
            int ori = player.getOrientation() - 1;
            team->_spr.setRotation(ori * 90 + 180);
            this->_rendtex.draw(team->_spr);
        }
    }
    // UI
    this->_background.setPosition(0, 0);
    this->_rendtex.draw(this->_background);
    this->_background.setPosition(1230, 0);
    this->_rendtex.draw(this->_background);
    
    this->_teamName.setPosition(90, 20);
    for (auto &team : this->_teams) {
        auto saveScale = team->_spr.getScale();
        auto saveRot = team->_spr.getRotation();
        team->_spr.setRotation(0);
        team->_spr.setScale(3, 3);
        team->_spr.setPosition(this->_teamName.getPosition());
        team->_spr.move(-50, 10);
        this->_rendtex.draw(team->_spr);
        auto &str = team->getName();
        this->_teamName.setFillColor(team->getColor());
        this->_teamName.setString(str.substr(0, 8));
        this->_rendtex.draw(this->_teamName);
        this->_teamName.setString(std::to_string(team->getPlayers().size()));
        this->_teamName.move(140, 0);
        this->_rendtex.draw(this->_teamName);
        this->_teamName.move(-140, 75);
        team->_spr.setRotation(saveRot);
        team->_spr.setScale(saveScale);
    }

    this->_rendtex.display();
    win.draw(this->_rendspr);
}

void Render::SetScale(float scale)
{
    if (scale < 0)
        return;
    this->_scale = scale;
    this->_grass.setScale(this->_scale, this->_scale);
    for (int i = 0; i < 7; i++)
        this->_sprfood[i].setScale(this->_scale / 3.5f, this->_scale / 3.5f);
    for (auto &team : this->_teams)
        team->setScale(this->_scale);
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
