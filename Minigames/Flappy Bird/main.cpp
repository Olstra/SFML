/**
Bugs:
-

TODO:
- nicer BG
- nicer Flappy bird
X nicer pipes
X add score count

for next update:
- score keeper

Ideas:
- variate distance of tubes for different game modus
- variate size of "anti-tubes"
- make pipes pass by faster

*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Pipes.h"
#include "Bird.h"

#include "icon.h"

using namespace sf;

//Screen dimension constants
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 800;

int score;
int idx;        // used to track pipes for score++

void init();    // initialize/reset game objects


int main() {

    // Create the main window
    RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "OLIVER CODES FLAPPY BIRD", sf::Style::Titlebar | sf::Style::Close);
    window.setIcon( flappy_icon.width, flappy_icon.height, flappy_icon.pixel_data );
    // SFML graphics stuff /////////////////////////////////////////////////////////////////////////////////////

    // Load background
    Texture bgTexture;
    if( !bgTexture.loadFromFile("media/background.png")){ std::cout<< "ERROR: Background could not be loaded" << std::endl; return -1; }
    Sprite bgSprite( bgTexture );

    // load (game over) menu
    Texture menu;
    if ( !menu.loadFromFile("media/menu.png") ) { std::cout << "ERROR: menu.png couldn't be loaded" << std::endl; return -1; }
    Sprite menuSprite( menu );
    menuSprite.setPosition( 100, 200 );

    // Load font
    Font font;
    if( !font.loadFromFile("media/Dyuthi.ttf")){ std::cout<< "ERROR: Font could not be loaded" << std::endl; return -1; }

    // score text
    Text scoreTxt( "0", font, 100 );
    FloatRect tempRect = scoreTxt.getLocalBounds();
    scoreTxt.setOrigin( tempRect.left+tempRect.width/2.0f, tempRect.top+tempRect.height/2.0f);
    scoreTxt.setPosition( SCREEN_WIDTH/2, 100 );
    scoreTxt.setFillColor( Color::Black );
    scoreTxt.setOutlineColor( Color::White );
    scoreTxt.setOutlineThickness( 3 );

    // game floor
    Color floorCol( 205, 215, 215 );
    RectangleShape gameFloor( Vector2f( 1200, 70 ) );
    gameFloor.setFillColor( floorCol );
    gameFloor.setPosition( Vector2f( 0, SCREEN_HEIGHT-gameFloor.getSize().y ) );

    //////////////////////////////////////////////////////////////////////////////////////////////////////

    // INIT GAME
    init();

    // Start the game loop
    while (window.isOpen()) {
        // Process events
        Event event;
        while (window.pollEvent(event)) {
            switch(event.type) {
                case Event::Closed: window.close(); break;

                case Event::KeyPressed:
                    switch (event.key.code) {

                        case Keyboard::Escape:
                            window.close();
                            break;

                        case Keyboard::Space:
                            if( flappyBird.state != gameOver ) { birdFly(); }
                            break;

                        case Keyboard::Return:
                            // re-play
                            if( flappyBird.state == gameOver ) {
                                init();
                                scoreTxt.setString( std::to_string( score ) ); // reset game score text
                            }
                            break;

                        default: break;
                    }

                default: break;
            }
        }

        // handle movement
        if( flappyBird.state == flying || flappyBird.state == falling ) {
            movePipes( SCREEN_WIDTH, SCREEN_HEIGHT );
            moveBird( SCREEN_HEIGHT );
        }

        // COLLISION detection
        // get current flappy bird position
        Vector2f flappyPos = flappyBird.sprite.getPosition();
        for( int i = 0; i < NR_OF_PIPES; i++ ) {
            if( pipesTopSprt[i].getGlobalBounds().contains( flappyPos ) || pipesBottomSprt[i].getGlobalBounds().contains( flappyPos ) ) {
                flappyBird.state = gameOver;
            }
        }

        // if pipe is behind flappyBird x pos score goes up
        if ( pipesBottomSprt[idx].getPosition().x < flappyPos.x ) {
            score++;
            scoreTxt.setString( std::to_string( score ) );
            // go to next pipe
            ( (idx+1) < NR_OF_PIPES ) ? idx++ : idx = 0;
        }

        // Clear screen
        window.clear( );

        // Draw
        window.draw( bgSprite );
        drawPipes( window );
        window.draw( flappyBird.sprite );
        window.draw( gameFloor );
        window.draw( scoreTxt );
        if( flappyBird.state == gameOver ) { window.draw( menuSprite ); }

        // display drawn stuff
        window.display();

    }

    return 0;
}


void init() {
    srand( time(0) );

    // reset score
    score = 0;
    idx = 0;

    initPipes( SCREEN_WIDTH, SCREEN_HEIGHT );
    initBird( SCREEN_WIDTH, SCREEN_HEIGHT );

}
