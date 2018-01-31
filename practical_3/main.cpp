#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const int gameWidth = 800;
const int gameHeight = 600;



void Load() {
	
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

}

void Render(RenderWindow &window) {
	// Draw everything

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