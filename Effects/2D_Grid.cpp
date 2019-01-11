#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

const int windowW = 1500;
const int windowH = 1500;

const int terrainW = 1500;
const int terrainH = 1500;
const int scale = 50;

int main() {

    int columns = terrainW/scale;
    int rows = terrainH/scale;
    int totRects = rows*columns;

    // template square to multiply
    RectangleShape baseRect;
    baseRect.setSize(Vector2f(50, 50));
    baseRect.setFillColor(Color::Transparent);
    baseRect.setOutlineColor(Color::Green);
    baseRect.setOutlineThickness(2);

    RectangleShape rects[totRects];
    int i = 0;
      for (int y = 0; y < rows; y++) {
            for (int x = 0; x < columns; x++) {
                rects[i] = baseRect;
                rects[i].setPosition(x*scale, y*scale);

                if(i<totRects) { i++; }
            }
      }

    RenderWindow window(VideoMode(windowW, windowH), "2D Grid", Style::Close | Style::Titlebar);

	// Start the game loop
    while (window.isOpen()) {
        // Process events
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {  window.close();  }

            if(event.type ==  Event::KeyPressed) {
                switch (event.key.code) {
                        case Keyboard::Enter:
                            break;
                        default: break;
                }
            }
        }

        // Clear screen
        window.clear(Color::Blue);

        for (int j = 0; j < totRects; j++) { window.draw(rects[j]); }

        // Update the window
        window.display();
    }

    return 0;
}
