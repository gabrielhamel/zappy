/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Application
*/

#include "Application.hpp"

Application::Application(unsigned int width, unsigned int height, const std::string &name, const std::string &hostname, const std::string &port)
: _size(width, height), _window(sf::VideoMode(width, height), name), _client(hostname, port)
{
    this->_window.setFramerateLimit(60);
    this->_window.setVerticalSyncEnabled(true);
}

void Application::Draw()
{

}

bool Application::Event()
{
    if (this->_event.type == sf::Event::Closed || _event.key.code == sf::Keyboard::Escape)
        return (false);
    return (true);
}

void Application::Run()
{
    while (this->_window.isOpen()) {
        while (this->_window.pollEvent(this->_event))
            if (this->Event() == false)
                this->_window.close();
        this->_window.clear(sf::Color::Black);
        this->Draw();
        this->_window.display();
    }
}