#include <SFML/Graphics.hpp>
#include "ship.h"
#include "game.h"
#include "bullet.h"
#include <iostream>
 
using namespace sf;
using namespace std;

Texture spritesheet;
Sprite invader;

std::vector<Ship*> ships;
Ship* player;

void Load() {
	if (!spritesheet.loadFromFile("C:/Users/40218994/Desktop/games_eng_build/bin/Debug/res/img/invaders_sheet.png")) {
		cerr << "Failed to load spritesheet!" << endl;
	}

	for (int r = 0; r < invaders_rows; ++r) {
		auto rect = IntRect(32 * r, 0, 32, 32);
		for (int c = 0; c < invaders_columns; ++c) {
			Vector2f position(32.0f * c + gameWidth / 4, 32.0f * r + gameHeight / 8);
			auto inv = new Invader(rect, position);
			ships.push_back(inv);
		}
	}
	player = new Player();
	ships.push_back(player);
}

void Update(RenderWindow &window) {
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	// check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	// Quit via ESC key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	for (auto &s : ships) {
		s->Update(dt);
	}
}

void Render(RenderWindow &window) {
	for (const auto s : ships) {
		window.draw(*s);
	}
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "SPACE INVADERS");
	Load();

	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}