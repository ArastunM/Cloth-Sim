/**
 * constraint.ccp implements the constraint.hpp functions
 */

#include "constraint.hpp"


/* === constraint class implementation ========================== */
Constraint::Constraint(VerletPoint * p0, VerletPoint * p1) : p0(p0), p1(p1), length(getDistance()) {}

Constraint::Constraint(VerletPoint * p0, VerletPoint * p1, float length): p0(p0), p1(p1), length(length) {}


void Constraint::update(sf::VertexArray & constraint_vertices, unsigned int constraint_idx) {
    if (!is_active) return; // deactivated constraints are not updated
    sf::Vector2f p0Pos = p0->getPosition();
    sf::Vector2f p1Pos = p1->getPosition();

    // calculating the offset between 2 verlet points
    sf::Vector2f diff = p0Pos - p1Pos;
    float dist = sqrtf(diff.x * diff.x + diff.y * diff.y);
    float diffFactor = (length - dist) / dist;
    sf::Vector2f offset = diff * diffFactor * 0.5f;

    // re-setting the point position (hence the constraint itself)
    p0->setPosition(p0Pos.x + offset.x, p0Pos.y + offset.y);
    p1->setPosition(p1Pos.x - offset.x, p1Pos.y - offset.y);
    updateVertex(constraint_vertices, constraint_idx);
}

void Constraint::updateVertex(sf::VertexArray & constraint_vertices, unsigned int vertex_idx) {
    // vertex position and color (if changed) is updated
    constraint_vertices[vertex_idx * 2].position = this->p0->getPosition();
    constraint_vertices[vertex_idx * 2+ 1].position = this->p1->getPosition();
    constraint_vertices[vertex_idx * 2].color = getCurrentColor();
    constraint_vertices[vertex_idx * 2 + 1].color = constraint_vertices[vertex_idx * 2].color;
}

sf::Color Constraint::getCurrentColor() {
    // constraint is only selected if both of its points are selected
    bool selection1 = this->getP0()->getIsSelected();
    bool selection2 = this->getP1()->getIsSelected();
    return (selection1 && selection2) ? sf::Color(Constraint::selected_color) : sf::Color(Constraint::color);
}

float Constraint::getDistance() {
    float dx = p0->getPosition().x - p1->getPosition().x;
    float dy = p0->getPosition().y - p1->getPosition().y;
    return sqrtf(dx * dx + dy * dy);
}

void Constraint::breakConstraint(sf::VertexArray & constraint_vertices, unsigned int vertex_idx) {
    // broken constraints are not updated and are transparent
    is_active = false;
    constraint_vertices[vertex_idx * 2].color = sf::Color::Transparent;
    constraint_vertices[vertex_idx * 2 + 1].color = constraint_vertices[vertex_idx * 2].color;
}

VerletPoint *Constraint::getP0() {
    return p0;
}

VerletPoint *Constraint::getP1() {
    return p1;
}

float Constraint::getLength() {
    return length;
}

bool Constraint::getIsActive () {
    return is_active;
}
