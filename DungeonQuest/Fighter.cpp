#include "Fighter.h"

#include "Solengine/ResourceManager.h"

Fighter::Fighter() 
{
}

Fighter::~Fighter()
{
}

void Fighter::init(glm::vec2 coords, Solengine::SpriteBatch* spriteBatch)
{
	m_energy = 20;
	m_health = 20;
    m_name = "Fighter";

	m_coords = coords;
	m_position.x = m_coords.x * TILE_WIDTH;
	m_position.y = m_coords.y * TILE_WIDTH;

	p_SOL_SB = spriteBatch;

	m_textureID = Solengine::ResourceManager::getTexture("Textures/zombie_pack/fighter.png").textureID;
}
