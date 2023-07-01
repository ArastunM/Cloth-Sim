/**
 * constraint.hpp defines the constraint lines (class).
 * holds 2 verlet points together
 */

#ifndef CLOTH_CONSTRAINT_HPP
#define CLOTH_CONSTRAINT_HPP

#include <cmath>
#include "verlet_point.hpp"


/* === constraint class definition ========================== */
class Constraint {
    VerletPoint * p0; // reference to point 1
    VerletPoint * p1; // reference to point 2
    float length;

    bool is_active = true; // deactivated after being broken

public:
    static const sf::Uint32 color = 0xFFFFFFFF;
    static const sf::Uint32 selected_color = 0xFF0048E3;

    Constraint (VerletPoint *, VerletPoint *);
    Constraint (VerletPoint *, VerletPoint *, float);
    ~Constraint () = default;

    void update (sf::VertexArray&, unsigned int); // updates object position
    void updateVertex (sf::VertexArray&, unsigned int); // updates vertex position

    sf::Color getCurrentColor ();
    float getDistance (); // returns distance between 2 reference points
    void breakConstraint (sf::VertexArray&, unsigned int);

    // setter and getter methods
    VerletPoint * getP0 ();
    VerletPoint * getP1 ();
    float getLength ();
    bool getIsActive ();
};


#endif
