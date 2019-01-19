/** NOTES
TODOS:
- what happens when draw
- bug if everything is clicked
- make init() function
- nicer display of game board/buttons in middle

LEARNINGS:
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
a == b == c <=doesn't work like that!!!
better with transitivity:
a == b && b == c
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

*/

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;


// COLORS of the buttons
Color startColor(250, 190, 0);
Color playerColor(250, 80, 35);
Color AIColor(Color::Black);
// create game board 3x3
sf::RectangleShape board[3][3];

// different game states used to display according background
enum GameState {
    startMenu, mainPlay, gameOver, youWin
}currentState;

void gameLogicWithColors () {
    // check for all 3 equal with transitivity...

    for(int i = 0; i < 3; i++) {
        // check win top to bottom
        if(board[i][0].getFillColor() == board[i][1].getFillColor() && board[i][1].getFillColor() == board[i][2].getFillColor()) {
            // check if player wins
            if(board[i][0].getFillColor() == playerColor) { currentState = youWin; }
            else if (board[i][0].getFillColor() == AIColor) { currentState = gameOver; }
        }
        // check for win from left to right
        else if(board[0][i].getFillColor() == board[1][i].getFillColor() && board[1][i].getFillColor() == board[2][i].getFillColor()) {
            if(board[0][i].getFillColor() == playerColor) { currentState = youWin; }
            else if (board[0][i].getFillColor() == AIColor) { currentState = gameOver; }
        }
    }

    // check the cross "X"
    // from Top left to Bottom right: [0][0] == [1][1] == [2][2]
    if( board[0][0].getFillColor()  == board[1][1].getFillColor() && board[1][1].getFillColor() == board[2][2].getFillColor() ) {
        if(board[0][0].getFillColor() == playerColor) { currentState = youWin; }
        else if (board[0][0].getFillColor() == AIColor) { currentState = gameOver; }
    }

    // from Bottom left to Top right: [0][2] == [1][1] == [2][0]
    if( board[0][2].getFillColor()  == board[1][1].getFillColor()  &&  board[1][1].getFillColor() == board [2][0].getFillColor()  ) {
        if(board[0][2].getFillColor() == playerColor) { currentState = youWin; }
        else if (board[0][2].getFillColor() == AIColor) { currentState = gameOver; }
    }
}

// AI chooses a random button
sf::Vector2i AILogic() {

    sf::Vector2i selectedButton;
    selectedButton.x = rand() % 3;
    selectedButton.y = rand() % 3;

    return selectedButton;
}

// check for draw
void checkForDraw() {

    bool draw = true;
    // check board if there is still boxes left to check
    for(int i = 0; i < 3; i++) {
        for (int j= 0; j <3; j++) {
            if(board[i][j].getFillColor() == startColor) { draw = false; }
        }
    }

    if(draw) { currentState = gameOver; }

}

int main() {

    // SETUP /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    const int windowW = 1500;
    const int windowH = 1500;

    // Create the main window
    RenderWindow window(VideoMode(windowW, windowH), "Oliver Codes Tic Tac Toe", Style::Titlebar | Style::Close);

    // Load backgrounds
    Texture one, two, three, four;
    if (!one.loadFromFile("media/start_menu.png")) { std::cout<< "ERROR: Background could not be loaded" << std::endl; return -1; }
    if (!two.loadFromFile("media/main_play.png")) { std::cout<< "ERROR: Background could not be loaded" << std::endl; return -1; }
    if (!three.loadFromFile("media/you_win.png")) { std::cout<< "ERROR: Background could not be loaded" << std::endl; return -1; }
    if (!four.loadFromFile("media/game_over.png")) { std::cout<< "ERROR: Background could not be loaded" << std::endl; return -1; }
    Sprite start_menu(one), main_play(two), you_win(three), game_over(four);

    // TIC TAC TOE //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool playerTurn;
    playerTurn = true;
    currentState = startMenu;
    srand(time(0));

    RectangleShape baseButton;
    baseButton.setSize(Vector2f(200, 200));

    // place buttons
    int scale = 300;
    int offset = 350;
    for(int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            board[x][y] = baseButton;
            board[x][y].setPosition(offset+x*scale, offset+y *scale);
        }
    }

	// Start the game loop /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
                                 // reset everything
                                for(int x = 0; x < 3; x++) { for (int y = 0; y < 3; y++) { board[x][y].setFillColor(startColor); } } // reset color of buttons
                                playerTurn = true;
                                currentState = mainPlay;
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

        if(currentState == mainPlay) {
            if(playerTurn) {
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    for(int x = 0; x < 3; x++) { for (int y = 0; y < 3; y++) {
                            if ( board[x][y].getGlobalBounds().contains
                                (Mouse::getPosition(window).x, Mouse::getPosition(window).y) ) { // get the current position of the mouse inside the window
                                    if(board[x][y].getFillColor() == startColor) { // meaning this is the first time we click on the button
                                        board[x][y].setFillColor(playerColor); // change color of the button that was clicked
                                        playerTurn = false;
                                    }
                                    else { continue; }
                            }
                        }
                    }
                }
            }

            if(!playerTurn) {
                Vector2i temp;
                // AI chooses its button
                do { temp = AILogic();
                }while (board[temp.x][temp.y].getFillColor() != startColor); // meaning this is the first time we click on the button

                board[temp.x][temp.y].setFillColor(AIColor);
                playerTurn = true;


                checkForDraw(); // so we don't count the starting mode
            }
        }
        //////////////////////////////////////////////////////////////

        // run game logic
        gameLogicWithColors();


        // Clear screen
        window.clear();

         // draw backgrounds according to current game state
        switch(currentState) {
            case startMenu:
                window.draw(start_menu);
                break;

            case mainPlay:
                window.draw(main_play);
                // draw the buttons/game board
                for (int x = 0; x < 3; x++) { for (int y = 0; y < 3; y++) { window.draw(board[x][y]); } }
                break;

            case gameOver:
                window.draw(game_over);
                break;

            case youWin:
                window.draw(you_win);
                break;
        }

        // Update the window
        window.display();
    }

    return 0;
}
