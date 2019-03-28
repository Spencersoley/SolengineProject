#pragma once

#include <glm/glm.hpp>

#include "Solengine/SpriteBatch.h"
#include "Level.h"

const float AGENT_WIDTH = 64.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;
//const int TILE_WIDTH = 64;

class Unit
{
public:
	Unit(glm::vec2 coords);
	~Unit();

	//virtual void move(float adjustedDeltaTicks, int globalFrameCount, std::vector<Human*>& humans, std::vector<Zombie*>& zombies) = 0;

	void draw(Solengine::SpriteBatch& _spriteBatch);

	glm::vec2 getPosition() const { return m_position; }	
	glm::vec2 getCoords() const { return m_coords; }


	std::string getName() const { return m_name; }
	int getHealth() { return m_health; }
	int getEnergy() { return m_energy; }

protected:

	int m_energy;
	int m_health;

	std::string m_name;

	glm::vec2 m_position;
	glm::vec2 m_coords;
	Solengine::ColourRGBA8 m_colour;
};

