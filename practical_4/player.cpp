#include "player.h"
using namespace std;
using namespace sf;

const Keyboard::Key controls[4] = {
	Keyboard::Left,
	Keyboard::Right,
	Keyboard::Up,
	Keyboard::Down
};

void Player::update(double dt) {
	// Move in four directions based on keys
	sf::Vector2f direction(0.0f, 0.0f);

	if (Keyboard::isKeyPressed(controls[0])) {
		direction.x = -1.0f;
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		direction.x = 1.0f;
	}
	if (Keyboard::isKeyPressed(controls[2])) {
		direction.y = -1.0f;
	}
	if (Keyboard::isKeyPressed(controls[3])) {
		direction.y = 1.0f;
	}

	Entity::move(direction * _speed * (float)dt);
	Entity::update(dt);
}

Player::Player() : _speed(200.0f), Entity(make_unique<CircleShape>(25.0f)) {
	_shape->setFillColor(Color::Yellow);
	_shape->setOrigin(Vector2f(25.0f, 25.0f));
}

void Player::render(sf::RenderWindow &window) const {
	window.draw(*_shape);
}