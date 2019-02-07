/**
    Here goes everything that has to do with the game PIPES
        - create pipes
        - move pipes (/update its position)
        - draw pipees
*/

#include <SFML/Graphics.hpp>
#include <iostream>


const int PIPE_WIDTH = 100;
float velPipes = 5.0;           // velocity at which the pipes pass by
int distance = PIPE_WIDTH * 3;  // distance between 2 pipes
int antiPipeH = 200;            // distance between pipe top and pipe bottom "Lücke"
sf::Clock pipesClock;

const int NR_OF_PIPES = ( 1200 / PIPE_WIDTH ) / 3; // (screenWidth/PW)/3 => pipe-x-x-pipe-x-x-pipe-...
static sf::RectangleShape pipes[NR_OF_PIPES];
static sf::RectangleShape antiPipes[NR_OF_PIPES];


int randHeight( int SCREEN_HEIGHT ) {

    int minHeight = antiPipeH + 100;
    int maxHeight = SCREEN_HEIGHT - ( antiPipeH + 100 );

    int randHeight = minHeight + rand() % ( ( maxHeight + 1 ) - minHeight );

    return randHeight;

}

void initPipes(int SCREEN_WIDTH, int SCREEN_HEIGHT) {

    int temp;

    // inititalize pipes
    for ( int i = 0; i < NR_OF_PIPES; i++) {
        // create pipes
        pipes[i].setSize(sf::Vector2f(PIPE_WIDTH, SCREEN_HEIGHT));
        pipes[i].setPosition(SCREEN_WIDTH + (i * distance), 0);
        pipes[i].setFillColor(sf::Color::Green);

        // create antipipes
        antiPipes[i].setSize(sf::Vector2f(PIPE_WIDTH, antiPipeH));
        antiPipes[i].setFillColor(sf::Color::White);
        antiPipes[i].setPosition(pipes[i].getPosition().x, randHeight( SCREEN_HEIGHT ) );
    }

}

void drawPipes( sf::RenderWindow& window ) {

    for(int i = 0; i < NR_OF_PIPES; i++) {
        window.draw( pipes[i] );
        window.draw( antiPipes[i] );
    }
}

void movePipes( int SCREEN_WIDTH, int SCREEN_HEIGHT ) {
    int temp;

    // move pipes according to ellapsed time
    if( pipesClock.getElapsedTime().asMilliseconds() >= velPipes) {
        for ( int i = 0; i < NR_OF_PIPES; i++) {

            if( pipes[i].getPosition().x >= 0) {
                temp = pipes[i].getPosition().x - 1;
                pipes[i].setPosition(sf::Vector2f(temp, 0));

               // setAntiPipePos(antiPipes[i], )
                //temp = antiPipes[i].getPosition().x - 1;
                antiPipes[i].setPosition(sf::Vector2f( temp, antiPipes[i].getPosition().y) );
            }
            else{
                pipes[i].setPosition( sf::Vector2f( SCREEN_WIDTH, 0 ) );
                antiPipes[i].setPosition(pipes[i].getPosition().x, randHeight( SCREEN_HEIGHT ) );
            }
        }

        pipesClock.restart();
    }

}



