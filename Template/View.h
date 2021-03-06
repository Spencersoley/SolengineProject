#pragma once

#include <Solengine/GLSLProgram.h>
#include <Solengine/Camera2D.h>
#include <Solengine/SpriteBatch.h>
#include <Solengine/Window.h>
#include <Solengine/Font.h>

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>


class View
{
public:
	View();
	~View();

	void init(Solengine::Camera2D* cam, Solengine::Camera2D* uiCam, int screenwidth, int screenheight);
	void update();

private:
	void drawGame();

	void drawUI();

	Solengine::GLSLProgram m_SOL_shaderProgram;
	Solengine::Window m_SOL_window;
	Solengine::SpriteBatch m_SOL_agentSpriteBatch;
	Solengine::SpriteBatch m_SOL_uiSpriteBatch;

	Solengine::Font* p_SOL_spriteFont = nullptr;

	Solengine::Camera2D* p_SOL_cam = nullptr;
	Solengine::Camera2D* p_SOL_uiCam = nullptr;

	int m_screenHeight;
	int m_screenWidth;
	int m_currentLevel;
};

