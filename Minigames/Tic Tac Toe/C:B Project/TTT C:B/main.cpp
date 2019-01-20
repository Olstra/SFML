/** NOTES

NEW:
- implemented game delay
- nicer GUI

BUGS:
-

TODOS:
-

FIXED/DONE:
- bug if everything is clicked
- make init() function
- what happens when draw
- nicer display of game board/buttons in middle
- change either esc with 'x' or change grpahic =>none is necessary
- logic is the same as coloring of buttons
*/

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

// game stuff
const int windowW = 800;
const int windowH = 800;
bool playerTurn;
int turnsTaken;

// GUI COLORS
Color startColor(0, 30, 175);
Color playerColor(255, 70, 65);
Color AIColor(60, 150, 255);
Color BGColor(35, 30, 65);

// create game board 3x3
sf::RectangleShape board[3][3];

// different game states used to display according background
enum GameState {
    mainPlay, gameOver, youWin, itsADraw
}currentState;  // define current state of the game

void gameLogicWithColors () {
    // count how manx boxes have been clicked
    int tempCounter = 0;
    for(int i = 0; i <3; i++) { for(int j = 0; j < 3; j++) {
        if(board[i][j].getFillColor() != startColor) { tempCounter++;  } } }
        std::cout << tempCounter << std::endl;

    // if counter >= 3 check if someone has won
    if( tempCounter >= 3) {
        // check top to bottm side to side
        for(int i = 0; i < 3; i++) {
            // check top to bottom
            if(board[i][0].getFillColor() == board[i][1].getFillColor() && board[i][1].getFillColor() == board[i][2].getFillColor()) {
                if(board[i][0].getFillColor() == playerColor) { currentState = youWin; return; }
                else if (board[i][0].getFillColor() == AIColor) { currentState = gameOver; return; }
            }
            // check for win from left to right
            else if(board[0][i].getFillColor() == board[1][i].getFillColor() && board[1][i].getFillColor() == board[2][i].getFillColor()) {
                if(board[0][i].getFillColor() == playerColor) { currentState = youWin; return; }
                else if (board[0][i].getFillColor() == AIColor) { currentState = gameOver; return; }
            }
        }

        // check the cross "X"
        // from Top left to Bottom right: [0][0] == [1][1] == [2][2]
        if( board[0][0].getFillColor()  == board[1][1].getFillColor() && board[1][1].getFillColor() == board[2][2].getFillColor() ) {
            if(board[0][0].getFillColor() == playerColor) { currentState = youWin; return; }
            else if (board[0][0].getFillColor() == AIColor) { currentState = gameOver; return; }
        }
        // from Bottom left to Top right: [0][2] == [1][1] == [2][0]
        if( board[0][2].getFillColor()  == board[1][1].getFillColor()  &&  board[1][1].getFillColor() == board [2][0].getFillColor()  ) {
            if(board[0][2].getFillColor() == playerColor) { currentState = youWin; return; }
            else if (board[0][2].getFillColor() == AIColor) { currentState = gameOver; return; }
        }
    }

    // if noone has won its a draw
    if(tempCounter >= 9){ currentState = itsADraw; }

}

// AI chooses a random button
sf::Vector2i AILogic() {

    sf::Vector2i selectedButton;
    selectedButton.x = rand() % 3;
    selectedButton.y = rand() % 3;

    return selectedButton;
}

void placeButtons(sf::RectangleShape baseButton) {

    // set origin of baseButton to center of button instead of upper left corner
    FloatRect tempRect = baseButton.getLocalBounds();
    baseButton.setOrigin(tempRect.left+tempRect.width/2.0f, tempRect.top+tempRect.height/2.0f);

    // initialize buttons
    for(int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            board[x][y] = baseButton;
        }
    }

    // set position of buttons = #
    int offset = windowW/4;

    // middle button goes on center
    board[1][1].setPosition(windowW/2, windowH/2);
    Vector2f centerPos = board[1][1].getPosition();

    board[1][2].setPosition(centerPos.x, centerPos.y+offset); // lower middle

    board[1][0].setPosition(centerPos.x, centerPos.y-offset); // upper middle

    board[0][0].setPosition(centerPos.x-offset, centerPos.y-offset);

    board[0][2].setPosition(centerPos.x-offset, centerPos.y+offset); // lower left

    board[0][1].setPosition(centerPos.x-offset, centerPos.y); // middle left

    board[2][0].setPosition(centerPos.x+offset, centerPos.y-offset); // upper right

    board[2][1].setPosition(centerPos.x+offset, centerPos.y); // middle right

    board[2][2].setPosition(centerPos.x+offset, centerPos.y+offset);

}

void init() {
    // initialize variables needed for the game
    playerTurn = true;
    currentState = mainPlay;
    turnsTaken = 0;
    srand(time(0));

    // define how the buttons should look
    RectangleShape baseButton;
    baseButton.setSize(Vector2f(windowW/5, windowH/5));
    baseButton.setFillColor(startColor);

    placeButtons(baseButton);

}


int main() {

    // SETUP /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Create the main window
    RenderWindow window(VideoMode(windowW, windowH), "Oliver Codes Tic Tac Toe", Style::Titlebar | Style::Close);

    // create strings to display current game state
    Font font;
    if(!font.loadFromFile("media/GojiraBlack.ttf")) { std::cout << "ERROR: font could not be loaded." << std::endl; return -1; }

    const int fontSize = 100;

    // create display text (for different game states)

    Text txtMainPlay("CLICK ON A BOX TO SELECT IT", font, fontSize/2);
    txtMainPlay.setStyle(Text::Italic);
    txtMainPlay.setFillColor(Color::White);

    Text txtGameOver("GAME OVER", font, fontSize);
    txtGameOver.setStyle(Text::Underlined | Text::Bold);
    txtGameOver.setFillColor(Color::Red);

    Text txtWin("YOU WIN!\n\t:-)", font, fontSize);
    txtWin.setStyle(Text::Bold);
    txtWin.setFillColor(Color::Green);

    Text txtDraw("IT'S A DRAW...?!", font, fontSize);
    txtDraw.setStyle(Text::Bold);
    txtDraw.setFillColor(Color::White);

    Text txtInfo("HIT ENTER TO PLAY AGAIN", font, fontSize/2);
    txtInfo.setStyle(Text::Italic);
    txtInfo.setFillColor(Color::White);

    // set positions of text

    // display tutorial & info text on bottom of window
    FloatRect tempRect = txtMainPlay.getLocalBounds();
    txtMainPlay.setOrigin(tempRect.left+tempRect.width/2.0f, tempRect.top+tempRect.height/2.0f);
    txtMainPlay.setPosition(windowW/2, windowH/15*14);

    tempRect = txtInfo.getLocalBounds();
    txtInfo.setOrigin(tempRect.left+tempRect.width/2.0f, tempRect.top+tempRect.height/2.0f);
    txtInfo.setPosition(windowW/2, windowH/15*14);

    // other text will be displayed in middle of window
    tempRect = txtDraw.getLocalBounds();
    txtDraw.setOrigin(tempRect.left+tempRect.width/2.0f, tempRect.top+tempRect.height/2.0f);
    txtDraw.setPosition(windowW/2, windowH/2);

    tempRect = txtGameOver.getLocalBounds();
    txtGameOver.setOrigin(tempRect.left+tempRect.width/2.0f, tempRect.top+tempRect.height/2.0f);
    txtGameOver.setPosition(windowW/2, windowH/2);

    tempRect = txtWin.getLocalBounds();
    txtWin.setOrigin(tempRect.left+tempRect.width/2.0f, tempRect.top+tempRect.height/2.0f);
    txtWin.setPosition(windowW/2, windowH/2);

    // Clock for ingame delays
    Clock clock;
    Time delay = seconds(0.5);

    // Start the game loop /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    init(); // initialize the game for the first time
    while (window.isOpen()) {
        // Process events
        Event event;
        while (window.pollEvent(event)) {
            switch(event.type) {
                case Event::Closed: window.close(); break;

                case Event::KeyPressed:
                    switch (event.key.code) {

                        case Keyboard::Return: // changed name in from 'enter' in windows
                            // player chooses "play (again)"
                            if(currentState != mainPlay) {
                                init(); // reset the games
                            }
                            break;

                        case Keyboard::Escape:
                            window.close();
                            break;

                        default: break;
                    }
            }
        }


        // Check for left mouse click ////////////////////////////
        // it's the players turn
        if(playerTurn) {
            if (Mouse::isButtonPressed(Mouse::Left)) {
                for(int x = 0; x < 3; x++) { for (int y = 0; y < 3; y++) {
                        if ( board[x][y].getGlobalBounds().contains
                            (Mouse::getPosition(window).x, Mouse::getPosition(window).y) ) { // get the current position of the mouse inside the window
                                if(board[x][y].getFillColor() == startColor) { // meaning this is the first time we click on the button
                                    board[x][y].setFillColor(playerColor); // change color of the button that was clicked
                                    playerTurn = false;
                                    turnsTaken++;
                                }
                        }
                    }
                }
            }
        }
        // it's AIs turn
        if(turnsTaken<9) {
            if(!playerTurn) {
                Vector2i temp;
                // AI chooses its button
                do { temp = AILogic();
                }while (board[temp.x][temp.y].getFillColor() != startColor); // meaning this is the first time we click on the button

                board[temp.x][temp.y].setFillColor(AIColor);
                playerTurn = true;
                turnsTaken++;

            }
        }
        //////////////////////////////////////////////////////////////

        // run game logic
        gameLogicWithColors();

        // Clear screen
        window.clear(BGColor);

         // draw backgrounds according to current game state
        switch(currentState) {

            case mainPlay:
                window.draw(txtMainPlay);
                // draw the buttons/game board
                for (int x = 0; x < 3; x++) { for (int y = 0; y < 3; y++) { window.draw(board[x][y]); }}
                break;

            case gameOver:
            // wait a lil to display
                clock.restart();
                while(clock.getElapsedTime().asSeconds() < delay.asSeconds()) {continue;}
                window.draw(txtGameOver);
                window.draw(txtInfo);
                break;

            case youWin:
                clock.restart();
                while(clock.getElapsedTime().asSeconds() < delay.asSeconds()) {continue;}
                window.draw(txtWin);
                window.draw(txtInfo);
                break;

            case itsADraw:
                clock.restart();
                while(clock.getElapsedTime().asSeconds() < delay.asSeconds()) {continue;}
                window.draw(txtDraw);
                window.draw(txtInfo);
                break;
        }

        // Update the window
        window.display();
    }

    return 0;
}
