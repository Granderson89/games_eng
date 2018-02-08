#include "ghost.h"
#include <cstdlib>

using namespace std;
using namespace sf;


void Ghost::update(double dt) {
	// Move randomly
	sf::Vector2f direction(0.0f, 0.0f);
	direction.x += (float) rand() / RAND_MAX * 2.0f - 1.0f;
	direction.y += (float)rand() / RAND_MAX * 2.0f - 1.0f;
	Entity::move(direction * _speed * (float)dt);
	Entity::update(dt);
}

Ghost::Ghost() : _speed(200.0f), Entity(make_unique<CircleShape>(25.0f)) {
	_shape->setFillColor(Color::Blue);
	_shape->setOrigin(Vector2f(25.0f, 25.0f));
}

void Ghost::render(sf::RenderWindow &window) const {
	window.draw(*_shape);
}