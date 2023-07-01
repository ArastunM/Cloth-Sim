/**
 * verlet_points.hpp defines the verlet point (class).
 * points are updated using verlet integration.
 * good use for structural simulations
 */

#ifndef CLOTH_VERLET_POINT_HPP
#define CLOTH_VERLET_POINT_HPP

#include <SFML/Graphics.hpp>
#include <cmath>


/* === verlet point class definition ========================== */
class VerletPoint {
protected:
    // base physics parameters:
    const sf::Vector2f GRAVITY = sf::Vector2f{0.0f, 981.f};
    const float BOUNCE = 0.85f;
    const float AIR_FRICTION = 0.f; // sometimes not required
    const float TOUCH_SENSITIVITY = 2.f; // reaction to user touches (e.g. dragging)

    sf::Vector2f pos;
    sf::Vector2f prev_pos;
    sf::Vector2f init_pos;
    // based on gravity, bounce, drag and initial velocity
    sf::Vector2f acceleration;

    bool is_pinned = false;
    bool is_selected = false;

    // mouse selection range of verlet points
    static const unsigned int min_selection = 10;
    static const unsigned int max_selection = 60;
    static unsigned int selection_range;
    void manageBounds (unsigned int, unsigned int);

public:
    VerletPoint (float, float, float mass = 1);
    VerletPoint (float, float, sf::Vector2f, float mass = 1);
    ~VerletPoint () = default;

    virtual void update (sf::RenderWindow *, float, sf::Vector2i);
    virtual void applyDragging (sf::RenderWindow *window, sf::Vector2i mouse_prev_pos);
    void pin ();

    // setter and getter methods
    static void set_selection_range (float change);
    bool getIsSelected () const;
    sf::Vector2f getPosition ();
    void setPosition (float, float);
};


#endif
