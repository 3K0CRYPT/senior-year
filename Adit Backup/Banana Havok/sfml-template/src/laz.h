#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
class laz{
public:
	laz();
	bool shoot(int func, int frames, double x, double y); //Draws laser if cooldown allows, and returns if the baddy is dead
	
	int cool; // Amount of frames tower waits before shooting laser
	int strength; // Amount of health laser reduces per hit
	int frame; // What frame count the last laser fired, used for cooldown calculations
	int laserup, coolup; // Used to determine upgrades upon loading game
	sf::RectangleShape lazt; // Used to draw the laser shooting

private:

};