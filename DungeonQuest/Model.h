#pragma once

#include <SDL/SDL.h>
#include <Solengine/GameState.h>
#include <Solengine/Camera2D.h>
#include <Solengine/InputManager.h>

#include "Unit.h"
#include "UIText.h"
#include "UIButton.h"
#include "UIIcon.h"

class Model
{
public:
	Model();
	~Model();

	void init(float physicsSpeed, Solengine::Camera2D* cam);

	void awake();

	Solengine::GameState update(int pauseDuration, std::vector<Unit*> units);
	
	//GETTERS
	bool getLeftMouse()
	{
		return m_SOL_inputManager.keyState(SDL_BUTTON_LEFT);
	}

	bool getRightMouse()
	{
		return m_SOL_inputManager.keyState(SDL_BUTTON_RIGHT);
	}

	glm::ivec2 getMouseScreenPos()
	{
		return m_SOL_inputManager.getMouseCoords();
	}

	glm::ivec2 getMouseWorldPos()
	{
		return p_SOL_cam->screenToWorld(getMouseScreenPos());
	}

	//SETTERS
	void setSelectedUnit(Unit* unit);

	glm::ivec2 getMouseCoordinates()
	{
		return flatten(getMouseWorldPos(), TILE_WIDTH);
	}

	glm::ivec2 flatten(glm::ivec2 vec2, int c)
	{
		return { floor(vec2.x / c), floor(vec2.y / c) };
	}

    void setCurrentUnit(Unit* unit) { p_currentUnit = unit; }                   

	void setCurrentUnitIcon(UIIcon* icon) { p_currentUnitIcon = icon; }

	void setCurrentUnitNameText(UIText* text) 
	{
		p_currentUnitNameText = text; 
	}

	void setCurrentUnitHealthText(UIText* text) 
	{
		p_currentUnitHealthText = text;
	}

	void setCurrentUnitEnergyText(UIText* text) 
	{
		p_currentUnitEnergyText = text;
	}

	void setCurrentUnitBox(UIIcon* icon) { p_currentUnitBox = icon; }

	void setSelectedUnitIcon(UIIcon* icon) { p_selectedUnitIcon = icon; }

	void setSelectedUnitNameText(UIText* text) 
	{
		p_selectedUnitNameText = text; 
	}

	void setSelectedHealthText(UIText* text)
	{ 
		p_selectedUnitHealthText = text; 
	}

	void setSelectedEnergyText(UIText* text) 
	{ 
		p_selectedUnitEnergyText = text;
	}

	void setSelectionBox(UIIcon* icon) { p_selectionBox = icon; }

	void setHoverHighlight(UIIcon* icon) { p_hoverHighlight = icon; }

    void setWalkableHighlight(UIIcon* icon) { p_walkableHighlight = icon; }

	void setTileMap(TileMap* tileMap) { p_tileMap = tileMap; }

private:
	Solengine::InputManager m_SOL_inputManager;
	Solengine::Camera2D* p_SOL_cam;
	
	Unit* p_selectedUnit = nullptr;
	Unit* p_currentUnit = nullptr;

	
	UIIcon* p_currentUnitIcon = nullptr;
	UIText* p_currentUnitNameText = nullptr;
	UIText* p_currentUnitHealthText = nullptr;
    UIText* p_currentUnitEnergyText = nullptr;
    UIIcon* p_currentUnitBox = nullptr;
	
	UIIcon* p_selectedUnitIcon = nullptr;
	UIText* p_selectedUnitNameText = nullptr;
	UIText* p_selectedUnitHealthText = nullptr;
	UIText* p_selectedUnitEnergyText = nullptr;
	UIIcon* p_selectionBox = nullptr;
	
	UIIcon* p_walkableHighlight = nullptr;
	UIIcon* p_hoverHighlight = nullptr;
	TileMap* p_tileMap;

	int m_turnCounter;
	float m_physicsSpeed;
	
	Uint32 getDeltaTicks();
	void movement(glm::ivec2 coords, TileMap* tileMap, Unit* currentUnit);
	Solengine::GameState nextTurn(std::vector<Unit*> units, Unit* currentUnit, 
		                          Unit* selectedUnit);
	Unit* selectionCheck(std::vector<Unit*> units, glm::ivec2 coords);

	void updateHighlight(std::vector<std::vector<Tile*>> tiles,
		               glm::ivec2 mouseCoords, UIIcon* hoverHighlight);
	bool checkIfCoordsInBound(std::vector<std::vector<Tile*>> tiles, 
		                      glm::ivec2 coords);
	void updateTileStates(TileMap* tileMap, Unit* currentUnit);
	void updateStatsDisplay(Unit* unit, UIIcon* icon, UIText* name,
	                     	UIText* health, UIText* energy);
	void updateSelectedUnitBox(Unit* selectedUnit, UIIcon* selectionBox);
    void updateCurrentUnitBox(Unit* currentUnit, UIIcon* currentUnitBox);

};