/**
    Here goes everything that has to do with the game PIPES
        - create pipes
        - move pipes (/update its position)
        - draw pipees
*/

#include <SFML/Graphics.hpp>
#include <iostream>


const int PIPE_WIDTH = 100;
int velPipes = 5;               // velocity at which the pipes pass by
const int distance = 200;//PIPE_WIDTH * 3;  // distance between 2 pipes (2x pipes witdth inbetween pipes)
int antiPipeH = 200;            // distance between pipe top and pipe bottom "Lücke"
sf::Clock pipesClock;

const int NR_OF_PIPES = 3;//( 1200 / PIPE_WIDTH ) / 3; // (screenWidth/PW)/3 => pipe-x-x-pipe-x-x-pipe-...
static sf::RectangleShape pipesTop[NR_OF_PIPES];
static sf::RectangleShape pipesBottom[NR_OF_PIPES];


int randHeight( int SCREEN_HEIGHT ) {

    int minHeight = antiPipeH + 100;
    int maxHeight = SCREEN_HEIGHT - ( antiPipeH + 100 );

    int randHeight = minHeight + rand() % ( ( maxHeight + 1 ) - minHeight );

    return randHeight;

}

void initPipes( int SCREEN_WIDTH, int SCREEN_HEIGHT ) {

    int temp;

    // inititalize pipes
    for ( int i = 0; i < NR_OF_PIPES; i++) {

        temp = randHeight( SCREEN_HEIGHT );

        // create pipes
        pipesTop[i].setSize( sf::Vector2f( PIPE_WIDTH, temp ) );
        pipesTop[i].setPosition( SCREEN_WIDTH + (i *( distance + PIPE_WIDTH ) ), 0 );
        pipesTop[i].setFillColor( sf::Color::Green );

        // create bottom pipes
        pipesBottom[i].setSize( sf::Vector2f( PIPE_WIDTH, ( SCREEN_HEIGHT-temp-antiPipeH ) ));
        pipesBottom[i].setPosition( SCREEN_WIDTH + (i * ( distance + PIPE_WIDTH ) ), ( temp+antiPipeH ));
        pipesBottom[i].setFillColor( sf::Color::Green );

    }

}

void drawPipes( sf::RenderWindow& window ) {

    for(int i = 0; i < NR_OF_PIPES; i++) {
        window.draw( pipesTop[i] );
        window.draw( pipesBottom[i] );
    }
}

int idxX = 0;

void movePipes( int SCREEN_WIDTH, int SCREEN_HEIGHT ) {

    int newPos;
	int nextIdx;
    // move pipes according to ellapsed time
    if( pipesClock.getElapsedTime().asMilliseconds() > velPipes ) {
        for ( int i = 0; i < NR_OF_PIPES; i++) {

            if( pipesTop[i].getPosition().x > 0 - PIPE_WIDTH ) {
                newPos = pipesTop[i].getPosition().x - 1; // move pipes to the left
                pipesTop[i].setPosition( sf::Vector2f( newPos, 0 ) );
                pipesBottom[i].setPosition( sf::Vector2f( newPos, pipesBottom[i].getPosition().y ) );
            }
            else{
		// re-insert pipe at 'distance' behing last pipe
		( i + 1 < NR_OF_PIPES ) ? nextIdx = i + 1 : nextIdx = 0; 
                newPos = randHeight( SCREEN_HEIGHT );
                pipesTop[i].setSize( sf::Vector2f( PIPE_WIDTH, newPos ) );
                pipesTop[i].setPosition( SCREEN_WIDTH + distance, 0 );
                pipesBottom[i].setSize( sf::Vector2f( PIPE_WIDTH, ( SCREEN_HEIGHT-newPos-antiPipeH ) ));
                pipesBottom[i].setPosition( SCREEN_WIDTH + distance , ( newPos + antiPipeH ));
		}
        }

        pipesClock.restart(); // better this way otherwise flackering in screen
    }

}



