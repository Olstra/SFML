#include <SFML/Graphics.hpp>
#include <iostream>

#include "complex_numbers.h"
#include "mandelbort_function.h"

using namespace sf;



int main() {
	
	const int S_WIDTH = 1000;
	const int S_HEIGHT = 1000;

    // Create the main window
    RenderWindow window( VideoMode( S_WIDTH, S_HEIGHT ), "OLIVER CODES ...", Style::Titlebar | Style::Close );

	// dimensions of our fractal
	int FRACT_WIDTH = 100;
	int FRACT_HEIGHT = 100;

	sf::RectangleShape pixels[FRACT_WIDTH*FRACT_HEIGHT]; // pixels of our grid
	sf::RectangleShape pixel(sf::Vector2f(1, 1); // a single pixel
	pixel.setFillColor( Color::Red );

	int start_W = 200;
	int start_H = 200;

	// make our own pixel grid in which well be drawing
	int idx = 0;
	for ( int x = start_W; x < FRACT_WIDTH; x++ ) {
		for ( int y = start_H; y < FRACT_HEIGHT; y++ ) {
			pixels[idx] = pixel;
			pixels[idx].setPosition( sf::Vector2f(x,y));
			idx++;		
		}
	
	
	
	}



	// Start the game loop
    while ( window.isOpen() ) {
        // Process events
        Event event;
        while (window.pollEvent( event )) {
            // Close window : exit
            if ( event.type == Event::Closed ) window.close();
        }

        // Clear screen
        window.clear( Color::Blue );

		for ( int x = 0; x < FRACT_WIDTH; x++ ) {
			for ( int y = 0; y < FRACT_HEIGHT; y++ ) {
			
					
			
			}
		
		
		
		}




        // Draw the sprite
        // window.draw( );

        // Update the window
        window.display();
    }

    return 0;
}
