#include "baddy.h"
using namespace std;
using namespace sf;
static int rip;
static int tot;
baddy::baddy() { return; }
baddy::baddy(int l){
	srand(pow(time(0),(1.0/double(tot))+1));
	func = rand() % 8; // determines how the sprite scrolls across the screen	
	l = 3 + ((l-9) / 10);
	health = rand()%l + 1;				
	speed = 1.0 / 50.0; //affected by level, i.e. faster, which means less time for the laser to respond
	pos[0] = 0, pos[1] = 0;	// x and y respectively,  iterated on by each frame

	//Determines the sprite based on the health 
	sprit();
	tot++;
}

void baddy::posit(double i,double j){
	pos[0] = i, pos[1] = j;
	sprite.setTexture(texture);
	sprite.setPosition(Vector2f(i, j));
}

double baddy::getx(){
	return pos[0];
}

double baddy::gety(){
	return pos[1];
}

void baddy::inpos(int i) {
	if (func == 0) {
		posit((i + 1) * -25, (i + 1) * -25);
		//y=0, x=0 
	}
	if (func == 1) {
		posit(0+((i+1)*-25), 750 + ((i) * 25));
		//x=0,y=750
	}
	if (func == 2) {
		posit(0 + ((i + 1)*-25), 365);
		//x=0,y=365
	}
	if (func == 3) {
		posit(365, 750 + ((i)* 25));
		//x=365,y=0
	}
	if (func == 4) {
		posit(750 + ((i)* 25), 750 + ((i)* 25));
		//x=750,y=750
	}
	if (func == 5) {
		posit(750 + ((i)* 25), 0+((i + 1)*-25));
		//x=750,y=0
	}
	if (func == 6) {
		posit(750 + ((i)* 25), 365);
		//x=750,y=365
	}
	if (func == 7) {
		posit(365, 0 + ((i + 1)*-25));
		//x=365,y=750
	}
}

int baddy::iter(){
	if (func == 0) {
		posit((getx() + speed), gety() + speed);
		// +x & +y each frame
		if ((getx()) >= 355) { posit(-20, -20); die(); return health; }
		else { return 0; }
	}
	if (func == 1) {
		posit((getx() + speed), gety() - speed);
		// +x & -y each frame
		if ((getx()) >= 355) { posit(-20, -20); die(); return health; }
		else { return 0; }
	}
	if (func == 2) {
		posit((getx() + speed), gety());
		// +x each frame
		if ((getx()) >= 355) { posit(-20, -20); die(); return health; }
		else { return 0; }
	}
	if (func == 3) {
		posit(getx(), gety()-speed);
		// -y each frame
		if ((gety()) <= 375) { posit(-20, -20); die(); return health; }
		else { return 0; }
	}
	if (func == 4) {
		posit(getx() - speed, gety() - speed);
		// -x & -y each frame
		if ((gety()) <= 375) { posit(-20, -20); die(); return health; }
		else { return 0; }
	}
	if (func == 5) {
		posit(getx() - speed, gety() + speed);
		// -x & +y each frame
		if ((getx()) <= 375) { posit(-20, -20); die(); return health; }
		else { return 0; }
	}
	if (func == 6) {
		posit(getx() - speed, gety());
		// -x each frame
		if ((getx()) <= 375) { posit(-20, -20); die(); return health; }
		else { return 0; }
	}
	if (func == 7) {
		posit(getx(), gety()+speed);
		// +y each frame
		if ((gety()) >= 355) { posit(-20, -20); die(); return health; }
		else { return 0; }
	}
}

void baddy::die(){
	dead = true;
	rip++;	
}

int baddy::ripc(){
	return rip;
}

void baddy::rips() {
	rip = 0;
}

void baddy::hit(int strength, int& count){
	if (dead) { count++; return; }
	health -= strength;
	if (health <= 0) { count++; die(); }
	else { sprit(); }
}
void baddy::sprit() {
	string SPRITE_PATH = "";
	if (health <= 1) { SPRITE_PATH = "src/sprites/baddy1.png"; } //Rotten bananas are the weakest
	if (health == 2) { SPRITE_PATH = "src/sprites/baddy2.png"; } //ripe bananas are moderately strong
	if (health == 3) { SPRITE_PATH = "src/sprites/baddy3.png"; } //unripe bananas are the tough
	if (health == 4) { SPRITE_PATH = "src/sprites/baddy4.png"; }
	if (health == 5) { SPRITE_PATH = "src/sprites/baddy5.png"; }
	if (health == 6) { SPRITE_PATH = "src/sprites/baddy6.png"; }
	if (health == 7) { SPRITE_PATH = "src/sprites/baddy7.png"; }
	if (health == 8) { SPRITE_PATH = "src/sprites/baddy8.png"; }
	if (health == 9) { SPRITE_PATH = "src/sprites/baddy9.png"; }
	if (health >= 10) { SPRITE_PATH = "src/sprites/baddy10.png"; }
	Image image;
	if (!image.loadFromFile(SPRITE_PATH)) {
		cerr << "Couldn't load image file " << SPRITE_PATH << endl;
		exit(1);
	}
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setPosition(Vector2f(pos[0], pos[1]));
}
void baddy::tots(){ tot = 0; }