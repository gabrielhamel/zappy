/*
** EPITECH PROJECT, 2019
** sfml
** File description:
** Render
*/

#pragma once

#define SPR_SIZE 16.0f

#include "Team.hpp"
#include <SFML/Graphics.hpp>
#include <array>

class Render {
	public:
        Render(std::vector<Team *> &teams);
		void Draw(sf::RenderWindow &win);
        void SetSize(const std::array<unsigned int, 2> &size);
        void SetScale(float scale);
        float GetScale(void) const;
        void SetCamera(const sf::Vector2f &pos);
        const sf::Vector2f &GetCamera() const;
        void MoveCamera(const sf::Vector2f &move);
        void SetMap(std::vector<std::vector<std::array<unsigned int, 7>>> *map);
    private:
        sf::Vector2u _texsize;
        sf::Sprite _grass;
        sf::Vector2u _size;
        float _scale;
        sf::Vector2f _camera;
        std::vector<sf::Sprite> _sprfood;
        std::vector<std::vector<std::array<unsigned int, 7>>> *_map;
        std::vector<Team *> &_teams;
        sf::Texture _tex;
        sf::RenderTexture _rendtex;
        sf::Sprite _rendspr;
        sf::RectangleShape _background;
        sf::Font _font;
        sf::Text _teamName;
};