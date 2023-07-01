/**
 * cloth.cpp implements the cloth.hpp functions
 */

#include "cloth.hpp"


/* === cloth class implementation ========================== */
Cloth::Cloth(unsigned int width, unsigned int height, unsigned int spacing, float top_x, float top_y) {
    // setting up the cloth object: height * width
    for (unsigned int y = 0; y <= height; y++) {
        for (unsigned int x = 0; x <= width; x++) {
            // setting the verlet point of current slot
            auto * point = new VerletPoint(top_x + static_cast<float>(x * spacing),
                                           top_y + static_cast<float>(y * spacing), 2.f);

            if (x != 0) { // as long as the point is not at the left
                auto * left_point = points[this->points.size() - 1];
                auto * constraint = new Constraint(point, left_point, static_cast<float>(spacing));
                constraints.push_back(constraint);
            }
            if (y != 0) { // as long as the point is not at the top
                auto * up_point = points[x + (y - 1) * (width + 1)];
                auto * constraint = new Constraint(point, up_point, static_cast<float>(spacing));
                constraints.push_back(constraint);
            }

            // pinning the top points (skipping every 1/2 to create hanging effect)
            if (y == 0 && x % 2 == 0) point->pin();
            points.push_back(point);
        }
    }
    // defining the drawable constraint vertices as lines (connecting 2 verlet points)
    constraint_vertices = sf::VertexArray(sf::Lines, constraints.size() * 2);
}

void Cloth::updateEntity(sf::RenderWindow * window, float delta_time, sf::Vector2i mouse_prev_position) {
    // updating point and constraint positions using delta time
    for (auto * verlet_point : points) {
        verlet_point->update(window, delta_time, mouse_prev_position);
    }
    for (unsigned int i = 0; i < constraints.size(); i++) {
        constraints[i]->update(constraint_vertices, i);
        // selected constraints get broken upon right lick
        if (constraints[i]->getCurrentColor() == sf::Color(Constraint::selected_color) &&
                sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
            constraints[i]->breakConstraint(constraint_vertices, i);
    }
}
