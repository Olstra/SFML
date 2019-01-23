#include <SFML/Graphics.hpp>
#include <iostream>

int main() {

    const int windowW = 1000;
    const int windowH = 1000;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(windowW, windowH), "OLIVER CODES ...", sf::Style::Titlebar | sf::Style::Close);

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("cb.bmp")){ std::cout<< "ERROR: Background could not be loaded" << std::endl; return -1; }
    sf::Sprite sprite(texture);

	// Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window : exit
            if (event.type == sf::Event::Closed) { window.close(); }
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
