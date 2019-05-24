/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Application
*/

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <string>
#include <SFML/Graphics.hpp>

namespace Zappy {

    class Application {
        public:
            // Initialise une fenêtre de width * height en ajoutant le name en tant que titre de la fenêtre
            // Ne lance pas la boucle principale
            Application(unsigned int width, unsigned int height, const std::string &name);
            // Lance une boucle infinie procédant à l'obtention des évenements, le traitement et l'affichage
            void Run();
        private:
            // Fonction appelée au moment où l'on gère les évenements
            // Si elle renvoie "false" l'application se termine
            bool Event();
            // Fonction appelée au moment où l'on doit dessiner
            void Draw();
            sf::Vector2u _size;
            sf::RenderWindow _window;
            sf::Event _event;
    };

}

#endif