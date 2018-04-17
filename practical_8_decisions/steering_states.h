#pragma once

#include "steering.h"
#include "components/cmp_state_machine.h"

class StationaryState : public State {
public:
	StationaryState() = default;
	void execute(Entity*, double) noexcept override;
};

class SeekState : public State {
private:
	Seek _steering;
	std::shared_ptr<Entity> _player;
public:
	SeekState(std::shared_ptr<Entity> owner, std::shared_ptr<Entity> player)
		: _player(player), _steering(owner.get(), player.get(), 50.0f) {}
	void execute(Entity*, double) noexcept override;
};

class FleeState : public State {
private:
	Flee _steering;
	std::shared_ptr<Entity> _player;
public:
	FleeState(std::shared_ptr<Entity> owner, std::shared_ptr<Entity> player)
		: _player(player), _steering(owner.get(), player.get(), 50.0f) {}
	void execute(Entity*, double) noexcept override;
};