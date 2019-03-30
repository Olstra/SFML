#include <SFML/Graphics.hpp>
#include <iostream>

#include "player.h"
#include "enemy.h"

using namespace sf;

const int S_WIDTH = 800;
const int S_HEIGHT = 800;

void fire( int nrOfBullets, Bullet theBullets[] ) {
	Bullet newBullet;
	theBullets[nrOfBullets] = newBullet;
	nrOfBullets++;
}

int main() {

    // Create the main window
    RenderWindow window( VideoMode( S_WIDTH, S_HEIGHT ), "OLIVER CODES TOUHOU", Style::Titlebar | Style::Close );
	
	// main player
	initPlayer();
	Vector2f playerPos;

	// Enemy
	Enemy A( 90, 90, 90 );

	// Bullets
	Bullet theBullets[100];
	int bulletsNr = 0;


	// Start the game loop
    while ( window.isOpen() ) {
        
		
		playerPos = player.body.getPosition();
		
		// Process events
        Event event;
        while (window.pollEvent( event )) {
        
			switch(event.type) {
					case Event::Closed: window.close(); break;

					case Event::KeyPressed:
						switch (event.key.code) {

							case Keyboard::Escape:
								window.close();
								break;

							case Keyboard::Space:
								break;

							case Keyboard::Return:
								fire( bulletsNr,  theBullets );
							//	Bullet newBullet;
							//	theBullets[bulletsNr] = newBullet;
								//bulletsNr++;
								break;


							// move player
							case Keyboard::Up:
								playerPos.y -= player.vel;
								player.body.setPosition( playerPos );
								break;

							case Keyboard::Down:
								playerPos.y += player.vel;	
								player.body.setPosition( playerPos );
								break;

							case Keyboard::Left:	
								playerPos.x -= player.vel;	
								player.body.setPosition( playerPos );
								break;

							case Keyboard::Right:
								playerPos.x += player.vel;	
								player.body.setPosition( playerPos );
								break;
								

							default: break;
						}

					default: break;
				}
		}

        // Clear screen
        window.clear( Color::White );

        // Draw the sprite
		window.draw( player.body );
		window.draw( A.body );
		// draw bullets
		for( int i = 0; i <= bulletsNr; i++ ) {
			// update bullets position
			// TODOi
			Vector2f pos = theBullets[i].body.getPosition();
			pos.y--;
			theBullets[i].body.setPosition( pos );
			window.draw( theBullets[i].body );		
		}

	// Update the window
	window.display();
}

return 0;
}
