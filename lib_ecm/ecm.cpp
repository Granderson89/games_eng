#include "ecm.h"

using namespace std;
using namespace sf;

Entity::Entity() : _rotation(0.0f), _alive(true), _visible(true), _fordeletion(false) {}

Entity::~Entity() = default;

void Entity::update(double dt) {
	for (const auto& component : _components)
		component->update(dt);
}

void Entity::render() {
	for (const auto& component : _components)
		component->render();
}

const sf::Vector2f &Entity::getPosition() const{
	return _position;
}

void Entity::setPosition(const Vector2f & pos) { 
	_position = pos; 
}

float Entity::getRotation() const{
	return _rotation;
}

void Entity::setRotation(const float rotation) {
	_rotation = rotation;
}

bool Entity::isAlive() const {
	return _alive;
}

void Entity::setAlive(const bool alive) {
	_alive = alive;
}

bool Entity::isVisible() const {
	return _visible;
}

void Entity::setVisible(const bool visible) {
	_visible = visible;
}

bool Entity::is_fordeletion() const {
	return _fordeletion;
}

void Entity::setForDelete() {
	_fordeletion = true;
}

Component::Component(Entity* const parent) : _parent(parent), _fordeletion(false) {}

Component::~Component() = default;

bool Component::is_fordeletion() const {
	return _fordeletion;
}