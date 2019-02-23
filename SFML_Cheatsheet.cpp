// pass window to a function
int main() { sf::RenderWindow window(...); }
void function( sf::RenderWindow &window ...) {...}


// "wait" in main loop
sf::Clock clock;
int currentTime;
int intervall = 1000; // milliseconds

while ( window.isOpen() ) { 
  int currentTime = clock.getElapsedTime().asMilliseconds();
  if( currentTime % intervall == 0 ) { // show thing }
}
