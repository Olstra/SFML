#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

const int S_WIDTH = 1000;
const int S_HEIGHT = 1000;

int main() {
    // Create the main window
    RenderWindow window( VideoMode( S_WIDTH, S_HEIGHT ), "OLIVER CODES ...", Style::Titlebar | Style::Close );

    // Load a sprite to display
    Texture texture;
    if (!texture.loadFromFile("cb.bmp")) { std::cout << "ERROR: Texture couldn't be loaded" << std::endl; return 0; }
    Sprite sprite(texture);

	// Start the game loop
    while ( window.isOpen() ) {
        // Process events
        Event event;
        while (window.pollEvent( event )) {
            // Close window : exit
            if ( event.type == Event::Closed ) window.close();
        }

        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw( sprite );

        // Update the window
        window.display();
    }

    return 0;
}
