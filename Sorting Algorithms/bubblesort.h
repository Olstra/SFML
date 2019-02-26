/**
    Contains bubble sort for use with SFML
    Author: Olstra
    Date: 23. Feb 2018
**/

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;


void bubbleSort( RenderWindow &window, Clock clock, int intervall, RectangleShape rects[], int NR_OF_RECTS ) {

    Vector2f tempLen;

    int currentTime = clock.getElapsedTime().asMilliseconds();

    if( currentTime % intervall == 0 ) { // make go slower
        // bubble sort
        for( int i = NR_OF_RECTS-2; i >= 0; i-- ) {

            window.clear(); // Clear screen

            for( int j = NR_OF_RECTS-1; j >= i ; j-- ) {

                if( rects[i].getSize().x > rects[j].getSize().x ) {

                    if( ( currentTime % intervall ) == 0 ) {
                        // swap length
                        tempLen = rects[i].getSize();
                        rects[i].setSize( rects[j].getSize() );
                        rects[j].setSize( tempLen );
                        break; // IMPORTANT
                    }
                }
            }

           // draw & display
           for( int i = 0; i < NR_OF_RECTS; i++ ) { window.draw( rects[i] ); }
           window.display();

        }
    }

}
