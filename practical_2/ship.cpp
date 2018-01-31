#include "ship.h"
#include "game.h"
#include "bullet.h"

using namespace sf;
using namespace std;

bool Invader::direction = true;
float Invader::speed = 20.0f;
const float playerSpeed = 400.f;
float Invader::bottom_row = 0.0f;
int Invader::count = 0;

const Keyboard::Key controls[3] = {
	Keyboard::Left,  // Player1 LEFT
	Keyboard::Right, // Player1 RIGHT
	Keyboard::Space
};

Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
	_exploded = false;
};

void Ship::Update(const float &dt) {
	if (is_exploded()) {
		explosionTimer -= dt;
		if (explosionTimer <= -2) {
			setTextureRect(IntRect(-32, -32, 32, 32));
		}
	}
}

void Ship::Explode() {
	setTextureRect(IntRect(128, 32, 32, 32));
	_exploded = true;
}

bool Ship::is_exploded() const{
	return _exploded;
}

// Define the ship deconstructor
// Although we set this to pure virtual, we still have to define it
Ship::~Ship() = default;

Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
}

void Invader::Update(const float &dt) {
	Ship::Update(dt);

	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);
	
	bottom_row = 0.0f;
	count = 0;

	for (int i = 0; i < ships.size() - 1; ++i) {
		if (!ships[i]->is_exploded()) {
			count++;
			if (ships[i]->getPosition().y > bottom_row) {
				bottom_row = ships[i]->getPosition().y;
			}
		}
		
	}
	if (!is_exploded() &&
		((direction && getPosition().x > gameWidth - 16) ||
		(!direction && getPosition().x < 16))) {
		direction = !direction;
		for (int i = 0; i < ships.size() - 1; ++i) {
			ships[i]->move(0, 24);
		}
	}

	static float firetime = 0.0f;
	firetime -= dt;
	static float firerate = 1.0f;
	if (count < 50) {
		firerate = 1.5f;
		speed = 50.0f;
	}
	if (count < 40) {
		firerate = 2.0f;
		speed = 100.0f;
	}
	if (count < 30) {
		firerate = 3.0f;
		speed = 150.0f;
	}
	if (count < 15) {
		firerate = 4.0f;
		speed = 200.0f;
	}
	if (count < 5) {
		firerate = 5.0f;
		speed = 300.0f;
	}

	if (firetime <= 0 && rand() % 100 == 0 && getPosition().y == bottom_row && !is_exploded()) {
		Bullet::Fire(getPosition(), true);
		firetime = 4.0f * firerate + (rand() % 60);
	}
}


Player::Player() : Ship(IntRect(160, 32, 32, 32)) {
	setPosition({ gameWidth * .5f, gameHeight - 32.f });
}

void Player::Update(const float &dt) {
	Ship::Update(dt);;
	float direction = 0.0f;
	if (Keyboard::isKeyPressed(controls[0])) {
		direction--;
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		direction++;
	}
	move(direction * playerSpeed * dt, 0);
	if (getPosition().x < 0) {
		move(2, 0);
	}
	else if (getPosition().x + 32 > gameWidth) {
		move(-2, 0);
	}
	
	static float firetime = 0.0f;
	firetime -= dt;
	if (firetime <= 0 && Keyboard::isKeyPressed(controls[2])) {
		Bullet::Fire(getPosition(), false);
		firetime = 0.7f;
	}

}