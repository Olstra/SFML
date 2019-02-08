/**
Bugs:
-

TODO:
- add score count

Ideas:
- variate distance of tubes for different game modus
- variate size of "anti-tubes"
- make pipes pass by faster

*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Pipes.h"
#include "Bird.h"

using namespace sf;

//Screen dimension constants
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 1000;

void init();    // initialize/reset game objects


int main() {

    // Create the main window
    RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "OLIVER CODES FLAPPY BIRD", sf::Style::Titlebar | sf::Style::Close);

    // SFML graphics stuff /////////////////////////////////////////////////////////////////////////////////////

    // Load background
    Texture bgTexture;
    if( !bgTexture.loadFromFile("media/background.png")){ std::cout<< "ERROR: Background could not be loaded" << std::endl; return -1; }
    Sprite bgSprite( bgTexture );

    // Load font
    Font font;
    if( !font.loadFromFile("media/GojiraBlack.ttf")){ std::cout<< "ERROR: Font could not be loaded" << std::endl; return -1; }

    // Game over text
    Text txtGameOver("GAME OVER", font, 120);
    txtGameOver.setFillColor(Color::Red);
    txtGameOver.setStyle(Text::Bold);
    FloatRect tempRect = txtGameOver.getLocalBounds();
    txtGameOver.setOrigin( tempRect.left + tempRect.width/2.0f, tempRect.top + tempRect.height/2.0f );
    txtGameOver.setPosition( SCREEN_WIDTH/2, SCREEN_HEIGHT/2 );

    Text txtReplay("hit enter to play again", font, 70);
    txtReplay.setFillColor(Color::Yellow);
    tempRect = txtReplay.getLocalBounds();
    txtReplay.setOrigin( tempRect.left + tempRect.width/2.0f, tempRect.top + tempRect.height/2.0f );
    txtReplay.setPosition( SCREEN_WIDTH/2, SCREEN_HEIGHT*0.8 );

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
                            if( flappyBird.state == gameOver ) { init(); } // re-play
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

        // check for collision
        Vector2f flappyPos = flappyBird.sprite.getPosition();
        for( int i = 0; i < NR_OF_PIPES; i++ ) {
            if( pipesTop[i].getGlobalBounds().contains( flappyPos ) || pipesBottom[i].getGlobalBounds().contains( flappyPos ) ) {
                flappyBird.state = gameOver;
            }

        }


        // Clear screen
        window.clear( );


        // Draw
        window.draw( bgSprite );
        drawPipes( window );
        window.draw( flappyBird.sprite );
        if( flappyBird.state == gameOver ) {
            window.draw(txtReplay);
            window.draw( txtGameOver );

        }

        // display drawn stuff
        window.display();

    }

    return 0;
}


void init() {
    srand(time(0));

    initPipes( SCREEN_WIDTH, SCREEN_HEIGHT );
    initBird( SCREEN_WIDTH, SCREEN_HEIGHT );

}








