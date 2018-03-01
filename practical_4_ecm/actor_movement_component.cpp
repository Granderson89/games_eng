#include "actor_movement_component.h"
#include "levelsystem.h"

using namespace sf;

const Keyboard::Key controls[4] = {
	Keyboard::Left,
	Keyboard::Right,
	Keyboard::Up,
	Keyboard::Down
};

/*
*	ACTOR MOVEMENT COMPONENT
*/
bool ActorMovementComponent::validMove(const sf::Vector2f& pos) {
	return (LevelSystem::getTileAt(pos) != LevelSystem::WALL);
}

ActorMovementComponent::ActorMovementComponent(Entity* p)
	: _speed(100.0f), Component(p) {}

float ActorMovementComponent::getSpeed() const {
	return _speed;
}

void ActorMovementComponent::setSpeed(float speed) {
	_speed = speed;
}

void ActorMovementComponent::move(const sf::Vector2f& p) {
	auto pp = _parent->getPosition() + p;
	if (validMove(pp)) {
		_parent->setPosition(pp);
	}
}

void ActorMovementComponent::move(float x, float y) {
	move(Vector2f(x, y));
}

/*
*	PLAYER MOVEMENT COMPONENT
*/

PlayerMovementComponent::PlayerMovementComponent(Entity* p)
	: ActorMovementComponent(p) {}

void PlayerMovementComponent::update(double dt) {
	// Move in four directions based on keys
	sf::Vector2f direction(0.0f, 0.0f);

	if (Keyboard::isKeyPressed(controls[0])) {
		direction.x = -1.0f * dt;
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		direction.x = 1.0f * dt;
	}
	if (Keyboard::isKeyPressed(controls[2])) {
		direction.y = -1.0f * dt;
	}
	if (Keyboard::isKeyPressed(controls[3])) {
		direction.y = 1.0f * dt;
	}

	move(direction * _speed);
}

/*
*	EMENY AI COMPONENT
*/

static const Vector2i directions[] = { Vector2i{ 1, 0 },Vector2i{ 0, 1 },Vector2i{ 0, -1 },Vector2i{ -1, 0 } };

EnemyAIComponent::EnemyAIComponent(Entity* p)
	: ActorMovementComponent(p) {
	_state = ROAMING;
	_speed = 100.f;
	_direction = Vector2f(directions[rand() % 4]);
}

void EnemyAIComponent::update(double dt) {
	// amount to move
	const auto mva = (float)(dt * _speed);
	// Current position
	const Vector2f pos = _parent->getPosition();
	// Next position
	const Vector2f newpos = pos + _direction * mva;
	// Inverse of our current direction
	const Vector2i baddir = -1 * Vector2i(_direction);
	// Random new direction
	Vector2i newdir = directions[(rand() % 4)];

	switch (_state) {
	case ROAMING:
		// Wall in front or at waypoint
		if (LevelSystem::getTileAt(newpos) == LevelSystem::WALL ||
			LevelSystem::getTileAt(pos) == LevelSystem::WAYPOINT) {
			// start rotate
			_state = ROTATING;
		}
		else {
			// keep moving
			move(_direction * mva);
		}
		break;

	case ROTATING:
		// Don't reverse
		// and don't pick a direction that will lead to a wall
		while (newdir == baddir || LevelSystem::getTileAt(pos + Vector2f(newdir) * mva) == LevelSystem::WALL) {
			// pick new direction
			newdir = directions[(rand() % 4)];
		}
		_direction = Vector2f(newdir);
		_state = ROTATED;
		break;

	case ROTATED:
		// have we left the waypoint?
		if (LevelSystem::getTileAt(pos) != LevelSystem::WAYPOINT) {
			_state = ROAMING; // yes
		}
		move(_direction * mva); // no
		break;

	default:
		break;
	}
	ActorMovementComponent::update(dt);
}