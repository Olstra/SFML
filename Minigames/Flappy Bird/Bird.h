/**
    Here goes everything that has to do with the BIRD
        - create bird
        - move bird
*/

#include <SFML/Graphics.hpp>

// movement of flappy bird
int gravity = 60;
int pushBird = 120;     // jump height of bird
int jumpDuration = 200;

int flappySize = 40;    // size of the flappy bird
sf::Clock flappyClock;
sf::Texture textureBird;
int spriteSize = 50;    // sprite of flappy bird is a square of 80x80 pixels


enum BIRD_STATE { stealth, falling, flying, gameOver };

struct bird {

    sf::Sprite sprite;

    BIRD_STATE state;

}flappyBird;

void initBird( int SCREEN_WIDTH, int SCREEN_HEIGHT ) {

    // Load and set texture for flappysprite
    if ( !textureBird.loadFromFile("media/flappy_bird.png") ){ std::cout<< "ERROR: Texture could not be loaded" << std::endl; }
    flappyBird.sprite.setTexture(textureBird);
    flappyBird.sprite.setTextureRect( sf::IntRect(0, 0, spriteSize, spriteSize) ); // stealth brid pic

    flappyBird.sprite.setPosition( SCREEN_WIDTH * 0.3, SCREEN_HEIGHT / 2 );

    flappyBird.state = stealth; // default init state
}

void birdFly() {

    int temp;

    if( flappyBird.state != flying ) {
        temp = flappyBird.sprite.getPosition().y - pushBird;
        flappyBird.sprite.setPosition( sf::Vector2f( flappyBird.sprite.getPosition().x, temp ) );    // update position

        flappyBird.state = flying;
    }

}

void moveBird( int SCREEN_HEIGHT ) {

    int temp;

    // move flappy bird
    switch( flappyBird.state ) {
        case falling:
            if( flappyClock.getElapsedTime().asMilliseconds() >= gravity) {
                // make sure flappy bird doesn't fall off the screen (-100 because of floor)
                if( flappyBird.sprite.getPosition().y <= ( SCREEN_HEIGHT - spriteSize - 100 )) {
                    temp = flappyBird.sprite.getPosition().y + gravity;
                    flappyBird.sprite.setPosition(sf::Vector2f(flappyBird.sprite.getPosition().x, temp));

                    flappyClock.restart();
                }
                else { flappyBird.state = gameOver; }
            }
            flappyBird.sprite.setTextureRect( sf::IntRect(160, 0, 80, 80) );
            break;

        case flying:
            if(flappyClock.getElapsedTime().asMilliseconds() >= jumpDuration) {
                flappyBird.state = falling;
                flappyClock.restart();
            }

            flappyBird.sprite.setTextureRect( sf::IntRect(80, 0, 80, 80) ); // update sprite
            break;

        case stealth:
            flappyBird.sprite.setTextureRect( sf::IntRect(0, 0, spriteSize, spriteSize) ); // stealth brid pic
            break;
    }

}
