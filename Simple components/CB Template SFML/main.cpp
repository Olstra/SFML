#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int main() {

    const int windowW = 800;
    const int windowH = 800;

    // Create the main window
    RenderWindow window(sf::VideoMode(windowW, windowH), "OLIVER CODES ...", sf::Style::Titlebar | sf::Style::Close);

    // Load a sprite to display
    Texture texture;
    if (!texture.loadFromFile("cb.bmp")){ std::cout<< "ERROR: Background could not be loaded" << std::endl; return -1; }
    Sprite sprite(texture);

	// Start the game loop
    while (window.isOpen()) {
        // Process events
        Event event;
        while (window.pollEvent(event)) {
            switch(event.type) {
                case Event::Closed: window.close(); break;

                case Event::KeyPressed:
                    switch (event.key.code) {

                        case Keyboard::Enter:
                            // ...
                            break;

                        case Keyboard::Escape:
                            window.close();
                            break;

                        default: break;
                    }
            }
        }

        // Clear screen
        window.clear();

        // Draw
        window.draw(sprite);

        // Update the window
        window.display();
    }

    return 0;
}
