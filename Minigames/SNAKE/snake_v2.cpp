#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace sf;

/** TODOS
o BUGFIX: when score >4/5 ???
o use better string display for score (see when score>9)
o application crashes if one doesnt click anything for some seconds
- reorganize code structure
- chage snakePos& fruitPos to sf::vectors
x build in: play again feature
x fix game over directly when touch wall, not after
x use better random funtion
*/

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
int seed = static_cast<int>(time(0));       // LEARNING: seed needed to create better random numbers

enum Movement { STOP, RIGHT, LEFT, UP, DOWN };
Movement dir;

void init() {
    srand(seed);        // LEARNING: before this function call was placed at a -global scope- but this way this function call doesn't work
    gameOver = false;
    score = 0;
    dir = STOP;

    // set starting position of player
    snakePos[0] = W/2; // x coordinate of snake
    snakePos[1] = H/2;

    // starting position of fruit
    fruitPos[0] = rand()%W;
    fruitPos[1] = rand()%H;
}

void logic(sf::Clock clock) {
    /* Responsible for:
        -Snake position (head and tail)
        -Fruit position
        -Game over
    */

    // Tail of the snake
    Vector2i temp;
    temp.x = snakePos[0];
    temp.y= snakePos[1];
    Vector2i temp2;
    for(int i = 0; i < score; i++) {
        temp2.x = tailPos[i][0];
        temp2.y = tailPos[i][1];

        tailPos[i][0] = temp.x;
        tailPos[i][1] = temp.y;

        temp = temp2;
    }

    // handle moving of player [snake] left,right,up,down
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
        fruitPos[0] = rand()%W-1;   // set coordinates for new fruit
        fruitPos[1] = rand()%H-1;
    }

    // Game over when...
    if (snakePos[0] >= W || snakePos[0] <= 0 || snakePos[1] >= H || snakePos[1] <= 0) {
        gameOver = true;
        clock.restart();
    }
}

string draw() {
    /** We draw the screen and its contents with the help of a loop that iterates from top to bottom, "row for row" */

    string s;

    for (int i = 0; i < W + 2; i++) { s+= "#"; } // draw upper wall
	s+= "\n";

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (j == 0) { s += "#"; }

			if (i == snakePos[1] && j == snakePos[0]) { s += "A"; }

			else if (i == fruitPos[1] && j == fruitPos[0]) { s += "*"; }

			else {
				bool print = false;
				for (int k = 0; k < score; k++) {
					if (tailPos[k][0] == j &&tailPos[k][1] == i) {
						s += "o";
						print = true;
					}
				}
				if(!print) { s += " "; }
			}
			if (j == W - 1) { s += "#"; }
		}
		s+= "\n";
	}
	for (int i = 0; i < W + 2; i++) { s += "#"; }   // draw lower wall
	s += "\n";

	// c style conversion, since compiler doesn't supports to_string method ?
    int tempS = 4;
    char str[tempS];
    sprintf(str, "%d", score);
    string foo;
    for (int i = 0; i< tempS;i++) { foo += str[i]; }
    s += "\nSCORE: "+ foo.substr(0,1)  +"\n";   // because of display reasons we only display first char
    s +=  "\n[x] EXIT \n";

return s;
}


int main()
{
    // Create the main window
    RenderWindow app(VideoMode(S_WIDTH, S_HEIGHT), "SFML Snake");
    app.setFramerateLimit(10);
    // Get Fonts
    Font font; if (!font.loadFromFile("media/consolas.ttf")) { cout << "Error while loading font!" <<endl; }

    sf::Time delayTime = sf::seconds(1.5);
    sf::Clock clock;
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

	// Start the game loop
    while (app.isOpen()) {
        // Process events
        Event event;
        while (app.pollEvent(event)) {
            // Close window : exit
            if (event.type == Event::Closed) {  app.close();  }

            if(event.type ==  Event::KeyPressed) {
                switch (event.key.code) {

                    if (!gameOver) {
                        case Keyboard::W:
                            dir = UP;
                            break;
                        case Keyboard::S:
                            dir = DOWN;
                            break;
                        case Keyboard::A:
                            dir = LEFT;
                            break;
                        case Keyboard::D:
                            dir = RIGHT;
                            break;
                    }
                    else {
                        case Keyboard::Enter:   // player chooses [play again]
                            init();
                            clock.restart();
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
            logic(clock);
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

    return EXIT_SUCCESS;
}
