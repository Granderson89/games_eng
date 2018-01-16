#pragma once
#include <SFML/Graphics.hpp>
#include "game.h"

class Ship : public sf::Sprite {
protected:
	sf::IntRect _sprite;
	Ship();
public:

	explicit Ship(sf::IntRect ir);

	virtual ~Ship() = 0;

	virtual void Update(const float &dt);
};

class Invader : public Ship {
public:
	static bool direction;
	static float speed;

	Invader(sf::IntRect ir, sf::Vector2f pos);
	Invader();
	void Update(const float &dt) override;
};

class Player : public Ship {
public:
	Player();
	void Update(const float &dt) override;
};