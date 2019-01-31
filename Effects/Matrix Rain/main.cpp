/**
TODOs:
- implement random white character


Notes:
- for optimization you can draw only the green chars to the window
- dimensions made on a 4k display
*/


#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;


int main() {

    const int windowW = 800;
    const int windowH = 800;
    const int fontSize = 32;

    Clock clock;    // Time management
    int currentTime;

    // define colors to be used
    //Color WhiteGreen(205, 250, 210);

    // Create the main window
    RenderWindow window(VideoMode(windowW, windowH), "OLIVER CODES MATRIX RAIN", Style::Titlebar | Style::Close);

    // load font
    Font font;
    if(!font.loadFromFile("media/matrix_code.ttf")){ std::cout<<"ERROR: couldn't load font"<<std::endl; return -1; }

    // GENERATE the SYMBOLS we'll be using

    int nrOfSymbols = 32;
    sf::String chars[nrOfSymbols];

    for(int i = 0; i < nrOfSymbols; i++){ chars[i] = (char)(nrOfSymbols + i); }

    // create array of size of length of windows to save chars in

    const int lineLength = (windowH/fontSize)+2;    // +2 so line fills up entire screen
    const int nrOfLines = windowW/fontSize;
    Text textLines[nrOfLines][lineLength];  // here we'll save all lines that will be displayed in the window

    // Create code lines //////////////////////////////////////////////////////////////////////////////////////////

    srand(time(0)); // start random seed

    Text baseText("", font, fontSize);
    baseText.setFillColor(Color::Black); // default starting color of char = "hidden char"

    for(int k = 0; k < nrOfLines; k++) {
        for(int i = 0; i < lineLength; i++) {
            textLines[k][i] = baseText;
            textLines[k][i].setString(chars[rand()%(nrOfSymbols-1)]); // choose random symbol
            textLines[k][i].setPosition(k*fontSize, i*fontSize); // position each slot accross the window
        }
    }

    // select random starting positions (to show lines with green color)
    int randPos[nrOfLines];
    int randSpeed[nrOfLines];

    int minSpeed = 100;  // are actually the -time- we wait to turn a char green in milliseconds
    int maxSpeed = 1000;

    // create random positions, random speeds
    for(int i = 0; i < nrOfLines; i++) {
        randPos[i] = rand() % (lineLength-1);
        randSpeed[i] = minSpeed + rand() % ((maxSpeed+1) - minSpeed);
    }

    // every char has its own changing speed to change to another rand char

    int charSpeed[nrOfLines][lineLength];
    for(int k = 0; k < nrOfLines; k++) {
        for(int i = 0; i < lineLength; i++) {
            charSpeed[k][i] = minSpeed + rand() % ((maxSpeed+1) - minSpeed);
        }
    }


	// Start the game loop

    while (window.isOpen()) {
        // Process events
        Event event;
        while (window.pollEvent(event)) {
            // Close window : exit
            if (event.type == Event::Closed) { window.close(); }

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) { window.close(); }
            }
        }

        // Clear screen
        window.clear();


        // change attributes of symbols ////////////////////////////////////////////////////////////////////////////////////////

        currentTime = clock.getElapsedTime().asMilliseconds();

        // go through all lines
        for(int i = 0; i < nrOfLines; i++) {

            if((currentTime % randSpeed[i]) == 0) {

                if(randPos[i] < lineLength) {   // check that we don't get IOB

                    // if char was black turn it green, otherwise hide char again (=turn black)
                    if(textLines[i][randPos[i]].getFillColor() == Color::Black) {
                        textLines[i][randPos[i]].setFillColor(Color::Green);
                    }
                    else { textLines[i][randPos[i]].setFillColor(Color::Black); }

                    randPos[i]++;
                }
                else{ randPos[i] = 0; }  // oder: rand() % (lineLength-1); }

            }

        }


        // Draw every slot
        for (int k = 0; k < nrOfLines; k++) { for(int i = 0; i < lineLength; i++) {

            // change displayed symbol randomly
            if(currentTime % charSpeed[k][i] == 0) { textLines[k][i].setString(chars[rand() % (nrOfSymbols-1)]); }

            window.draw(textLines[k][i]);   // draw characters

        } }

        // Update the window
        window.display();
    }

    return 0;
}
