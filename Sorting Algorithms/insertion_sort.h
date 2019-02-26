/**
    Contains insertion sort for use with SFML
    Author: Olstra
    Date: 23. Feb 2018
**/

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;


void insertionSort( RenderWindow &window, Clock clock, int intervall, RectangleShape rects[], int NR_OF_RECTS ) {

    Vector2f tempLen, key;
    int currentTime = clock.getElapsedTime().asMilliseconds();

    if( currentTime % intervall == 0 ) { // make go slower
        // insertion sort
        for( int i = 1; i < NR_OF_RECTS; i++ ) {

            window.clear(); // Clear screen

            key = rects[i].getSize();

            while( key.x < rects[i-1].getSize().x && i >= 1 ) {
                // swap length
                tempLen = rects[i].getSize();
                rects[i].setSize( rects[i-1].getSize() );
                rects[i-1].setSize( tempLen );

                i--; // go to next element
                break;
            }

            rects[i].setSize( key );

            // draw & display
            for( int i = 0; i < NR_OF_RECTS; i++ ) { window.draw( rects[i] ); }
            window.display();

        }
    }
}
