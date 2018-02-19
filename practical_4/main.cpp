#include <SFML/Graphics.hpp>
#include "system_renderer.h"
#include "ecm.h"
#include "pacman.h"
#include <iostream>

using namespace sf;
using namespace std;

const int gameWidth = 800;
const int gameHeight = 800;


void Load() {
	// Load Scene-Local Assets
	gameScene.reset(new GameScene());
	menuScene.reset(new MenuScene());
	gameScene->load();
	menuScene->load();
	// Start at main menu
	activeScene = menuScene;
}

void Update(RenderWindow &window) {
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	activeScene->update(dt);
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
}

void Render(RenderWindow &window) {
	activeScene->render();
	// flush to screen
	Renderer::render();
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PACMAN");
	Renderer::initialise(window);
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}

	Renderer::shutdown();

	return 0;
}