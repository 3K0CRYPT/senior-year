#include "tower.h"
#include <iostream>
using namespace std;
using namespace sf;
const static string SPRITE_PATH = "src/sprites/tower1.png";
tower::tower() {
	maxhealth = 5;
	health = 5; // Amount of times tower can be hit before losing
	
	//Health fraction displayed on screen
	string str = to_string(health);	str += "/"; str += to_string(maxhealth);
	heal.setString(str);
	heal.setColor(Color::White);
	heal.setPosition(250, 700);
	heal.setCharacterSize(24);
	if (!font.loadFromFile("src/sprites/swgothe.ttf")) { cerr << "Can't read font\n"; exit(1); }
	heal.setFont(font);
	//
}
bool tower::hit(int health){
	this->health -= health;
	if (this->health <= 0) { return false; }
	else { 
		string str = to_string(this->health);	str += "/"; str += to_string(maxhealth);
		heal.setString(str);
		heal.setPosition(210-(4*double(str.size())), 669);
		return true;
	}
}
void tower::sprit(int i){
	string SPRITE_PATH1 = "src/sprites/tower1.png";
	sprite.setPosition(Vector2f(365, 372));
	if (i == 0) { SPRITE_PATH1 = "src/sprites/tower1.png";}
	if (i == 1) { SPRITE_PATH1 = "src/sprites/tower2.png"; }
	if (i == 2) { SPRITE_PATH1 = "src/sprites/tower3.png"; }
	if (i >= 3) { SPRITE_PATH1 = "src/sprites/tower4.png"; }
	if (i >= 4) { SPRITE_PATH1 = "src/sprites/tower5.png"; }
	if (i >= 6) { SPRITE_PATH1 = "src/sprites/tower6.png"; }
	if (i >= 8) { SPRITE_PATH1 = "src/sprites/tower7.png"; }
	if (i >= 10) { SPRITE_PATH1 = "src/sprites/tower8.png"; }
	if (i >= 13) { SPRITE_PATH1 = "src/sprites/tower9.png"; }
	if (i >= 16) { SPRITE_PATH1 = "src/sprites/tower10.png"; sprite.setPosition(Vector2f(350, 367)); }
	Image image;
	if (!image.loadFromFile(SPRITE_PATH1)) {
		cerr << "Couldn't load image file " << SPRITE_PATH1 << endl;
		exit(1);
	}
	texture.loadFromImage(image);	
	sprite.setTexture(texture);
}