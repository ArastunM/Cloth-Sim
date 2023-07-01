/**
 * cloth.hpp defines the cloth object.
 * derives from the verlet entity class
 */

#ifndef CLOTH_CLOTH_HPP
#define CLOTH_CLOTH_HPP

#include <SFML/Graphics.hpp>
#include "../engine/verlet/verlet_entity.hpp"


/* === cloth class definition ========================== */
class Cloth: public VerletEntity {

public:
    Cloth () = default;
    // parameters: cloth width, height, spacing and position on the window
    Cloth (unsigned int, unsigned int, unsigned int, float, float);

    void updateEntity (sf::RenderWindow *, float, sf::Vector2i) override;
};


#endif
