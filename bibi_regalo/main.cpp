#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;


int main() {

	const int S_WIDTH = VideoMode::getDesktopMode().width;
	const int S_HEIGHT =  VideoMode::getDesktopMode().height;
	// Create main window
	RenderWindow window( VideoMode( S_WIDTH, S_HEIGHT ), "FELIZ CUMPLE, BIBI!", Style::Titlebar | Style::Close );

	// Colors
	Color bgColor(252, 108, 133);
	Color butColor(253, 188, 180);

	// Text
	Font font;
	if(!font.loadFromFile("media/font.ttf")){ printf("Couldn't open FONT!"); return -1; }
	Text openMe("\tFELICIDADES PRIMA\n\tABRE TU REGALO!", font, 50);
	FloatRect tempRect;
	tempRect = openMe.getLocalBounds();
    openMe.setOrigin(tempRect.left+tempRect.width/2.0f, tempRect.top+tempRect.height/2.0f);
	openMe.setPosition(S_WIDTH/6, S_HEIGHT/7);

	Text goodbye("ESO ES TODO AMIGOS,\nHASTA LA PROXIMA!\n\nSALUDOS DESDE SUIZA |[+]", font, 50);
	tempRect = goodbye.getLocalBounds();
    goodbye.setOrigin(tempRect.left+tempRect.width/2.0f, tempRect.top+tempRect.height/2.0f);
	goodbye.setPosition(S_WIDTH/2, S_HEIGHT/2);

	Texture regaloTxt;
	if(!regaloTxt.loadFromFile("media/regalo.png")){ return -1; }
	Sprite regalo;
	regalo.setTexture(regaloTxt);

	int abstand = 00;
	tempRect = regalo.getLocalBounds();
    regalo.setOrigin(tempRect.left+tempRect.width/2.0f, tempRect.top+tempRect.height/2.0f);
	regalo.setPosition(openMe.getPosition().x, openMe.getPosition().y*3);


	// ragalo glowing box
	int box_W = regaloTxt.getSize().x;
	int box_H = regaloTxt.getSize().y;
	RectangleShape glowingBox(Vector2f(box_W, box_H));
	tempRect = glowingBox.getLocalBounds();
    glowingBox.setOrigin(tempRect.left+tempRect.width/2.0f, tempRect.top+tempRect.height/2.0f);
	glowingBox.setPosition(openMe.getPosition().x, openMe.getPosition().y*3);

	Text moore("PUCHALE OTRA VEZ, HAY MAS!", font, 25);
	tempRect = moore.getLocalBounds();
    moore.setOrigin(tempRect.left+tempRect.width/2.0f, tempRect.top+tempRect.height/2.0f);
	moore.setPosition(S_WIDTH/6, regalo.getPosition().y+250);

	Color transparentColor(0, 0, 0, 0);
	Color outColorA(255, 255, 255);
	Color outColorB(255, 250, 105);
	glowingBox.setFillColor(transparentColor); // set fill color to transparent
	glowingBox.setOutlineThickness(10.0f);

	// Images
	Texture fotos[9];
	for(int i=0; i<9; i++){
		std::string path = "media/IMG_" + std::to_string(i+1) + ".jpg";
		if( !fotos[i].loadFromFile(path)){ printf("Couldn't load pic!"); return -1; }
	}

	Sprite thePic;
	Sprite widePic;

	tempRect = thePic.getLocalBounds();
    thePic.setOrigin(tempRect.left+tempRect.width/2.0f, tempRect.top+tempRect.height/2.0f);
	thePic.setPosition(S_WIDTH/2, S_HEIGHT/2);


	int flag = -1;
	bool show = false;
	Vector2i mousePos;

	Clock clock;
	int ellapsedTime;

	// Start the game loop
	while( window.isOpen() ) {
	
		// Process events
		Event event;
		while( window.pollEvent( event ) ) {

			switch(event.type) {
				case Event::Closed: window.close(); break;

				case Event::KeyPressed:
					if(event.key.code == Keyboard::Escape){ window.close(); }
					break;

				case Event::MouseButtonPressed:
					mousePos = Mouse::getPosition(window);
					if(Mouse::isButtonPressed(Mouse::Left)){
						if(regalo.getGlobalBounds().contains(mousePos.x, mousePos.y)){ 
							// reset counter for fotos
							( flag < 9 ) ? (flag++) : (flag = 0);
							show = true; 
						}
						else{ show = false; }
					}
					break;

				default: break;			
			
			}
		}

		ellapsedTime = clock.getElapsedTime().asMilliseconds();

		// Glowing effect for regalo
		if(!show){
			if(ellapsedTime % 5 == 0){
				glowingBox.setOutlineColor(outColorA);
				clock.restart();
			}
			else{ glowingBox.setOutlineColor(outColorB); }
		}	
		
		// Clear screen
		window.clear(bgColor);

		// Draw stuff
		window.draw(regalo);
		
		if(show){
			if(flag == 0 || flag == 6){
				thePic.setTexture(fotos[flag]);

				tempRect = thePic.getLocalBounds();
				thePic.setOrigin(tempRect.left+tempRect.width/2.0f, tempRect.top+tempRect.height/2.0f);
				thePic.setPosition(S_WIDTH/2, S_HEIGHT/2);
				thePic.setScale(0.2f, 0.2f);

				window.draw(thePic);
			}
			else if(flag == 9){ window.draw(goodbye); }
			else{
				widePic.setTexture(fotos[flag]);
				tempRect = widePic.getLocalBounds();
				widePic.setOrigin(tempRect.left+tempRect.width/2.0f, tempRect.top+tempRect.height/2.0f);
				widePic.setPosition(S_WIDTH/2, S_HEIGHT/2);
				widePic.setScale(0.2f, 0.2f);
				window.draw(widePic);
			}

			window.draw(moore);
		}

		window.draw(glowingBox);
		window.draw(openMe);
		// Update window
		window.display();

	}


	return 0;

}







