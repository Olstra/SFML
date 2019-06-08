#include <SFML/Graphics.hpp>

// ? make enemy attributes private 

class Enemy {

public:

	Enemy( int HP, int attack, int vel ); // constructor

	//void fire();

	int attack;
	int HP;
	int vel;

	// sprite
	sf::CircleShape body;


};

Enemy::Enemy( int HP, int attack, int vel ) {

	Enemy::attack = attack;
	Enemy::HP = HP;
	Enemy::vel = vel;

	// init shape
	Enemy::body.setRadius( 30 );
	Enemy::body.setFillColor( sf::Color::Magenta );
	Enemy::body.setPosition( sf::Vector2f( 400, 200 ) ); 

}
