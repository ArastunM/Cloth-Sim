/**
 * verlet_entity.ccp implements the verlet_entity.hpp functions
 */

#include "verlet_entity.hpp"


/* === verlet entity class implementation ========================== */
void VerletEntity::draw(sf::RenderTarget & renderTarget, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = nullptr; // no texture used
    renderTarget.draw(constraint_vertices, states);
}

VerletEntity::VerletEntity() = default;

void VerletEntity::updateEntity(sf::RenderWindow * window, float delta_time, sf::Vector2i mouse_prev_pos) {
    // updating point and constraint positions every using delta time
    for (auto * verlet_point : points) {
        verlet_point->update(window, delta_time, mouse_prev_pos);
    }
    for (unsigned int i = 0; i < constraints.size(); i++) {
        constraints[i]->update(constraint_vertices, i);
        // selected constraints get broken upon right lick
        if (constraints[i]->getCurrentColor() == sf::Color(Constraint::selected_color)
                && sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
            constraints[i]->breakConstraint(constraint_vertices, i);
    }
}

VerletEntity::~VerletEntity() {
    for (auto * point : points) {
        delete point;
    }
    for (auto * constraint : constraints) {
        delete constraint;
    }
}
