#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <math.h>
using namespace std;
using namespace sf;
int main() {
	// creates the window object with an 800x600 resolution window
	RenderWindow window(sf::VideoMode(800, 800), "Lab07B: StarMap");

	// Draw loop: Each iteration of this loop draws a single frame
	while (window.isOpen()) {

		// Erase the screen with black (because space)
		window.clear();
		CircleShape star;
		ifstream stars("ModifiedStars.txt");
		if (stars.fail()) { cerr << "Error opening file(s)."; exit(1); }
		double x, y, brite;
		while (!stars.eof()) {
			stars >> x >> y >> brite;
			star.setRadius(brite/10.0);
			int color = (int)((255.0 * brite) / 8);
			double rad = brite;
			brite /= 1.5;
			for (int i = 0; i < int(round(rad))+1; i++) {
				if (i == 0) {
					star.setPosition(Vector2f(x + 80 - brite, y + 80));
					star.setFillColor(Color(color, 0, 0));
				}
				if (i == 1) {
					star.setPosition(Vector2f(x + 80 - brite, y + 80 - brite));	
					star.setFillColor(Color(color, color/2.0, 0));
				}
				if (i == 2) {
					star.setPosition(Vector2f(x + 80, y + 80 - brite));
					star.setFillColor(Color(color, color, 0));
				}
				if (i == 3) {
					star.setPosition(Vector2f(x + 80 + brite, y + 80 - brite));
					star.setFillColor(Color(0, color, 0));
				}
				if (i == 4) {
					star.setPosition(Vector2f(x + 80 + brite, y + 80));
					star.setFillColor(Color(0, color, color));
				}
				if (i == 5) {
					star.setPosition(Vector2f(x + 80 + brite, y + 80 + brite));
					star.setFillColor(Color(0, 0, color));
				}
				if (i == 6) {
					star.setPosition(Vector2f(x + 80, y + 80 + brite));
					star.setFillColor(Color(color, 0, color));
				}
				if (i == 7) {
					star.setPosition(Vector2f(x + 80 - brite, y + 80 + brite));
					star.setFillColor(Color(color, 0, color/2.0));
				}				
				window.draw(star);
			}
		}
		window.display();
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
	}
		return EXIT_SUCCESS;
}