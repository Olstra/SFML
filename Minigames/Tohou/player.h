#include <SFML/Graphics.hpp> 

enum STATE {
	stealth,
	alive,
	dead
};


struct PLAYER {
	
	sf::CircleShape body;
	
	int HP;
	int attack;
	int vel = 10;

}player;


void initPlayer( ) {
	
	player.body.setRadius( 30 );
	player.body.setFillColor( sf::Color::Blue );

	// set starting pos of player
	player.body.setPosition( sf::Vector2f( 400, 400 ) );

	player.HP = 100;
	player.attack = 10;


}



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
	Bullet::body.setFillColor(sf::Color::Black );

}


void fire(){

	// create bullet

//	bullet.setRadius( 5 );
}
