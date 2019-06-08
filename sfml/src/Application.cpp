/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Application
*/

#include "Application.hpp"

Application::Application(unsigned int width, unsigned int height, const std::string &name, const std::string &hostname, const std::string &port)
: _size(width, height), _window(sf::VideoMode(width, height), name, sf::Style::Close), _client(hostname, port, this->_render), _render(this->_client.getTeams())
{
    this->_window.setFramerateLimit(60);
    this->_window.setVerticalSyncEnabled(true);
    auto size = this->_client.GetMapSize();
    this->_render.SetSize(size);
    this->_render.SetMap(this->_client.GetMap());
    for (auto &i : this->_keys)
        i = false;
    this->_mousePressed = false;
}

void Application::Draw()
{
    this->_render.Draw(this->_window);
}

bool Application::Event()
{
    if (this->_event.type == sf::Event::Closed)
        return (false);
    else if (this->_event.type == sf::Event::KeyPressed)
        this->_keys[this->_event.key.code] = true;
    else if (this->_event.type == sf::Event::KeyReleased)
        this->_keys[this->_event.key.code] = false;
    else if (this->_event.type == sf::Event::MouseButtonPressed)
        this->_mousePressed = true;
    else if (this->_event.type == sf::Event::MouseButtonReleased)
        this->_mousePressed = false;
    return (true);
}

bool Application::Refresh()
{
    this->_client.Refresh();
    if (this->KeyPress(sf::Keyboard::Escape))
        return (false);
    // if (this->KeyPress(sf::Keyboard::Equal))
    //     this->_render.SetScale(this->_render.GetScale() + 0.035f * this->_speed);
    // if (this->KeyPress(sf::Keyboard::Hyphen))
    //     this->_render.SetScale(this->_render.GetScale() - 0.035f * this->_speed);
    // if (this->KeyPress(sf::Keyboard::Q) || this->KeyPress(sf::Keyboard::Left))
    //     this->_render.MoveCamera(sf::Vector2f(-8.f * this->_speed, 0));
    // if (this->KeyPress(sf::Keyboard::D) || this->KeyPress(sf::Keyboard::Right))
    //     this->_render.MoveCamera(sf::Vector2f(8.f * this->_speed, 0));
    // if (this->KeyPress(sf::Keyboard::Z) || this->KeyPress(sf::Keyboard::Up))
    //     this->_render.MoveCamera(sf::Vector2f(0, -8.f * this->_speed));
    // if (this->KeyPress(sf::Keyboard::S) || this->KeyPress(sf::Keyboard::Down))
    //     this->_render.MoveCamera(sf::Vector2f(0, 8.f * this->_speed));
    if (this->KeyPress(sf::Keyboard::P))
        this->_render.setPlayerFocus(nullptr);
    if (this->KeyPress(sf::Keyboard::T))
        this->_render.unsetTileFocus();
    if (this->_mousePressed) {
        this->_render.testFocus(sf::Mouse::getPosition(this->_window));
        this->_mousePressed = false;
    }
    if (this->KeyPress(sf::Keyboard::PageUp))
        this->_render.scrollTeam(10.f * this->_speed);
    if (this->KeyPress(sf::Keyboard::PageDown))
        this->_render.scrollTeam(-10.f * this->_speed);
    return (true);
}

void Application::Run()
{
    while (this->_window.isOpen()) {
        this->_speed = 1000000.f / (this->_clock.getElapsedTime().asMicroseconds() * 60);
        this->_clock.restart();
        while (this->_window.pollEvent(this->_event))
            if (this->Event() == false)
                this->_window.close();
        if (this->Refresh() == false)
            this->_window.close();
        this->_window.clear(sf::Color::Black);
        this->Draw();
        this->_window.display();
    }
}

bool Application::KeyPress(sf::Keyboard::Key key)
{
    return (this->_keys[key]);
}