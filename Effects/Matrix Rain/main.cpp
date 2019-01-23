#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;


int main() {

    const int windowW = 1500;
    const int windowH = 1500;
    const int fontSize = 50;

    // Create the main window
    RenderWindow window(VideoMode(windowW, windowH), "OLIVER CODES MATRIX RAIN", Style::Titlebar | Style::Close);

    // load font
    Font font;
    if(!font.loadFromFile("media/matrix_code.ttf")){ std::cout<<"ERROR: couldn't load font"<<std::endl; return -1; }

    // define the charachters we'll be using (for testing)
    sf::String chars[] = {"a", "b", "c", "d", "e", "1", "2", "3", "4"};
    //chars[0].setFillColor(Color::Green);
    int tempNrs = 9;


    // create arra of size of length of windows to save chars in
    const int lineLength = (windowH/fontSize)+2;    // +2 so line fills up entire screen
    const int nrOfLines = windowW/fontSize;

    // Create code lines
    sf::String line;

    srand(time(0)); // start random seed

    Text baseText("", font, fontSize);
    baseText.setFillColor(Color::Black);
    Text textLines[nrOfLines][lineLength];  // here we'll save all lines that will be displayed in the window

    int temp;
    for(int k = 0; k < nrOfLines; k++) {
        for(int i = 0; i < lineLength; i++) {
            line = "";
            temp = rand() % (tempNrs-1);

            textLines[k][i] = baseText;

            line += chars[temp];
            line += "\n";

            textLines[k][i].setString(line);
            textLines[k][i].setPosition(k*fontSize, i*fontSize);
        }
    }

    //int idx = 0;
    //int speed = 100; // "milliseconds"
    Clock clock;


    // select random starting positions
    int randPos[nrOfLines];
    int randSpeed[nrOfLines];

    int minSpeed = 10;  // are actually the -time- we wait to turn a char green in milliseconds
    int maxSpeed = 100;

    // create random positions, random speeds
    for(int i = 0; i < nrOfLines; i++) {
        randPos[i] = rand() % (lineLength-1);
        randSpeed[i] = minSpeed + rand() % ((maxSpeed+1) - minSpeed);
    }

    // every char has its own changing speed

    int minSpeed2 = 100;  // are actually the -time- we wait to turn a char green in milliseconds
    int maxSpeed2 = 1000;

    int charSpeed[nrOfLines][lineLength];
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
        int tempF = clock.getElapsedTime().asMilliseconds();

        for(int i = 0; i < nrOfLines; i++) {

            if((tempF % randSpeed[i]) == 0) {

                if(randPos[i] < lineLength) {
                    textLines[i][randPos[i]].setFillColor(Color::Green);
                    randPos[i]++;
                }
                else{ randPos[i] = 0; }
            }

        }


        // Draw
        for (int k=0;k < nrOfLines;k++) { for(int i=0;i < lineLength;i++) {

            if(tempF % charSpeed[k][i] == 0) {
                temp = rand() % (tempNrs-1);
                textLines[k][i].setString(chars[temp]);
            }

            window.draw(textLines[k][i]);

        } }


        // Update the window
        window.display();
    }

    return 0;
}
