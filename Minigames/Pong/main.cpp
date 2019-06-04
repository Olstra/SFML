#include <SFML/Graphics.hpp>
#include <iostream>
// #include "Ball.h"
// #include "Paddle.h"

using namespace sf;

const int S_WIDTH = 1200;
const int S_HEIGHT = 800;


int main() {


	// Create main window
	RenderWindow window( VideoMode( S_WIDTH, S_HEIGHT ), "OLIVER CODES PONG", Style::Titlebar | Style::Close );

	enum GAME_STATE { start, playing, paused, gameOver } gameState;

	gameState = start;

	// PADDLES // // // // // // // // // // // // // // // // // // // // // // // // 
	int PADDLE_W = 20;
	int PADDLE_H = 80;
	int velPaddle = 10;

	RectangleShape leftPaddle( Vector2f( PADDLE_W, PADDLE_H ) );
	RectangleShape rightPaddle( Vector2f( PADDLE_W, PADDLE_H ) );
	// set initial position of paddles
	int rightXPos = S_WIDTH - PADDLE_W;
	rightPaddle.setPosition( Vector2f( rightXPos, S_HEIGHT/2-PADDLE_H/2 ) );
	leftPaddle.setPosition( Vector2f( 0, S_HEIGHT/2-PADDLE_H/2 ) );
	
	int yPos; // temp variable to update position of paddles

	// BALL // // // // // // // // // // // // // // // // // // // // // // // // // 
	int BALL_S = 10;
	CircleShape ball( BALL_S );
	ball.setPosition( Vector2f( S_WIDTH/2, S_HEIGHT/2 ) );

	// Start the game loop // // // // // // // // // // // // // // // // // // // // 
	while( window.isOpen() ){
	
		// Process events
		Event event;
		while( window.pollEvent( event ) ){
		
			switch( event.type ){
				
				case Event::Closed: window.close(); break; // Exit per "(x)"

				case Event::KeyPressed: 
					switch( event.key.code ){
						
						case Keyboard::Escape: window.close(); break; // Exit per "esc"
				
						// initial ball schuss
						case Keyboard::Space:
							if( gameState == start ){ }
							break;

						// move left paddle with w/s
						case Keyboard::W:
							yPos = leftPaddle.getPosition().y;
							if( yPos > 0 ){ leftPaddle.setPosition( Vector2f( 0, yPos-velPaddle ) ); }
							break;

						case Keyboard::S:
							yPos = leftPaddle.getPosition().y;
							if( yPos < S_HEIGHT-PADDLE_H ){ leftPaddle.setPosition( Vector2f( 0, yPos+velPaddle ) ); }
							break;

						// move right paddle with arrow keys up/down
						case Keyboard::Up:
							yPos = rightPaddle.getPosition().y;
							if( yPos > 0 ){ rightPaddle.setPosition( Vector2f( rightXPos, yPos-velPaddle ) ); }
							break;

						case Keyboard::Down:
							yPos = rightPaddle.getPosition().y;
							if( yPos < S_HEIGHT-PADDLE_H ){ rightPaddle.setPosition( Vector2f( rightXPos, yPos+velPaddle ) ); }
							break;
						
						
						default: break;
					}
			
				default: break;
			}
		
		
		}

		
		if( gameState == playing ){
			// move/update ball
		}

		// Clear screen
		window.clear();

		// Draw stuff
		window.draw( leftPaddle );
		window.draw( rightPaddle );
		window.draw( ball );

		// Update window
		window.display();

	}


	return 0;

}
