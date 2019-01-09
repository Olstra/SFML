/*
    Authot: Olstra
    Date: 09. Jan 2019
    Brief: Make text appear on the screen according different times
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace sf;

// Screen dimensions
int S_W = 2000;
int S_H = 1500;

int main()
{
    RenderWindow app(VideoMode(S_W, S_H), "Prototype");     // Create the main window
    Font font; if (!font.loadFromFile("consolas.ttf")) { cout << "Error while loading font!" <<endl; }  // Get Font

    Text text("Starting line...", font, 50);
    FloatRect textRect = text.getLocalBounds();     // set position at center of screen
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect .height/2.0f);
    text.setPosition(Vector2f(S_W/2.0f,S_H/3.0f));
    sf::Vector2f textPos = text.getPosition(); // get position to put other text relative to this position

    Text t1("New line appears!", font, 50);
    FloatRect textRect1 = t1.getLocalBounds();     // set position at center of screen
    t1.setOrigin(textRect1.left + textRect1.width/2.0f, textRect1.top  + textRect1 .height/2.0f);
    t1.setPosition(textPos.x, textPos.y + 150);
    sf::Vector2f t1Pos = t1.getPosition();

    Text t2("Exit with 'x'", font, 50);
    FloatRect textRect2 = t2.getLocalBounds();     // set position at center of screen
    t2.setOrigin(textRect2.left + textRect2.width/2.0f, textRect2.top  + textRect2 .height/2.0f);
    t2.setPosition(t1Pos.x, t1Pos.y + 150);

    sf::Time time01, time02;
    int ziit01 = 1.5; // zur verdeutlichung vom erwünschten effekt: text 3 soll später als text 2 erscheinen
    time01 = sf::seconds(ziit01);     // create time object to specify the time we want our 2nd text to apear
    time02 = sf::seconds(ziit01*2);
    // start clock (clock starts automatically after being created)
    Clock clock;        // Achtung: create clock outside game loop, other wise it will be created again between all iterations!

	// Start the game loop
    while (app.isOpen()) {
        // Process events
        Event event;
        while (app.pollEvent(event)) {
            // Close window : exit
            if (event.type == Event::Closed) { app.close(); }

             if(event.type ==  Event::KeyPressed) {
                switch (event.key.code) {
                    case Keyboard::X:   // quit application
                        app.close();
                        break;
                    default: break;
                }
            }
        }
        app.clear(sf::Color::Blue);    // Btw clear actually fills the screen with a colour (default is black)

//////////////////////////// MAIN EFFECT ///////////////////////////////////////////////////////////////

        app.draw(text);
        if ( clock.getElapsedTime() > time01 ) {
                app.draw(t1);
                if ( clock.getElapsedTime() > time02 ) { app.draw(t2); }
        }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
        app.display();  // Update the window
    }
    return EXIT_SUCCESS;
}
