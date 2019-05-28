/*
** EPITECH PROJECT, 2019
** sfml
** File description:
** Render
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <array>

#define TILE_SIZE 40

class Render {
	public:
        Render();
		void Draw(sf::RenderWindow &win);
        void SetSize(const std::array<unsigned int, 2> &size);
        void SetScale(float scale);
        float GetScale(void) const;
        void SetCamera(const sf::Vector2f &pos);
        const sf::Vector2f &GetCamera() const;
        void MoveCamera(const sf::Vector2f &move);
    private:
        sf::Vector2u _texsize
;        sf::Texture _tex_grass;
        sf::Sprite _grass;
        sf::Vector2u _size;
        float _scale;
        sf::Vector2f _camera;
};