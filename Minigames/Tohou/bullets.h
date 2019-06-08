/**
	This is the class for the bulltes
	Author: Olstra
	What does a bullet need?:
		- velocity
		- shape/sprite
		- damage points
*/

#include <SFML/Graphics.hpp>

class Bullet {

	public:
		// constructor
		Bullet( sf::Vector2f pos ){
			this->vel = vel;
			this->body.setPosition( pos );
		}

		// update bullet position
		void update( int timeElapsed ) {
			body.setPosition( body.getPosition().x, body.getPosition().y + timeElapsed * vel );
		}
	
		sf::CircleShape body;
		int vel;

};
