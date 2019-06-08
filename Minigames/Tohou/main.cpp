#include <SFML/Graphics.hpp>
#include <iostream>

#include "player.h"
#include "bullets.h"
// #include "enemy.h"

using namespace sf;

const int S_WIDTH = 800;
const int S_HEIGHT = 800;

void fire( int nrOfBullets, Bullet* theBullets[], Vector2f pos ) {
 	Bullet newBullet( pos );
 	theBullets[nrOfBullets] = newBullet;
 	nrOfBullets++;
}


void addNewBullet( Vector2f pos );


int main() {

    // Create the main window
    RenderWindow window( VideoMode( S_WIDTH, S_HEIGHT ), "OLIVER CODES TOUHOU", Style::Titlebar | Style::Close );
	
	// main player // // // // // // // 
	initPlayer();
	Vector2f playerPos;

	// Enemy // // // // // // // // 
	// Enemy A( 90, 90, 90 );

	// Bullets // // // // // // // // 
	const size_t maxBullets = 3000;
	Bullet* theBullets[maxBullets];
	// init the bullets
	for(size_t i=0; i < maxBullets; i++) { theBullets[i] = NULL; } 

	// Time management
	Clock clock;
	Time timeElapsed;


	// Start the game loop
    while ( window.isOpen() ) {
		
		playerPos = player.body.getPosition();
		timeElapsed = clock.restart();	

	
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

							// case Keyboard::Return:
								// addNewBullet( playerPos );
							// 	break;

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


	// fire bullet
	if( Keyboard::isKeyPressed( Keyboard::Return ) ) { Bullet newBullet( playerPos ); }



		// update bullets
		for(size_t i=0; i < maxBullets; i++){
			if(theBullets[i] != NULL){
				theBullets[i]->update( timeElapsed.asMilliseconds() );
			}
		}
		

        // Clear screen
        window.clear( Color::White );

        // Draw the sprite
		window.draw( player.body );
	
		window.draw( newBullet.body );
	
		// Update the window
		window.display();
	}


	return 0;

}

//void addNewBullet( Vector2f pos ) {
//
//	// got to next free slot
//	int i = 0;
//	while( theBullets[i] != NULL ){ i++; }
//
//	// if(i >= maxBullets ) {
//	// 	// TODO do sth if max nr of bullets reached...
//	// }
//
//	Bullet newBullet( pos );
//	theBullets[i] = newBullet;
//
//
//}
