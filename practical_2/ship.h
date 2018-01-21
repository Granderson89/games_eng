#pragma once
#include <SFML/Graphics.hpp>

class Ship : public sf::Sprite {
protected:
	sf::IntRect _sprite;
	bool _exploded;
	// Default constructor is hidden
	Ship();
public:
	// Constructor that takes a sprite
	explicit Ship(sf::IntRect ir);
	// Pure virtual deconstructor -- makes this an abstract class
	virtual ~Ship() = 0;
	// Update, virtual so can be overriden, but not pure virtual
	virtual void Update(const float &dt);
	bool is_exploded() const;
	virtual void Explode();
	float explosionTimer = 0.0f;
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