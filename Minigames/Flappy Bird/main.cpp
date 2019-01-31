/**

LEARNINGS:
- vector cannot be initialized inside struct instead in main function

*/


#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

const int windowW = 800;
const int windowH = 800;

//our flappy bird object
struct theFlappyBird{

    sf::Vector2f pos;

    float vel = 20.0f;

    sf::Sprite flappySprite;

}flappyBird;



int main() {

    // Create the main window
    RenderWindow window(sf::VideoMode(windowW, windowH), "OLIVER CODES FLAPPY BIRD", sf::Style::Titlebar | sf::Style::Close);

    // Load a sprite to display
    Texture texture;
    if (!texture.loadFromFile("cb.bmp")){ std::cout<< "ERROR: Background could not be loaded" << std::endl; return -1; }

    // init flappy bird ///////////////////////////////////////////////////////////////////////////////////////////////////

    flappyBird.pos.x = windowW/2;
    flappyBird.pos.y = windowH/2;

    flappyBird.flappySprite.setTexture(texture);


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // manage time
    Clock clock;
    Time elapsedTime;
    Time delay = seconds(1);

    const int gravity = 20;


	// Start the game loop
    while (window.isOpen()) {
        // Process events
        Event event;
        while (window.pollEvent(event)) {
            switch(event.type) {
                case Event::Closed: window.close(); break;

                case Event::KeyPressed:
                    switch (event.key.code) {

                        case Keyboard::Space:
                            flappyBird.pos.y -= flappyBird.vel;

                        break;

                        default: break;
                    }
            }
        }

        // force of gravity
        if(clock.getElapsedTime().asSeconds() > delay.asSeconds()) { flappyBird.pos.y += gravity; clock.restart(); }


        // Clear screen
        window.clear();

        // update flappy bird position
        flappyBird.flappySprite.setPosition(flappyBird.pos);

        // Draw
        window.draw(flappyBird.flappySprite);

        // Update the window
        window.display();
    }

    return 0;
}
