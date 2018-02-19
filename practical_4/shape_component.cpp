#include "shape_component.h"
#include "system_renderer.h"

using namespace sf;
using namespace std;

/*
*	SHAPE COMPONENT
*/

void ShapeComponent::update(double dt) {
	_shape->setPosition(_parent->getPosition());
}

void ShapeComponent::render() { Renderer::queue(_shape.get()); }

sf::Shape& ShapeComponent::getShape() const { return *_shape; }

ShapeComponent::ShapeComponent(Entity* p)
	: Component(p), _shape(make_shared<sf::CircleShape>()) {}

