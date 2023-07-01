/**
 * cloth_app.hpp defines the cloth app window.
 */

#ifndef CLOTH_CLOTH_APP_HPP
#define CLOTH_CLOTH_APP_HPP

#include <SFML/Graphics.hpp>
#include "../engine/cloth.hpp"


/* === cloth app class definition ========================== */
class ClothApp {
    sf::RenderWindow * window;
    sf::Event event {};
    sf::Clock clock;

    Cloth * cloth; // the cloth object

public:
    ClothApp (unsigned int, unsigned int);
    ClothApp (unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
    ~ClothApp ();

    void launchWin ();
};


#endif
