#include <SFML/Graphics.hpp>
#include "entity.h"
#include "player.h"
#include "ghost.h"
#include <iostream>

using namespace sf;
using namespace std;

const int gameWidth = 800;
const int gameHeight = 600;

EntityManager em;

int number_ghosts = 4;

void Load() {
	// Create player and add to entities
	auto player = make_shared<Player>();
	player->setPosition(Vector2f(100.0f, 100.0f));
	em.list.push_back(player);
	
	// Create ghosts and add to entities
	for (int i = 0; i < number_ghosts; i++) {
		auto ghost = make_shared<Ghost>();
		em.list.push_back(ghost);
	}
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

	// Update all entities
	em.update(dt);
}

void Render(RenderWindow &window) {
	// Draw all entities
	em.render(window);
}

int main() {
	Load();
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PACMAN");
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}

	return 0;
}