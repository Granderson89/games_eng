#include <SFML/Graphics.hpp>
#include "entity.h"
#include "player.h"

using namespace sf;
using namespace std;

const int gameWidth = 800;
const int gameHeight = 600;

Entity* player;

void Load() {
	player = new Player();
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

	player->update(dt);
}

void Render(RenderWindow &window) {
	// Draw everything
	player->render(window);

}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "TILE ENGINE");
	Load();

	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}