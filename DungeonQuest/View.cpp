#include "View.h"

#include "Solengine/ResourceManager.h"

#include <iostream>
#include <glm/glm.hpp>

View::View()
{
}

View::~View()
{
}

//View needs a reference to everything we want to draw. we'll pass them all with init. We'll also create a window and initialise shader/spritebatch/camera here.
void View::init(Solengine::Camera2D* cam, Solengine::Camera2D* uiCam, int screenwidth, int screenheight)
{
	//Creates window
	m_SOL_window.create("DQ", screenwidth, screenheight, 0);

	//Initialises the shader programs
	m_SOL_shaderProgram.compileShaders("Shaders/colourShading.vert", "Shaders/colourShading.frag");
	m_SOL_shaderProgram.addAttribute("vertexPosition");
	m_SOL_shaderProgram.addAttribute("vertexColour");
	m_SOL_shaderProgram.addAttribute("vertexUV");
	m_SOL_shaderProgram.linkShaders();

	//Obtain the cameras from the scene and intiialise/position them
	p_SOL_cam = cam;
	cam->init(screenwidth, screenheight);
	p_SOL_uiCam = uiCam;
	uiCam->init(screenwidth, screenheight);
	
	//Stores the screen dimensions
	m_screenHeight = screenheight;
	m_screenWidth = screenwidth;

	//Draws the ui background panel
	glm::vec4 destRect(20, 0, m_screenWidth, 150);
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

}

void View::update(std::vector<Level*>& levels, std::vector<Unit*>& units, std::vector<UIElement*>& uiElements, Unit* currentUnit, Unit* selectedUnit)
{
	p_SOL_cam->update();
	p_SOL_uiCam->update();
	p_SOL_uiCam->setPosition(glm::vec2(m_screenWidth / 2, m_screenHeight / 2));
	drawGame(levels, units, uiElements, currentUnit, selectedUnit);
}

void View::drawGame(std::vector<Level*>& levels, std::vector<Unit*>& units, std::vector<UIElement*>& uiElements, Unit* currentUnit, Unit* selectedUnit)
{
	//Set base depth
	glClearDepth(1.0);
	//Clear colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//start the shader program
	m_SOL_shaderProgram.use();
	//DrawCode, optional? Tells it to use texture unit 0
	glActiveTexture(GL_TEXTURE0);
	//Shader uses texture 0
	GLint textureUniform = m_SOL_shaderProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	// NTS: anything that changes/moves must be redrawn. Otherwise we simply rerender.

	drawWorld(levels, units);
	drawUI(uiElements, currentUnit, selectedUnit);

	m_SOL_shaderProgram.unuse();
	m_SOL_window.swapBuffer();
}

void View::drawWorld(std::vector<Level*>& levels, std::vector<Unit*>& units)
{
	//Grab world camera matrix
	glm::mat4 projectionMatrix = p_SOL_cam->getCameraMatrix();
	GLint pUniform = m_SOL_shaderProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	drawLevel(levels);

	drawUnits(units);
}

void View::drawLevel(std::vector<Level*>& levels)
{
	static Solengine::SpriteBatch* spriteBatch = levels[0]->getSpriteBatch();

	spriteBatch->renderBatch();
}

void View::drawUnits(std::vector<Unit*>& units)
{
	//This will work for units if they share a sprite batch

	glm::vec2 agentDims(AGENT_RADIUS * 2.0f);
    
	//Draw units
	for (size_t i = 0; i < units.size(); i++)
	{
		Solengine::SpriteBatch* spriteBatch = units[i]->getSpriteBatch();
		spriteBatch->begin();
		units[i]->draw();
		spriteBatch->end();
		spriteBatch->renderBatch();
	}
}

// For now we can let this do everything every frame.
void View::drawUI(std::vector<UIElement*>& uiElements, Unit* currentUnit, Unit* selectedUnit)
{
	//Grab UI camera matrix
	glm::mat4 projectionMatrix = p_SOL_uiCam->getCameraMatrix();
	GLint pUniform = m_SOL_shaderProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
	

	//Update statistical information
	//CURRENT UNIT
	if (p_currentUnitNameTextBox != nullptr)
	{
		p_currentUnitNameTextBox->updateText(0, currentUnit->getName());
	}

	if (p_currentUnitIcon != nullptr)
	{
		p_currentUnitIcon->updateIcon(currentUnit->getTextureID());
	}

	//SELECTED UNIT
	if (p_selectedUnitNameTextBox != nullptr && selectedUnit != nullptr) //selected
	{
		p_selectedUnitNameTextBox->updateText(0, selectedUnit->getName());
	} 
	else if (p_selectedUnitNameTextBox != nullptr  && selectedUnit == nullptr) //no selected
	{
		p_selectedUnitNameTextBox->updateText(0, "");
	}

	if (p_selectedUnitIcon != nullptr  && selectedUnit != nullptr) //selected
	{
		p_selectedUnitIcon->updateIcon(selectedUnit->getTextureID());
	}
	else if (p_selectedUnitIcon != nullptr  && selectedUnit == nullptr) //no selected
	{
		p_selectedUnitIcon->updateIcon(-1);
	}


	//REDRAW PHASE

	for (size_t i = 0; i < uiElements.size(); i++)
	{
		Solengine::SpriteBatch* spriteBatch = uiElements[i]->getSpriteBatch(); //get the correct sprite batch from the element
	
		spriteBatch->begin();                                                  //begin the batch
		uiElements[i]->draw();         // Not the best way to do this... //call the draw function from the element
		spriteBatch->end();                                                    //end the batch
		spriteBatch->renderBatch();                                            //render the batch
	}

	//+ std::to_string(currentUnit->getEnergy())).c_str()
}

