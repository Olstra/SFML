/** New v.3.0 [16 Jan 2019]:
- implemented movement restriction (e.g. right->left not possible any more)
- nicer code for draw() function and tail movement for-loop
- fixed fruit positions (can now only appear inside walls)
- better/correct string display for score (with sstream instead of C style method)

TODOS:
- implement game over when you touch snake tail

KNOWN ISSUES:
? tail first appears in map at (0/0), why tho
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
using namespace sf;

// SFML stuff
const int S_WIDTH = 2000;
const int S_HEIGHT = 1500;
const int FONT_S = 50;

// Game stuff
const int H = 15;   // Dimensions of game walls
const int W = 30;
bool gameOver;
int score;
int snakePos[2];
int tailPos[100][2]; // store values for position(x/y)coordinates of snake tail as 2D array
int fruitPos[2];
int seed = static_cast<int>(time(0));

enum Movement { STOP, RIGHT, LEFT, UP, DOWN };
Movement dir;

void init() {
    srand(seed);
    gameOver = false;
    score = 0;
    dir = STOP;

    // set default starting position of player
    snakePos[0] = W/2; // x-coordinate of snake
    snakePos[1] = H/2; // y-coordinate of snake

    // starting position of fruit
    fruitPos[0] = 1 + rand()%(W-2); // minimum at 1 and max W-1(-min) because we want it inside the walls
    fruitPos[1] = 1 + rand()%(H-2);
}

void logic() {
    /* Responsible for:
        -Snake position (head and tail)
        -Fruit position
        -Game over
    */

    // Caution: update snake tail coordinates before snake head!
        // otherwise snake movement becomes ugly...

    // Tail of the snake
    if (score > 1) {
        for (int i = score-1; i > 0; i--) {
            tailPos[i][0] = tailPos[i-1][0];
            tailPos[i][1] = tailPos[i-1][1];
        }
    }
    if (score > 0) {
        tailPos[0][0] = snakePos[0];
        tailPos[0][1] = snakePos[1];
    }

    // handle moving of player [snake] left, right, up, down
    switch(dir) {
        case STOP:
            break;
        case LEFT:
            snakePos[0]--;
            break;
        case RIGHT:
            snakePos[0]++;
            break;
        case UP:
            snakePos[1]--;
            break;
        case DOWN:
            snakePos[1]++;
            break;
    }

    // we eat a fruit, snakeTail += 1
    if (snakePos[0] == fruitPos[0] && snakePos[1] == fruitPos[1]) {
        score++;    // increase score
        fruitPos[0] = 1 + rand()%(W-2);   // set coordinates for new fruit
        fruitPos[1] = 1 + rand()%(H-2);
    }

    // Game over when...
    if (snakePos[0] >= W || snakePos[0] <= 0 || snakePos[1] >= H || snakePos[1] <= 0) {
        gameOver = true;
    }
}

string draw() {
    // We draw the screen and its contents with the help of a loop that iterates from top to bottom, "row for row"

    string s;
    bool space; // flag that tells us when to draw an empty space character
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
                space = true;
                // walls
                if (y == 0 || x == 0 || y == H-1 || x == W-1) { s += "#"; space = false; }
                // snake head
                if (x == snakePos[0] && y == snakePos[1]) { s += "A"; space = false; }
                // snake head
                for (int i = 0; i < score; i++) { if (x == tailPos[i][0] && y == tailPos[i][1]) { s += "o"; space = false; } }
                // fruit
                if (x == fruitPos[0] && y == fruitPos[1]) { s += "*"; space = false; }
                // space between objects
                if(space) { s += " "; }
        }
        s += "\n";  // we draw a new line every time we reach W
    }

    // convert -int-score to -string-score
    string scoreS; stringstream ss;
    ss << score;
    scoreS = ss.str();
    s += "\n\nSCORE: "+ scoreS;
    s +=  "\n\n[x] EXIT";

return s;
}


int main() {
    // Create the main window
    RenderWindow app(VideoMode(S_WIDTH, S_HEIGHT), "Oliver Coding Snake");
    app.setFramerateLimit(10);
    // Get Fonts
    Font font; if (!font.loadFromFile("media/consolas.ttf")) { cout << "Error while loading font!" <<endl; return -1; }

    // set starting position of snake head
    snakePos[0] = W/2;
    snakePos[1] = H/2;

    init(); // initialize game

    // Logical gui (command line style)
    string gui = draw();
    Text text(gui, font, FONT_S);
    text.setFillColor(Color::Green);
    FloatRect textRect = text.getLocalBounds();     // set position at center of screen
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect .height/2.0f);
    text.setPosition(sf::Vector2f(S_WIDTH/2.0f,S_HEIGHT/2.0f));

    // game over display
    Text gameOverS("GAME OVER", font, 100);
    gameOverS.setFillColor(Color::Green);
    FloatRect textRect1 = gameOverS.getLocalBounds();     // set position at center of screen
    gameOverS.setOrigin(textRect1.left + textRect1.width/2.0f, textRect1.top  + textRect1 .height/2.0f);
    gameOverS.setPosition(Vector2f(S_WIDTH/2.0f,S_HEIGHT/2.0f));
    Vector2f goPos = gameOverS.getPosition();

    Text gameOverOptions("[x] EXIT\t\t\t\t\t\t\t\t[enter] PLAY AGAIN", font, FONT_S);
    gameOverOptions.setFillColor(Color::Green);
    FloatRect textRect2 = gameOverOptions.getLocalBounds();     // set position at center of screen
    gameOverOptions.setOrigin(textRect2.left + textRect2.width/2.0f, textRect2.top  + textRect2 .height/2.0f);
    gameOverOptions.setPosition( Vector2f(S_WIDTH/2.0f, S_HEIGHT-100) );

	// Start the game loop ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    while (app.isOpen()) {
        // Process events
        Event event;
        while (app.pollEvent(event)) {
            // Close window : exit
            if (event.type == Event::Closed) {  app.close();  }

            if(event.type ==  Event::KeyPressed) {
                switch (event.key.code) {
                    if (!gameOver) {    // player movement
                        case Keyboard::W:
                            if (dir != DOWN) { dir = UP; }
                            break;
                        case Keyboard::S:
                            if (dir != UP) { dir = DOWN; }
                            break;
                        case Keyboard::A:
                            if (dir != RIGHT) { dir = LEFT; }
                            break;
                        case Keyboard::D:
                            if (dir != LEFT) { dir = RIGHT; }
                            break;
                    }
                    else {
                        case Keyboard::Enter:   // player chooses "play again"
                            init();
                            break;
                    }
                    case Keyboard::X:
                        app.close();
                        break;
                    default: break;
                }
            }
        }

        // Clear screen
        app.clear();

        if (!gameOver) {
            logic();
            gui = draw();
            text.setString(gui);
            app.draw(text);
        }
        else {
                app.draw(gameOverS);
                app.draw(gameOverOptions);
        }

        // Update the window
        app.display();
    }

    return 0;
}
