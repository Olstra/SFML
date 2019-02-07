/**
Bugs:
-

TODO:
- how many tubes do we really need ???

Ideas:
- variate distance of tubes for different game modus
- variate size of "anti-tubes"
- make pipes pass by faster

DONE:
x why do we get no bottoms ???
x time management
x Flappy square to circle
x tubes class/objects
x function - move flappy bird
x fix unschöne tubes abstand

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

    // Load a sprite to display
    Texture texture;
    if (!texture.loadFromFile("media/Untitled.png")){ std::cout<< "ERROR: Background could not be loaded" << std::endl; return -1; }
    Sprite sprite(texture);

    // Load font
    Font font;
    if( !font.loadFromFile("media/GojiraBlack.ttf")){ std::cout<< "ERROR: Font could not be loaded" << std::endl; return -1; }

    // Game over text
    Text txtGameOver("GAME OVER", font, 100);
    txtGameOver.setFillColor(Color::Red);
    FloatRect tempRect = txtGameOver.getLocalBounds();
    txtGameOver.setOrigin( tempRect.left + tempRect.width/2.0f, tempRect.top + tempRect.height/2.0f );
    txtGameOver.setPosition( SCREEN_WIDTH/2, SCREEN_HEIGHT/2 );

    // INIT STUFF
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
                            if( flappyBird.state != gameOver ) {
                                birdFly();
                            }
                            else { init(); }
                            break;

                        default: break;
                    }
            }
        }


        // handle movement
        if( flappyBird.state == flying || flappyBird.state == falling ) {
            movePipes( SCREEN_WIDTH, SCREEN_HEIGHT );
            moveBird( SCREEN_HEIGHT );
        }

        Vector2f flappyPos = flappyBird.shape.getPosition();
        for( int i = 0; i < NR_OF_PIPES; i++ ) {
            if( antiPipes[i].getGlobalBounds().contains( flappyPos )) { continue; }
            else if( pipes[i].getGlobalBounds().contains( flappyPos )) {
                flappyBird.state = gameOver;
            }

        }

        // Clear screen
        window.clear( Color::White );

        // Draw
        drawPipes( window );
        window.draw( flappyBird.shape );
        if( flappyBird.state == gameOver ) window.draw( txtGameOver );

        window.draw(sprite);
        window.display();

    }

    return 0;
}


void init() {
    srand(time(0));

    initPipes( SCREEN_WIDTH, SCREEN_HEIGHT );
    initBird( SCREEN_WIDTH, SCREEN_HEIGHT );

}








