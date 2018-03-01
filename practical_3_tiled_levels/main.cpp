#include <SFML/Graphics.hpp>
#include "LevelSystem.h"
#include "entity.h"
#include "player.h"
#include <iostream>

using namespace sf;
using namespace std;

const int gameWidth = 800;
const int gameHeight = 600;


Entity* player;

Font font;
Text scoreText;
float timer;
float previous;
float best = FLT_MAX;
bool played = false;

bool validmove(Vector2f pos) {
	return (ls::getTileAt(pos) != ls::WALL);
}

bool endGame(Vector2f pos) {
	return (ls::getTileAt(pos) == ls::END);
}

void reset() {
	// Print the level to the console
	for (size_t y = 0; y < ls::getHeight(); ++y) {
		for (size_t x = 0; x < ls::getWidth(); ++x) {
			std::cout << ls::getTile({ x, y });
			if (ls::getTile({ x, y }) == ls::START) {
				player->setPosition(ls::getTilePosition({ x, y }) + Vector2f(30.0f, 30.0f));
			}
		}
		std::cout << std::endl;
	}
	// Update score text
	if (timer < best && played == true)
		best = timer;
	previous = timer;
	timer = 0.0f;
	scoreText.setPosition(0, 0);
	scoreText.setColor(Color::Black);
}

void Load() {
	player = new Player();
	ls::loadLevelFile("res/maze_2.txt");
	// Load font-face from res dir
	font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
	// Set text element to use font
	scoreText.setFont(font);
	// set the character size to 24 pixels  
	scoreText.setCharacterSize(24);
	reset();
}

void Update(RenderWindow &window) {
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	timer += dt;
	scoreText.setString("Current: " + to_string(timer) +
		" Previous: " + to_string(previous));
	if (best != FLT_MAX)
		scoreText.setString(scoreText.getString() + " Best: " + to_string(best));
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

	sf::Vector2f previous = player->getPosition();

	player->update(dt);

	if (!validmove(player->getPosition()))
		player->setPosition(previous);

	if (endGame(player->getPosition()))
		reset();
}

void Render(RenderWindow &window) {
	// Draw everything
	ls::render(window);
	player->render(window);
	window.draw(scoreText);
}

int main() {
	Load();
	RenderWindow window(VideoMode(gameWidth, gameHeight), "TILE ENGINE");
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
		played = true;
	}

	return 0;
}