/**
TODOs:
- implement random white character

*/


#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;


int main() {

    const int windowW = 1500;
    const int windowH = 1500;
    const int fontSize = 50;

    Clock clock;    // start clock

    // Create the main window
    RenderWindow window(VideoMode(windowW, windowH), "OLIVER CODES MATRIX RAIN", Style::Titlebar | Style::Close);

    // load font
    Font font;
    if(!font.loadFromFile("media/matrix_code.ttf")){ std::cout<<"ERROR: couldn't load font"<<std::endl; return -1; }

    // GENERATE the SYMBOLS we'll be using

    int nrOfSymbols = 52;
    sf::String chars[nrOfSymbols];

    for(int i = 0; i < nrOfSymbols; i++){
        chars[i] = (char)(nrOfSymbols + i);
    }

    // create array of size of length of windows to save chars in
    const int lineLength = (windowH/fontSize)+2;    // +2 so line fills up entire screen
    const int nrOfLines = windowW/fontSize;
    Text textLines[nrOfLines][lineLength];  // here we'll save all lines that will be displayed in the window

    // Create code lines //////////////////////////////////////////////////////////////////////////////////////////

    srand(time(0)); // start random seed

    Text baseText("", font, fontSize);
    baseText.setFillColor(Color::Black); // default starting color of char = "hidden char"

    int temp;
    for(int k = 0; k < nrOfLines; k++) {
        for(int i = 0; i < lineLength; i++) {

            temp = rand() % (nrOfSymbols-1);    // choose random symbol
            textLines[k][i] = baseText;
            textLines[k][i].setString(chars[temp]);
            textLines[k][i].setPosition(k*fontSize, i*fontSize); // position each slot accross the window
        }
    }


    // select random starting positions
    int randPos[nrOfLines];
    int randSpeed[nrOfLines];

    int minSpeed = 10;  // are actually the -time- we wait to turn a char green in milliseconds
    int maxSpeed = 100;

    // create random positions, random speeds
    int randWhites[nrOfLines];
    for(int i = 0; i < nrOfLines; i++) {
        randPos[i] = rand() % (lineLength-1);
        randSpeed[i] = minSpeed + rand() % ((maxSpeed+1) - minSpeed);
    }


    // every char has its own changing speed

    int minSpeed2 = 100;  // are actually the -time- we wait to turn a char green in milliseconds
    int maxSpeed2 = 1000;

    int minSpeed3 = 1000;  // are actually the -time- we wait to turn a char green in milliseconds
    int maxSpeed3 = 10000;

    int charSpeed[nrOfLines][lineLength]; // if 0 turn green if 1 turn black
    for(int k = 0; k < nrOfLines; k++) {
        for(int i = 0; i < lineLength; i++) {
            charSpeed[k][i] = minSpeed2 + rand() % ((maxSpeed2+1) - minSpeed2);
        }
    }



	// Start the game loop //////////////////////////////////////////////////////////////////////////////////////////////////////

    while (window.isOpen()) {
        // Process events
        Event event;
        while (window.pollEvent(event)) {
            // Close window : exit
            if (event.type == Event::Closed) { window.close(); }
        }

        // Clear screen
        window.clear();


        // change attributes of symbols
        int currentTime = clock.getElapsedTime().asMilliseconds();

        // go through all lines
        for(int i = 0; i < nrOfLines; i++) {


            if((currentTime % randSpeed[i]) == 0) {

                if(randPos[i] < lineLength) {

                    if(textLines[i][randPos[i]].getFillColor() == Color::Black) {
                        textLines[i][randPos[i]].setFillColor(Color::Green);
                    }
                    else { textLines[i][randPos[i]].setFillColor(Color::Black); }

                    randPos[i]++;
                }
                else{ randPos[i] = 0; }
            }
        }



        // Draw
        for (int k=0;k < nrOfLines;k++) { for(int i=0;i < lineLength;i++) {

            // change displayed symbol randomly
            if(currentTime % charSpeed[k][i] == 0) {
                temp = rand() % (nrOfSymbols-1);
                textLines[k][i].setString(chars[temp]);
            }

            window.draw(textLines[k][i]);   // draw every symbol

        } }


        // Update the window
        window.display();
    }

    return 0;
}
