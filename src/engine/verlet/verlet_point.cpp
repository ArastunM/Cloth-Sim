/**
 * verlet_point.ccp implements the verlet_point.hpp functions
 */

#include "verlet_point.hpp"


/* === verlet point class implementation ========================== */
unsigned int VerletPoint::selection_range = 20;

void VerletPoint::manageBounds(unsigned int win_width, unsigned int win_height) {
    // manages verlet point collisions with window bounds
    // -1 to account for the particle size
    auto f_width = static_cast<float>(win_width) - 1;
    auto f_height = static_cast<float>(win_height) - 1;

    // re-setting the velocity by changing previous position
    float vx = pos.x - prev_pos.x;
    float vy = pos.y - prev_pos.y;

    if (pos.x > f_width) { pos.x = f_width; prev_pos.x = pos.x + vx * BOUNCE; }
    else if (pos.x < 1) { pos.x = 1; prev_pos.x = pos.x + vx * BOUNCE; }
    if (pos.y > f_height) { pos.y = f_height; prev_pos.y = pos.y + vy * BOUNCE; }
    else if (pos.y < 1) { pos.y = 1; prev_pos.y = pos.y + vy * BOUNCE; }
}

VerletPoint::VerletPoint(float x, float y, float mass) {
    pos = prev_pos = init_pos = sf::Vector2f {x, y};
    this->acceleration = GRAVITY / mass; // a = F/m
}

VerletPoint::VerletPoint(float x, float y, sf::Vector2f init_vel, float mass) : VerletPoint(x, y, mass) {
    this->prev_pos = pos - init_vel; // setting initial velocity;
}

void VerletPoint::update(sf::RenderWindow * window, float delta_time, sf::Vector2i mouse_prev_pos) {
    // using mouse position to detect verlet point selection
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
    sf::Vector2f mouse_dir = sf::Vector2f {pos.x - static_cast<float>(mouse_pos.x),
                                          pos.y - static_cast<float>(mouse_pos.y)};
    float mouseDist = std::sqrt(mouse_dir.x * mouse_dir.x + mouse_dir.y * mouse_dir.y);
    is_selected = mouseDist < static_cast<float>(VerletPoint::selection_range);
    // applying cloth dragging effect
    applyDragging(window, mouse_prev_pos);

    // applying the verlet integration (+ AIR_FRICTION and BOUNCE force)
    /**
     * VERLET INTEGRATION
     *
     * v(n + 1) = v(n) + a(n) * dt
     * v(n) = (x(n) - x(n-1)) * (1/dt)
     * x(n + 1) = x(n) + v(n + 1) * dt
     * hence
     * x(n + 1) = x(n) + (v(n) + a(n) * dt) * dt
     * x(n + 1) = x(n) + dt(v(n)) + (dt * dt)a(n)
     * x(n + 1) = x(n) + (x(n) - x(n-1)) + a(n)(dt * dt)
     * x(n + 1) = 2x(n) - x(n-1) + a(n)(dt * dt)
     */
    sf::Vector2f new_pos = pos + (pos - prev_pos) * (1 - AIR_FRICTION) + acceleration * (1 - AIR_FRICTION) * delta_time * delta_time;
    prev_pos = pos;
    pos = new_pos;
    manageBounds(window->getSize().x, window->getSize().y);

    if (is_pinned) { pos = init_pos; return; }
}

void VerletPoint::applyDragging(sf::RenderWindow * window, sf::Vector2i mouse_prev_pos) {
    // cloth is moved/dragged when left button is pressed
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && is_selected) {
        sf::Vector2i difference = sf::Mouse::getPosition(*window) - mouse_prev_pos;
        sf::Vector2f difference_f = sf::Vector2f {static_cast<float>(difference.x),
                                                  static_cast<float>(difference.y)};
        if (difference_f.x > TOUCH_SENSITIVITY) difference_f.x = TOUCH_SENSITIVITY;
        if (difference_f.y > TOUCH_SENSITIVITY) difference_f.y = TOUCH_SENSITIVITY;
        if (difference_f.x < -TOUCH_SENSITIVITY) difference_f.x = -TOUCH_SENSITIVITY;
        if (difference_f.y < -TOUCH_SENSITIVITY) difference_f.y = -TOUCH_SENSITIVITY;;
        prev_pos = pos - difference_f;
    }
}

void VerletPoint::pin() {
    is_pinned = true;
}

void VerletPoint::set_selection_range(float change) {
    VerletPoint::selection_range += (static_cast<int>(change * 10));
    if (VerletPoint::selection_range > max_selection) VerletPoint::selection_range = max_selection;
    if (VerletPoint::selection_range < min_selection) VerletPoint::selection_range = min_selection;
}

bool VerletPoint::getIsSelected() const {
    return is_selected;
}

sf::Vector2f VerletPoint::getPosition() {
    return pos;
}

void VerletPoint::setPosition(float x, float y) {
    pos = sf::Vector2f {x, y};
}
