#pragma once

#include <Solengine/SDLInitialiser.h>
//#include <Solengine/ErrorHandler.h>
#include <Solengine/GLSLProgram.h>
#include <Solengine/GLTexture.h>
#include <Solengine/Window.h>
#include <Solengine/FPSManager.h>
#include <Solengine/TileLevelLoader.h>
#include <Solengine/Camera2D.h>
#include <Solengine/SpriteBatch.h>
#include <Solengine/InputManager.h>
#include <Solengine/GameState.h>

#include "Model.h"
#include "View.h"
#include "Level.h"

class Scene
{
public:
	Scene();
	~Scene();

	void Run();

private:
	void initSystems();
	void initScene();

	void gameLoop(Model* model, View* view);

	void deleteEntity();

	Solengine::TileLevelLoader m_SOL_tileLevelLoader;
	Solengine::FPSManager m_SOL_fpsManager;
	Solengine::Camera2D m_SOL_cam;
	Solengine::Camera2D m_SOL_uiCam;
	Model m_model;
	View m_view;

	std::vector<Level*> p_levels;
	TileMap* p_tileMap = nullptr;
	std::vector<Unit*> p_units;

	std::vector<Drawable*> p_worldDrawables;
	std::vector<Drawable*> p_overlayDrawables;

	Unit* p_currentUnit = nullptr;
	Unit* p_selectedUnit = nullptr;

	SpellBook m_spellBook;

	int m_turnCounter;
	int m_screenWidth;
	int m_screenHeight;
	int m_currentLevel;
	int m_fpsMax;
	float m_physicsSpeed;
	bool m_announceFPS;
};

