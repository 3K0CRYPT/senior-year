#include <SFML/Graphics.hpp>
#include <string>
class tower {
public:
	tower();
	bool hit(int health);
	void sprit(int i);
	int maxhealth, health, healthup;
	sf::Sprite sprite; // Used to draw the image representing them, along with texture
	sf::Texture texture; // ↑	
	sf::Text heal; //Used to write health fraction on the health bar
	sf::Font font; //The font of the text
private:

};