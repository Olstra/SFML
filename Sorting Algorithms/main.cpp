/**
    Visualizations for following sorting algotithms:
        °bubble sort
        °insertion sort
        °selection sort

    Author: Olstra
    Date: 23. Feb 2018

    TODOS:
        - implement selection sort
        - make main menu
        - show current element, change colors

*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include "bubblesort.h"
#include "insertion_sort.h"
#include "selection_sort.h"

using namespace sf;

enum GAME_STATE { mainMenu, bubble, insertion, selection } state;

int main() {

    const int S_WIDTH = 800;
    const int S_HEIGHT = 800;

    // Create the main window
    RenderWindow window( VideoMode( S_WIDTH, S_HEIGHT ), "OLIVER VISUALIZES SORTING ALGORITHMS", Style::Titlebar | Style::Close );

    // Time management
    Clock clock;
    int currentTime;
    int intervall = 1000; // milliseconds

    state = insertion;

    // Create rects /////////////////////////////////////////////////////////////////////////////

    int margin = 100;
    int abstand = 40;
    int length;             // for rects, will be set later randomly
    const int WIDTH = 25;   // width of rectangles

    const int MIN_LEN = 10;
    const int MAX_LEN = S_WIDTH - ( 2 * abstand );
    const int NR_OF_RECTS = (S_HEIGHT - ( 2 * abstand ) ) / WIDTH; 
    RectangleShape rects[NR_OF_RECTS];

    srand( (int)time( 0 ) ); // init random seed

    for( int i = 0; i < NR_OF_RECTS; i++ ) {

        length = MIN_LEN + rand() % ( ( MAX_LEN + 1 ) - MIN_LEN ); // create rand length for each rect

        // create rects
        rects[i].setSize( Vector2f( length, WIDTH ) );
        rects[i].setPosition( Vector2f( margin, i * abstand + abstand ) );
        rects[i].setFillColor( Color::Blue );

    }

    /////////////////////////////////////////////////////////////////////////////////////////////


	// Start the game loop
    while ( window.isOpen() ) {

        // Process events
        Event event;
        while (window.pollEvent( event )) {

             switch( event.type ) {

                case Event::Closed: window.close(); break;

                case Event::KeyPressed:

                    switch (event.key.code) {
                        case Keyboard::Return:
                            state = bubble;
                            break;

                        case Keyboard::Escape: window.close(); break;
                        default: break;
                    }
            }
        }


        switch( state ) {

            case mainMenu:
                window.clear();
                break;

            case bubble:
                bubbleSort( window, clock, intervall, rects, NR_OF_RECTS );
                break;

            case insertion:
                insertionSort( window, clock, intervall, rects, NR_OF_RECTS );
                break;

            case selection:
                selectionSort( window, clock, intervall, rects, NR_OF_RECTS );
                break;

        }

    }

    return 0;
}
