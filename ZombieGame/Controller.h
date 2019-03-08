#pragma once

#include <Solengine/InputManager.h>
#include <Solengine/GameState.h>

#include "View.h"
#include "Player.h"

class Controller
{
public:
	Controller();
	~Controller();

	void init(View* view);
	void initPlayer(Player* player); //best practice? what about passing a reference every function call?
	Solengine::GameState playStateInput();
	Solengine::GameState pauseStateInput();

private:
	Solengine::InputManager m_SOL_inputManager;

	View* p_view;
	Player* p_player;

};

