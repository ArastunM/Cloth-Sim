/**
 * main.ccp is used to launch the cloth app
 */

#include "gui/cloth_app.hpp"


/* === main function ========================== */
int main() {
    ClothApp cloth_sim(800, 600);
    cloth_sim.launchWin();
    return 0;
}
