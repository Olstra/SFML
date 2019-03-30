#include <SFML/Graphics.hpp>
#include "player.h"

class Bullet {

public:
	int damage;
	int vel;

	sf::CircleShape body;

	Bullet();

};

Bullet::Bullet( ) {

	Bullet::body.setRadius( 10 );
	Bullet::body.setPosition( player.body.getPosition() );


}
