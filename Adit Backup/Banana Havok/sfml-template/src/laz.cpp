#include "laz.h"
using namespace sf;
laz::laz(){
	strength = 1;
	cool = 500;
	lazt.setFillColor(Color(0, 0, 255));
	lazt.setSize(Vector2f(200, 5));
	lazt.setPosition(375, 375);	
}
bool laz::shoot(int func, int frames, double x, double y) {
	//std::cout << "Last shoot frame: " << frame << std::endl;
	//std::cout << "Given frame count: " << frames << std::endl;
	if (frames - frame < cool) { return false; }
	else {
		
		frame = frames;
		double dist = double(sqrt(pow((375.0 - double(x)), 2.0) + pow((375.0 - double(y)), 2.0)));
		lazt.setSize(Vector2f(dist, 5));
		lazt.setFillColor(Color(((double(dist) / 750.0)*255.0), 0, ((double(750.0 - dist) / 750.0)*255.0)));
		if (func == 0) { lazt.setRotation(-135); }
		if (func == 1) { lazt.setRotation(135); }
		if (func == 2) { lazt.setRotation(180); }
		if (func == 3) { lazt.setRotation(90); }
		if (func == 4) { lazt.setRotation(45); }
		if (func == 5) { lazt.setRotation(-45); }
		if (func == 6) { lazt.setRotation(0); }
		if (func == 7) { lazt.setRotation(-90); }
		return true;
	}
}