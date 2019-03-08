#include "Controller.h"

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::init(View* view)
{
	p_view = view;
}

void Controller::initPlayer(Player* player)
{
	p_player = player;
	p_player->initInputManager(&m_SOL_inputManager);
}

Solengine::GameState Controller::playStateInput()
{
	const float CAMERA_SPEED = 2.0f;
	const float SCALE_SPEED = 0.1f;

	Solengine::GameState state = m_SOL_inputManager.processInput();

	if (m_SOL_inputManager.keyPress(SDLK_p))
	{
		state = Solengine::GameState::PAUSE; 
	}
	if (m_SOL_inputManager.keyState(SDLK_q))
	{
		p_view->scale(SCALE_SPEED);
	}
	if (m_SOL_inputManager.keyState(SDLK_e))
	{
		p_view->scale(-SCALE_SPEED);
	}

	return state;
}

Solengine::GameState Controller::pauseStateInput()
{
	m_SOL_inputManager.processInput();
	Solengine::GameState state = Solengine::GameState::PAUSE;

	//This needs to check keydown

	if (m_SOL_inputManager.keyPress(SDLK_p))
	{
		state = Solengine::GameState::PLAY;
	}

	return state;
}
