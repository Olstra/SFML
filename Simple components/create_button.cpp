/**
How to create a simple button in SFML
By: Olstra
Date: 17 Jan 2019
*/

#include <SFML/Graphics.hpp>
using namespace sf;

const int windowW = 1000;
const int windowH = 1000;

int main() {
    // Create the main window
    RenderWindow window(VideoMode(windowW, windowH), "Oliver Codes A Button", Style::Titlebar | Style::Close);

    // Create the button
    RectangleShape theButton;
    theButton.setSize(Vector2f(200, 200));
    theButton.setFillColor(Color::Black);
    FloatRect textRect = theButton.getLocalBounds();
    theButton.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect .height/2.0f); // set origin to middle of shape
    theButton.setPosition(windowW/2, windowH/2); // set position at center of the screen

	// Start the game loop
    while (window.isOpen()) {
        // Process events
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {  window.close();  }
        }

        // Clear screen
        window.clear(Color::Red);

        // Check for left mouse click //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (Mouse::isButtonPressed(Mouse::Left)) {
                if ( theButton.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y) ) {
                    if (theButton.getFillColor() == Color::Blue) { theButton.setFillColor(Color::Yellow); }
                    else { theButton.setFillColor(Color::Blue); }
                }
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        // Draw the button
        window.draw(theButton);

        // Update the window
        window.display();
    }

    return 0;
}
