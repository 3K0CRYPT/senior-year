#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <random>
#include <cmath>
class baddy{
	public:
	baddy();
	baddy(int l);
	void posit(double i, double j);
	double getx(); double gety();
	void inpos(int i);
	int iter(); //Iterates baddy frame by frame
	void die(); //Runs necessary functions to kill baddy, and increase death count
	int ripc(); //Returns the death count
	void rips(); //Resets the death count for continuous play
	void hit(int strength, int& count); //used to register damage from laser beams
	void sprit(); //Used to affect the sprite based on health of each baddy
	void tots(); //Used to make levels more random since the game operates faster than ctime counts
	

	///// Modifiable accessibles
	
	int health; // varies depening on level, and is randomized during each baddy's creation between a certain range
	
	double speed; //also varies depending on level, and is randomized for each baddy
	
	sf::Sprite sprite; // Used to draw the image representing them, along with texture
	
	sf::Texture texture; // ↑
	
	int func; // Used to determine which of the 8 possible paths to the center the enemies can scroll along
	
	bool dead; // Used to determine if a baddy should continue scrolling across the screen
			   // Is made true if killed midflight or collides with the player's tower

	/////

private:
	double pos[2]; // Determine's the baddy's location in the play space
};