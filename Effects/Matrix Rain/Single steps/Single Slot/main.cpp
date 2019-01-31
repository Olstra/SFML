/**
How to create a randomly changing symbol

Date: 31. Jan 2019
Author: olstra
*/


#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;


int main() {

    const int windowW = 800;
    const int windowH = 800;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(windowW, windowH), "OLIVER CODES ...", sf::Style::Titlebar | sf::Style::Close);

    const int fontSize = 50;

    Clock clock;    // Time management
    int currentTime;

    srand(time(0));

    int speed = 800;
    int ellapsedTime;

    // load font
    Font font;
    if(!font.loadFromFile("matrix_code.ttf")){ std::cout<<"ERROR: couldn't load font"<<std::endl; return -1; }

    // GENERATE the SYMBOLS we'll be using
    int nrOfSymbols = 32;
    sf::String chars[nrOfSymbols];
    for(int i = 0; i < nrOfSymbols; i++){ chars[i] = (char)(nrOfSymbols + i); }

    Text symbol("A", font, fontSize);
    symbol.setPosition(windowW/2, windowH/2);
    symbol.setFillColor(Color::Green);

	// Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window : exit
            if (event.type == sf::Event::Closed) { window.close(); }
        }


        ellapsedTime = clock.getElapsedTime().asMilliseconds();

        if(ellapsedTime % speed == 0) { symbol.setString(chars[rand() % (nrOfSymbols-1)]); }

        // Clear screen
        window.clear();

        // Draw
        window.draw(symbol);

        // Update the window
        window.display();
    }

    return 0;
}
