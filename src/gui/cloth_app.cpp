/**
 * cloth_app.cpp implements the cloth_app.hpp functions
 */

#include "cloth_app.hpp"


/* === cloth app class implementation ========================== */
ClothApp::ClothApp (unsigned int width, unsigned int height) : // setting default values
    ClothApp(width, height, 700, 400, 10) {
}

ClothApp::ClothApp (unsigned int width, unsigned int height, unsigned int cloth_width,
                    unsigned int cloth_height, unsigned int cloth_spacing) {
    window = new sf::RenderWindow();
    window->create(sf::VideoMode(width, height),
                   "Cloth Simulator", sf::Style::Close);

    // adjusting the cloth height and width to required spacing
    unsigned int cloth_width_count = cloth_width / cloth_spacing;
    unsigned int cloth_height_count = cloth_height / cloth_spacing;
    // setting up cloth start positions on the window (centered top)
    float start_x = static_cast<float>(window->getSize().x) * 0.5f -
            (static_cast<float>(cloth_width_count * cloth_spacing) * 0.5f);
    float start_y = static_cast<float>(window->getSize().y) * 0.1f;
    cloth = new Cloth(cloth_width_count, cloth_height_count, cloth_spacing, start_x, start_y);
}

void ClothApp::launchWin () {
    sf::Vector2i mouse_prev_position {};
    float delta_cap = 1.0f / 100.f;
    float delta_time;

    // main loop (runs as long as main window is open)
    while (window->isOpen()) {
        // event loop (checks for triggered events in every iteration)
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            if (event.type == sf::Event::MouseButtonPressed &&
                sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                mouse_prev_position = sf::Mouse::getPosition(*window);
            }
            if (event.type == sf::Event::MouseWheelScrolled) {
                VerletPoint::set_selection_range(event.mouseWheelScroll.delta);
            }
        }

        // pixel update operations
        window->clear(sf::Color::Black);
        // updating the window
        delta_time = clock.restart().asSeconds();
        // capping deals with the high delta time during start-up
        if (delta_time > delta_cap) continue;
        cloth->updateEntity(window, delta_time, mouse_prev_position);
        window->draw(*cloth);
        window->display();
    }
}

ClothApp::~ClothApp() {
    delete window;
    delete cloth;
}
