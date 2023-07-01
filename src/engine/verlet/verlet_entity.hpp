/**
 * verlet_entity.hpp defines the verlet entity (class).
 * drawable entity for verlet points and constraints
 */

#ifndef CLOTH_VERLET_ENTITY_HPP
#define CLOTH_VERLET_ENTITY_HPP

#include "verlet_point.hpp"
#include "constraint.hpp"


/* === verlet entity class definition ========================== */
class VerletEntity: public sf::Drawable, public sf::Transformable {
protected:
    std::vector<VerletPoint*> points;
    std::vector<Constraint*> constraints;

    // only storing and drawing constraints (lines) to save extra space
    sf::VertexArray constraint_vertices;

    void draw (sf::RenderTarget&, sf::RenderStates) const override;

public:
    VerletEntity ();
    ~VerletEntity () override;

    // updates entity every frame
    virtual void updateEntity (sf::RenderWindow *, float, sf::Vector2i);
};


#endif
