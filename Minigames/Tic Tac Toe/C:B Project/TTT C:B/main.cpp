/** NOTES

TODOS:
X implement lag for AI
X show last move
X implement game modus menu
X put all text entities into array and loop to set origin

NEW:
- Play vs friend
- smart PC moves instead of random

BUGS:
-

FIXED/DONE:
X implement lag for AI
X make smart AI

*/

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

// game stuff
const int windowW = 1500;
const int windowH = 1500;
bool playerTurn;
int turnsTaken;

// GUI COLORS
Color startColor(255, 255, 255);
Color playerColor(220,20,60);
Color AIColor(0,191,255);
Color BGColor(10, 10, 10);

// create game board 3x3
sf::RectangleShape board[3][3];

// different game states used to display according background
enum GameState {
    mainPlay, gameOver, youWin, itsADraw, player02Wins, player02Loses, gameMenu
}currentState;  // define current state of the game

enum GameModus {
    vsDumbAI, vsSmartAI, vsFriend
}gameModus;

void gameLogicWithColors () {

    // first check game modus to display correct winning/losing screens
    GameState player01Loses, player01Wins;
    switch(gameModus) {
        case vsFriend:
        player01Wins = player02Loses;
        player01Loses = player02Wins;
        break;

        default:
        player01Wins = youWin;
        player01Loses = gameOver;
        break;

    }

    // if >= 3 moves have been made check if someone has won
    if( turnsTaken >= 3) {
        // check top to bottm side to side
        for(int i = 0; i < 3; i++) {
            // check top to bottom
            if(board[i][0].getFillColor() == board[i][1].getFillColor() && board[i][1].getFillColor() == board[i][2].getFillColor()) {
                if(board[i][0].getFillColor() == playerColor) { currentState = player01Wins; return; }
                else if (board[i][0].getFillColor() == AIColor) { currentState = player01Loses; return; }
            }
            // check for win from left to right
            else if(board[0][i].getFillColor() == board[1][i].getFillColor() && board[1][i].getFillColor() == board[2][i].getFillColor()) {
                if(board[0][i].getFillColor() == playerColor) { currentState = player01Wins; return; }
                else if (board[0][i].getFillColor() == AIColor) { currentState = player01Loses; return; }
            }
        }

        // check the cross "X"
        // from Top left to Bottom right: [0][0] == [1][1] == [2][2]
        if( board[0][0].getFillColor()  == board[1][1].getFillColor() && board[1][1].getFillColor() == board[2][2].getFillColor() ) {
            if(board[0][0].getFillColor() == playerColor) { currentState = player01Wins; return; }
            else if (board[0][0].getFillColor() == AIColor) { currentState = player01Loses; return; }
        }
        // from Bottom left to Top right: [0][2] == [1][1] == [2][0]
        if( board[0][2].getFillColor()  == board[1][1].getFillColor()  &&  board[1][1].getFillColor() == board [2][0].getFillColor()  ) {
            if(board[0][2].getFillColor() == playerColor) { currentState = player01Wins; return; }
            else if (board[0][2].getFillColor() == AIColor) { currentState = player01Loses; return; }
        }
    }

    // if noone has won its a draw
    if(turnsTaken >= 9){ currentState = itsADraw; }

}

void randAIMove() {
    // AI chooses a random button

    sf::Vector2i selectedButton;
    // AI chooses its button
    do {
        selectedButton.x = rand() % 3;
        selectedButton.y = rand() % 3;
    }while (board[selectedButton.x][selectedButton.y].getFillColor() != startColor);

    board[selectedButton.x][selectedButton.y].setFillColor(AIColor);

    return;

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
    int offset = windowW/5;

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
    baseButton.setSize(Vector2f(windowW/7, windowH/7));
    baseButton.setFillColor(startColor);

    placeButtons(baseButton);

}

void player01Move(int x, int y) {

    board[x][y].setFillColor(playerColor); // change color of the button that was clicked

    playerTurn = false;
    turnsTaken++;

}

void player02Move(int x, int y) {

    board[x][y].setFillColor(AIColor); // change color of the button that was clicked

    playerTurn = true;
    turnsTaken++;

}

void smartAIMove() {

    playerTurn = true;
    turnsTaken++;

    // check if player has 2 boxes next to each other, then 'block' the third one
    if(turnsTaken >= 3) {

        for(int y = 0; y < 3; y++) {
            // check for almost win from LEFT TO RIGHT
            if(board[0][y].getFillColor() == playerColor && board[1][y].getFillColor() == playerColor) {
                if(board[2][y].getFillColor() == startColor) { board[2][y].setFillColor(AIColor); return; }
            }
            else if(board[1][y].getFillColor() == playerColor && board[2][y].getFillColor() == playerColor) {
                if(board[0][y].getFillColor() == startColor) { board[0][y].setFillColor(AIColor); return; }
            }
            else if(board[0][y].getFillColor() == playerColor && board[2][y].getFillColor() == playerColor) {
                if(board[1][y].getFillColor() == startColor) { board[1][y].setFillColor(AIColor); return; }
            }

            // check for almost win from TOP TO BOTTOM
            else if(board[y][0].getFillColor() == playerColor && board[y][1].getFillColor() == playerColor) {
                if(board[y][2].getFillColor() == startColor) { board[y][2].setFillColor(AIColor); return; }
            }
            else if(board[y][1].getFillColor() == playerColor && board[y][2].getFillColor() == playerColor) {
                if(board[y][0].getFillColor() == startColor) { board[y][0].setFillColor(AIColor); return; }
            }
            else if(board[y][0].getFillColor() == playerColor && board[y][2].getFillColor() == playerColor) {
                if(board[y][1].getFillColor() == startColor) { board[y][1].setFillColor(AIColor); return; }
            }
        }

        // check DIAGONAL
        if(board[0][0].getFillColor() == playerColor && board[1][1].getFillColor() == playerColor) {
            if(board[2][2].getFillColor() == startColor) { board[2][2].setFillColor(AIColor); return; }
        }
        else if(board[1][1].getFillColor() == playerColor && board[2][2].getFillColor() == playerColor) {
            if(board[0][0].getFillColor() == startColor) { board[0][0].setFillColor(AIColor); return; }
        }
        else if(board[0][0].getFillColor() == playerColor && board[2][2].getFillColor() == playerColor) {
            if(board[1][1].getFillColor() == startColor) { board[1][1].setFillColor(AIColor); return; }
        }

        if(board[0][2].getFillColor() == playerColor && board[1][1].getFillColor() == playerColor) {
            if(board[2][0].getFillColor() == startColor) { board[2][0].setFillColor(AIColor); return; }
        }
        else if(board[1][1].getFillColor() == playerColor && board[2][0].getFillColor() == playerColor) {
            if(board[0][2].getFillColor() == startColor) { board[0][2].setFillColor(AIColor); return; }
        }
        else if(board[0][2].getFillColor() == playerColor && board[2][0].getFillColor() == playerColor) {
            if(board[1][1].getFillColor() == startColor) { board[1][1].setFillColor(AIColor); return; }
        }

    }

    // default if no smart move possible
    randAIMove();

}



int main() {

    // SETUP /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Create the main window
    RenderWindow window(VideoMode(windowW, windowH), "Oliver Codes Tic Tac Toe", Style::Titlebar | Style::Close);

    // create strings to display current game state
    Font font;
    if(!font.loadFromFile("media/GojiraBlack.ttf")) { std::cout << "ERROR: font could not be loaded." << std::endl; return -1; }

    const int fontSize = 200;

    // create display TEXT (for different game states & game info)

    std::string textText[] = {"IT'S A DRAW...?!", "YOU WIN!\n\t:-)", "GAME OVER", "PLAYER 01 WINS!\n\t:-D", "PLAYER 02 WINS!\n\tB-)",
    "CLICK ON A BOX TO SELECT IT", "HIT ENTER TO PLAY AGAIN", "select game mode:", "VS COMPUTER", "PLAY WITH FRIEND", "Tic Tac Toe"};

    Text textes[11];
    FloatRect tempRect;

    for(int i = 0; i < 11; i++) {
        textes[i].setString(textText[i]);
        textes[i].setFont(font);
    }

    for(int i = 0; i < 5; i++) {
        textes[i].setCharacterSize(fontSize);
        tempRect = textes[i].getLocalBounds();
        textes[i].setOrigin(tempRect.left+tempRect.width/2.0f, tempRect.top+tempRect.height/2.0f);
        textes[i].setPosition(windowW/2, windowH/2);
        // winning screen = green
        if(i == 1 || i == 3 || i == 4) { textes[i].setFillColor(Color::Green); }
        else if(i == 4) { textes[i].setFillColor(Color::Red); }
    }

    for (int i = 5; i < 10; i++) { textes[i].setCharacterSize(fontSize/3); }

    tempRect = textes[5].getLocalBounds();
    textes[5].setOrigin(tempRect.left+tempRect.width/2.0f, tempRect.top+tempRect.height/2.0f);
    textes[5].setPosition(windowW/2, windowH/15*14); // "CLICK ON A BOX TO SELECT IT"

    tempRect = textes[6].getLocalBounds();
    textes[6].setOrigin(tempRect.left+tempRect.width/2.0f, tempRect.top+tempRect.height/2.0f);
    textes[6].setPosition(windowW/2, windowH/15*14); // "HIT ENTER TO PLAY AGAIN"

    tempRect = textes[7].getLocalBounds();
    textes[7].setOrigin(tempRect.left+tempRect.width/2.0f, tempRect.top+tempRect.height/2.0f);
    textes[7].setPosition(windowW/2, windowH/2); // "select game mode:"

    tempRect = textes[8].getLocalBounds();
    textes[8].setOrigin(tempRect.left+tempRect.width/2.0f, tempRect.top+tempRect.height/2.0f);
    textes[8].setPosition(windowW/2, windowH*0.65); // "VS COMPUTER"
    textes[8].setFillColor(Color::Yellow);

    tempRect = textes[9].getLocalBounds();
    textes[9].setOrigin(tempRect.left+tempRect.width/2.0f, tempRect.top+tempRect.height/2.0f);
    textes[9].setPosition(windowW/2, windowH*0.75); // "PLAY WITH FRIEND"
    textes[9].setFillColor(Color::Yellow);

    tempRect = textes[10].getLocalBounds();
    textes[10].setOrigin(tempRect.left+tempRect.width/2.0f, tempRect.top+tempRect.height/2.0f);
    textes[10].setPosition(250, 100); // "Tic Tac Toe"
    textes[10].setCharacterSize(fontSize);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // TIME management for ingame delays
    Clock clock;
    Time delay = milliseconds(1250);

    sf::Vector2i mousePos;


    // Start the game loop /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    currentState = gameMenu; // per default we start with game menu
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
                            if(currentState != mainPlay) { init(); }
                            break;

                        case Keyboard::Escape:
                            window.close();
                            break;

                        default: break;

                    }

                // Check for left mouse click ////////////////////////////
                case Event::MouseButtonPressed:
                    if (Mouse::isButtonPressed(Mouse::Left)) {
                        switch (currentState) {
                            case gameMenu:
                                mousePos = Mouse::getPosition(window); //get coordinates of mouse position

                                if(textes[8].getGlobalBounds().contains(mousePos.x, mousePos.y)) { gameModus = vsSmartAI; }
                                else if(textes[9].getGlobalBounds().contains(mousePos.x, mousePos.y)) { gameModus = vsFriend; }

                                currentState = mainPlay;
                                init();
                            break;

                            case mainPlay:
                                if(playerTurn) {
                                    for(int x = 0; x < 3; x++) { for (int y = 0; y < 3; y++) {
                                        if (board[x][y].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) { // get the current position of the mouse inside the window
                                            // check if button is not selected
                                            if(board[x][y].getFillColor() == startColor) { player01Move(x, y); }
                                        }
                                    }}

                                }

                                // it's AIs turn
                                if(turnsTaken < 9 && !playerTurn) {
                                    switch(gameModus) {
                                        case vsDumbAI:
                                            randAIMove();
                                            break;

                                        case vsSmartAI:
                                            smartAIMove();
                                            break;

                                        case vsFriend:
                                            for(int x = 0; x < 3; x++) { for (int y = 0; y < 3; y++) {
                                                if (board[x][y].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) { // get the current position of the mouse inside the window
                                                    // check if button is not selected
                                                    if(board[x][y].getFillColor() == startColor) { player02Move(x, y); }
                                                }
                                            }}
                                            break;
                                    }

                                }

                            break;
                        }
                    }
                    break;

                    default: break;
            }
        }

        //////////////////////////////////////////////////////////////

        // Clear screen
        window.clear(BGColor);

        clock.restart();
        // draw backgrounds according to current game state
        switch(currentState) {

            case gameMenu:
            for(int i = 7; i < 11; i++) { window.draw(textes[i]); }
                break;

            case mainPlay:
                window.draw(textes[5]);
                // draw the buttons/game board
                for (int x = 0; x < 3; x++) { for (int y = 0; y < 3; y++) { window.draw(board[x][y]); }}
                break;

            case itsADraw:
                while(clock.getElapsedTime().asSeconds() < delay.asSeconds()) {continue;}
                window.draw(textes[0]);
                window.draw(textes[6]);
                break;

            case youWin:
                while(clock.getElapsedTime().asSeconds() < delay.asSeconds()) {continue;}
                window.draw(textes[1]);
                window.draw(textes[6]);
                break;

            case gameOver:
                while(clock.getElapsedTime().asSeconds() < delay.asSeconds()) {continue;}
                window.draw(textes[2]);
                window.draw(textes[6]);
                break;

            case player02Loses:
                while(clock.getElapsedTime().asSeconds() < delay.asSeconds()) {continue;}
                window.draw(textes[3]);
                window.draw(textes[6]);
                break;

            case player02Wins:
                while(clock.getElapsedTime().asSeconds() < delay.asSeconds()) {continue;}
                window.draw(textes[4]);
                window.draw(textes[6]);
                break;

        }

        // Update the window
        window.display();

        // run game logic
        gameLogicWithColors();
    }

    return 0;
}
