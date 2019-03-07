#pragma once

#include "Agent.h"

class Zombie : public Agent
{
public:
	Zombie();
	~Zombie();

	void init(float speed, glm::vec2 pos);

	void move(std::vector<Human*>& humans, std::vector<Zombie*>& zombies, float deltaTime, int globalFrameCount) override;

private:
	Human* getNearestHuman(std::vector<Human*>& humans);
	void redirect();

	Human* p_nearestHuman = nullptr;
};

