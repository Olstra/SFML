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

	STATE state;

}player;


void initPlayer( ) {
	
	player.body.setRadius( 30 );
	player.body.setFillColor( sf::Color::Blue );

	// set starting pos of player
	player.body.setPosition( sf::Vector2f( 400, 400 ) );

	player.HP = 100;
	player.attack = 10;
	player.state = stealth;

}
