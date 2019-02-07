/**
    Here goes everything that has to do with the BIRD
        - create bird
        - move bird
*/

#include <SFML/Graphics.hpp>


int flappySize = 40;    // size of the flappy bird
int gravity = 10;
int pushBird = 125;     // jump height of bird
int jumpDuration = 200;
sf::Clock flappyClock;

enum BIRD_STATE { stealth, falling, flying, gameOver };

struct bird {

    sf::CircleShape shape;

    BIRD_STATE state;

}flappyBird;

void initBird( int SCREEN_WIDTH, int SCREEN_HEIGHT ) {

    flappyBird.shape.setRadius( flappySize );
    flappyBird.shape.setPosition(SCREEN_WIDTH * 0.3, SCREEN_HEIGHT / 2);
    flappyBird.shape.setFillColor(sf::Color::Black);

    flappyBird.state = stealth; // default init state
}

void birdFly() {

    int temp;

    if( flappyBird.state != flying ) {
        temp = flappyBird.shape.getPosition().y - pushBird;
        flappyBird.shape.setPosition(sf::Vector2f(flappyBird.shape.getPosition().x, temp));    // update position
        flappyBird.state = flying;
    }

}

void moveBird( int SCREEN_HEIGHT ) {

    int temp;

    // move flappy bird
    switch( flappyBird.state ) {
        case falling:
            if( flappyClock.getElapsedTime().asMilliseconds() >= gravity) {
                // make sure flappy bird doesn't fall off the screen
                if( flappyBird.shape.getPosition().y <= ( SCREEN_HEIGHT - flappyBird.shape.getRadius() )) {
                    temp = flappyBird.shape.getPosition().y + gravity;
                    flappyBird.shape.setPosition(sf::Vector2f(flappyBird.shape.getPosition().x, temp));

                    flappyClock.restart();
                }
                else { flappyBird.state = gameOver; }
            }

            break;

        case flying:
            if(flappyClock.getElapsedTime().asMilliseconds() >= jumpDuration) {
                flappyBird.state = falling;
                flappyClock.restart();
            }
            break;

        case stealth:
            break;
    }

}


