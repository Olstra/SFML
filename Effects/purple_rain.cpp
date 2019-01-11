#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

using namespace sf;

/**
TODO:
- add music

Done:
X make size of drops variable
X add random speed per drop

Maybe:
? change opacity of raindrops to give effect of depth
*/


// window dimensions
const int W = 1500;
const int H = 1000;

// keep track of all drops
const int totalDrops = 1000;
RectangleShape rainDrops[totalDrops];
int wPosDrops[totalDrops];
int startHDrops[totalDrops];

int main() {

    // Create the main window
    RenderWindow window(VideoMode(W, H), "Purple rain", Style::Titlebar | Style::Close);
    window.setFramerateLimit(50);

    // create our colors
    Color background(58, 31, 85);
    Color dropColor(191,	127,	191);

    // Text stuff /////////////////////////////////////////////////////////////////////////////////////////////////////////
    Clock clock;
    Time waitTime = seconds(3);
    int transparency01 = 0;
    int transparency02 = 0;
    const int fontSize = 100;
    Font font;
    if ( !font.loadFromFile("media/cassandra.ttf")) { return -1; }

    Text text01("The first line", font, fontSize);
    FloatRect textRect = text01.getLocalBounds();     // set position at center of screen
    text01.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    text01.setPosition(Vector2f(W/2.0f, H/2.0f));

    Text text02("\n\n\n\n\n\n2nd line appears", font, fontSize);
    FloatRect textRect1 = text02.getLocalBounds();     // set position at center of screen
    text02.setOrigin(textRect1.left + textRect1.width/2.0f, textRect1.top  + textRect1.height/2.0f);
    text02.setPosition(Vector2f(W/2.0f, H/2.0f));

    // CREATE RAIN DROPS /////////////////////////////////////////////////////////////////////////////////
    srand((int)time(0));
    int startH, wPos, length, thickness;
    for (int i = 0; i < totalDrops; i++) {

        // create random variables for drops
        length = rand()%30;
        thickness = rand()%5;
        startH = (-300 + (rand()%(int)(-100 + 300 + 1)));
        wPos = (rand()%W)+1;

        rainDrops[i].setSize(Vector2f(thickness, length));
        rainDrops[i].setFillColor(dropColor);

        wPosDrops[i] = wPos;
        startHDrops[i] = startH;

        rainDrops[i].setPosition(wPosDrops[i], startHDrops[i]);
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Start the game loop
    while (window.isOpen()) {
        // Process events
        Event event;
        while (window.pollEvent(event)) {
            // Close window : exit
            if (event.type == Event::Closed) {  window.close();  }
        }

        // Clear screen
        window.clear(background);

        if (transparency01 < 255) { transparency01++; }
        Color txtColor(255, 255, 255, transparency01);
        text01.setColor(txtColor);

        if (clock.getElapsedTime() > waitTime) {
            window.draw(text02);
            if (transparency02 < 255) { transparency02++; }
            Color txtColor2(255, 255, 255, transparency02);
            text02.setColor(txtColor2);

        }

        // draw to screen
        window.draw(text01);

        // handle drops
        int fallSpeed;
        for(int i = 0; i < totalDrops; i++) {
                // draw drops
                window.draw(rainDrops[i]);
                // make rain drops fall
                fallSpeed = rand()%50;
                startHDrops[i] += fallSpeed;
                rainDrops[i].setPosition(wPosDrops[i], startHDrops[i]);
        }

        // reset raindrop to keep them falling
        for (int i = 0; i < totalDrops; i++) {
            if (startHDrops[i] > H) {
              startHDrops[i] =  (-300 + (rand()%(int)(-100 + 300 + 1)));
            }
        }

        window.display();
    }

    return 0;
}
