//============================================================================
// Name        : Snake
// Author      : Oliver
// Version     : v.1.0
// Description : Snake console game
//============================================================================

/** First try at snake game - Jan 03 2019
* Requirements notes:
	* We imagine we are in a raster-system of Height*Width
	* Fruit appears at rand()[om] position on this raster
	* We begin in the middle of the screen (not moving)
	* if we hit a wall or our tail, we die
	* Pressing on arrow keys changes direction
	* That's it ?
**/

#include <iostream>
#include <random>
#include <conio.h>

using namespace std;

const int H = 20;
const int W = 40;
bool gameOver;
int score;
int snakePos[2];
string snake = "O";
int fruitPos[2];

enum Movement { STOP, RIGHT, LEFT, UP, DOWN };
Movement dir;

void init() {

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

void logic() {
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
        score++;
        fruitPos[0] = rand()%W;
        fruitPos[1] = rand()%H;
        snake += "-";
    }

    if (snakePos[0] > W || snakePos[1] > H) {
        gameOver = true;
    }

    // Game over?
}

void draw() {
    /** We draw the screen and its contents with the help of a loop that iterates from top to bottom, "row for row" */
    system("CLS");

    for (int y = 0; y < H; y++) {
        for(int x = 0; x < W; x++) {
            // draw walls
            if ( x == 0 || x == W-1 || y == 0 || y == H-1 ) { cout << "#"; }
            // draw player/snake
            else if(x == snakePos[0] && y == snakePos[1]) { cout << snake; }
            // draw fruit
            else if(x == fruitPos[0] && y == fruitPos[1]) { cout << "X"; }
            // fill the remaining space
            else { cout << " "; } // LEARNING: you also have to print the space, since its only a raster in our heads, but not for the console!
        }
        cout << "\n";
    }
    cout << "Score: " << score << endl;
    cout << "[x] exit" << endl;
}

void input() {

    if(_kbhit()) {
        switch (_getch()) {
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}


int main() {

    system("CLS");

    init();
    while(!gameOver) {
        logic();
        draw();
        input();
    }

    cin.ignore();

    return 0;
}
