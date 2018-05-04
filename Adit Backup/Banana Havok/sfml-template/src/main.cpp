#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <time.h>
#include "tower.h"
#include "baddy.h"
#include "laz.h"
#include "save.h"
using namespace std;
using namespace sf;
const string FONT_PATH = "src/sprites/swgothe.ttf";
Font font;
int main() {
	if (!font.loadFromFile(FONT_PATH)) { cerr << "Can't find font"; return 0; }
	while (true) {
		bool win = false;
		int brake = 0;
		
		//Establishes base for health bar
		RectangleShape max, bar;
		max.setFillColor(Color(100, 0, 0)); bar.setFillColor(Color::Red);
		max.setSize(Vector2f(200, 20)); bar.setSize(Vector2f(200, 20));
		max.setPosition(125, 675); bar.setPosition(125, 675);
		//
		
		RenderWindow window(sf::VideoMode(750, 750), "Banana Havok");
		vector<baddy> bad(0);
		laz lazr;
		tower tow;
		int level;
		
		//loads upgrades and level
		load(level, tow.healthup, lazr.laserup, lazr.coolup, win);

		while (win==true) {
			window.clear();
			string str = "UPGRADE";
			Text upgr; upgr.setString(str);	upgr.setColor(Color::Cyan); upgr.setPosition(195, 30);	upgr.setCharacterSize(70); upgr.setFont(font);
			window.draw(upgr);

			str = "Press \"H\" to upgrade the tower's health";
			upgr.setString(str); upgr.setColor(Color(0, 100, 255)); upgr.setPosition(100, 150); upgr.setCharacterSize(30); upgr.setFont(font);
			window.draw(upgr);

			str = "Press \"L\" to upgrade the laser's strength";
			upgr.setString(str); upgr.setColor(Color(0, 100, 255)); upgr.setPosition(90, 250); upgr.setCharacterSize(30); upgr.setFont(font);
			window.draw(upgr);

			if (lazr.coolup < 480) {
				str = "Press \"C\" to reduce the cooldown of the laser";
				upgr.setString(str); upgr.setColor(Color(0, 100, 255)); upgr.setPosition(75, 350); upgr.setCharacterSize(30); upgr.setFont(font);
				window.draw(upgr);
			}

			str = "Press \"N\" to continue without an upgrade";
			upgr.setString(str); upgr.setColor(Color(0, 100, 255)); upgr.setPosition(90, 450); upgr.setCharacterSize(30); upgr.setFont(font);
			window.draw(upgr);

			str = "Press \"Esc\" to quit";
			upgr.setString(str); upgr.setColor(Color(255, 0, 100)); upgr.setPosition(240, 550); upgr.setCharacterSize(30); upgr.setFont(font);
			window.draw(upgr);

			window.display();

			Event evn;
			while (window.pollEvent(evn)) {
				if (evn.type == Event::Closed) { window.close(); }
				if (evn.type == sf::Event::KeyPressed) {
					if (evn.key.code == sf::Keyboard::H) { tow.healthup++; win = false; }
					if (evn.key.code == sf::Keyboard::L) { lazr.laserup++; win = false; }
					if (evn.key.code == sf::Keyboard::C) { if (lazr.coolup < 480) { lazr.coolup += 20; win = false; } }
					if (evn.key.code == sf::Keyboard::N) { win = false; }
					if (evn.key.code == sf::Keyboard::Escape) { win = false; window.close(); return 0; }
				}
			}
		}
		
		//applies upgrades from load
		tow.maxhealth += tow.healthup; tow.health = tow.maxhealth; // Applies health upgrade
		lazr.strength += lazr.laserup; lazr.cool -= lazr.coolup; //Applies laser strength and wait period upgrades
		tow.sprit(tow.healthup); //Applies respective sprite based on health upgrade
		//
				
		for (int i = 0; i < level; i++)	{
			if (i >= bad.size()) {
				baddy w(level);
				bad.push_back(w);
			}
			bad[i].inpos(i);
			//bad[i].speed = 2*(((50.0 - level) > 0) ? double(1 / (50.0 - level)) : double(level / 2000.0));
			bad[i].speed = 2.0 * double(level) / 500.0;
		}
		int badc = 0, frame = 0;

		//Displayes info on sfml screen
		string str = "Level " + to_string(level - 9) + "\nLaser damage: " + to_string(lazr.strength) + "\nCooldown: " + to_string(lazr.cool) + "\n";
		Text levl; levl.setString(str);	levl.setColor(Color::White); levl.setPosition(125, 10);	levl.setCharacterSize(20);	levl.setFont(font);

		Text bananas;
		str = "Bananas: " + to_string(bad.size() - bad[0].ripc());
		bananas.setString(str);	bananas.setColor(Color::Yellow); bananas.setPosition(450, 10); bananas.setCharacterSize(20); bananas.setFont(font);
		//

		while (window.isOpen()) {
			frame++;
			window.clear();
			window.draw(tow.sprite);
			window.draw(levl);
			str = "Bananas: " + to_string(bad.size() - bad[0].ripc());
			bananas.setString(str);
			window.draw(bananas);
			for (int i = 0; i < bad.size(); i++)	{
				if (bad[i].dead) { continue; }
				//Convilutedly checks for loss, incriments baddies across screen, and lowers tower's health on collision all at once				
				if (tow.hit(bad[i].iter()) == false) {
					bad[0].rips(); badc == 0, frame = 0; bad.empty();
					window.clear();
					Text text;
					text.setString("Game Over");
					text.setColor(Color::Red);
					text.setPosition(110, 330);
					text.setCharacterSize(100);
					text.setFont(font);
					while (true) {
						//window.clear();
						window.draw(text);
						bar.setPosition(Vector2f(-1000, -1000)); max.setPosition(Vector2f(-1000, -1000)); bad[0].tots();
						window.display();
						Event event1;
						while (window.pollEvent(event1)) {
							if (event1.type == sf::Event::KeyPressed) { return 0; }
							else { continue; }
						}
					}
				}
				else {
					window.draw(bad[i].sprite);
					/////////laser animation;
					while (bad[badc].dead && badc < bad.size()-1) { badc++; }
					if (lazr.shoot(bad[badc].func, frame, bad[badc].getx(), bad[badc].gety())==true) {
						bad[badc].hit(lazr.strength, badc);
						window.draw(lazr.lazt);
					}
					if (frame - lazr.frame <= double(lazr.cool) / 3.0 && frame > lazr.cool &&win == false) { window.draw(lazr.lazt); }
					 
					//////////////health bar
					window.draw(max);
					bar.setSize(Vector2f((double((double(tow.health) / double(tow.maxhealth))) * 200.0), 20));
					window.draw(bar);
					window.draw(tow.heal);
				}
			}
			window.display();
			//checks for win
			if (bad[0].ripc() >= level) {
				win = true;
				save(level + 1, tow.healthup, lazr.laserup, lazr.coolup, win);
				while (brake == 0) {
					window.clear(); bar.setPosition(Vector2f(-1000, -1000)); max.setPosition(Vector2f(-1000, -1000));
					Text text, text2;
					text.setString("You Win!"); text2.setString("Press any key to\nstart the next game!\n\nPress \"Esc\" to quit!");
					text.setColor(Color::Blue); text2.setColor(Color(0, 100, 255));
					text.setPosition(160, 250); text2.setPosition(235, 400);
					text.setCharacterSize(100); text2.setCharacterSize(30);
					text.setFont(font); text2.setFont(font);
					window.draw(text); window.draw(text2);
					window.display();
					Event event2;
					while (window.pollEvent(event2)) {
						if (event2.type == sf::Event::KeyPressed) {	
							if (event2.key.code == sf::Keyboard::Escape) { window.close(); return 0; }	
							else { brake = 1; bad[0].rips(); bad[0].tots(); }
						}
						else { continue; }
					}
				}
				if (brake = 1) { brake = 0; break; }
			}
			//Checks for certain events
			Event event;
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed) { window.close(); }
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Escape) { window.close(); return 0; }
					if (event.key.code == sf::Keyboard::P) {
						cout << "Hit enter to resume\n"; cin.get();
					}
				}
			}
		}
	}
}