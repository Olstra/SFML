/**
    Here goes everything that has to do with the game PIPES
        - create pipes
        - move pipes (/update its position)
        - draw pipees
*/

#include <SFML/Graphics.hpp>
#include <iostream>


// Pipes attributes
const int PIPE_WIDTH = 100;
int velPipes = 5;               	// velocity at which the pipes pass by
const int distance = PIPE_WIDTH * 2;	// distance between 2 pipes (2x pipes witdth inbetween pipes)
int antiPipeH = 200;            	// distance between pipe top and pipe bottom "Lücke"
const int NR_OF_PIPES = 3;		// ( SCREEN_WIDTH / PIPE_WIDTH ) / 3 => pipe-x-x-pipe-x-x-pipe-...

// SFML Stuff
sf::Clock pipesClock;
static sf::RectangleShape pipesTop[NR_OF_PIPES];
static sf::RectangleShape pipesBottom[NR_OF_PIPES];

// Load Pipes textures/PNGs
static sf::Texture bottomPipeTxtr, topPipeTxtr;
static sf::Sprite pipesBottomSprt[NR_OF_PIPES], pipesTopSprt[NR_OF_PIPES];


int randHeight( int SCREEN_HEIGHT ) {

    int minHeight = antiPipeH + 100;
    int maxHeight = SCREEN_HEIGHT - ( antiPipeH + 100 );

    int randHeight = minHeight + rand() % ( ( maxHeight + 1 ) - minHeight );
    return randHeight;

}


void initPipes( int SCREEN_WIDTH, int SCREEN_HEIGHT ) {

    int temp;

    // Load pics for pipes
    if ( !bottomPipeTxtr.loadFromFile( "media/pipes_bottom.png" ) ) { std::cout << "ERROR: Pipes.h line 24" << std::endl; }
    if ( !topPipeTxtr.loadFromFile( "media/pipes_top.png" ) ) { std::cout << "ERROR: Pipes.h line 24" << std::endl; }

    // inititalize pipes
    for ( int i = 0; i < NR_OF_PIPES; i++) {

        temp = randHeight( SCREEN_HEIGHT );

        // create pipes
	pipesTopSprt[i].setTexture( topPipeTxtr );
	pipesTopSprt[i].setTextureRect( sf::IntRect( 0, SCREEN_HEIGHT-temp, PIPE_WIDTH, temp ) );
	pipesTopSprt[i].setPosition( SCREEN_WIDTH + ( i * ( distance + PIPE_WIDTH ) ), 0 );

	pipesBottomSprt[i].setTexture( bottomPipeTxtr );
	pipesBottomSprt[i].setTextureRect( sf::IntRect( 0, 0, PIPE_WIDTH, SCREEN_HEIGHT ) );
	pipesBottomSprt[i].setPosition( SCREEN_WIDTH + ( i * ( distance + PIPE_WIDTH ) ), ( temp + antiPipeH ) );

    }

}


void drawPipes( sf::RenderWindow& window ) {

    for(int i = 0; i < NR_OF_PIPES; i++) {
	window.draw( pipesTopSprt[i] );
	window.draw( pipesBottomSprt[i] );
    }
}


void movePipes( int SCREEN_WIDTH, int SCREEN_HEIGHT ) {

    int newPos;

    // move pipes according to ellapsed time
    if( pipesClock.getElapsedTime().asMilliseconds() > velPipes ) {
        for ( int i = 0; i < NR_OF_PIPES; i++) {
            if( pipesTopSprt[i].getPosition().x > 0 - PIPE_WIDTH ) {
                newPos = pipesTopSprt[i].getPosition().x - 1; // move pipes to the left
                pipesTopSprt[i].setPosition( sf::Vector2f( newPos, 0 ) );
                pipesBottomSprt[i].setPosition( sf::Vector2f( newPos, pipesBottomSprt[i].getPosition().y ) );
            }
            else{
                // generate new pipes dimensions every time pipes "leave" screen
                newPos = randHeight( SCREEN_HEIGHT );

                pipesTopSprt[i].setTextureRect( sf::IntRect( 0, SCREEN_HEIGHT-newPos, PIPE_WIDTH, newPos ) );
                pipesTopSprt[i].setPosition( SCREEN_WIDTH + distance, 0 );

                pipesBottomSprt[i].setTextureRect( sf::IntRect( 0, 0, PIPE_WIDTH, SCREEN_HEIGHT ) );
                pipesBottomSprt[i].setPosition( SCREEN_WIDTH + distance,  newPos + antiPipeH  );
            }
        }

        pipesClock.restart(); // better this way otherwise flackering in screen
    }

}
