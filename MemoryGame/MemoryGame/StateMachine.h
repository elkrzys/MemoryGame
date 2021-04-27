#pragma once
#include <SFML/Graphics.hpp>

enum class State {
	// buttons
	INIT_STATE = -1,
	GAME_EASY_STATE = 0,
	GAME_MEDIUM_STATE = 1,
	GAME_HARD_STATE = 2,
	SHOW_SCORE_STATE = 4,
	EXIT_STATE = 5,

	//game state menu, win, lose
	MENU_STATE = 99,
	GAME_STATE = 100,
	GAME_WIN = 101,
	GAME_OVER = 102,
	CLOSE_WINDOW = 999
};

class StateMachine {
	// is state being updated
	static bool updating;
	static State currentState;

public:
	
	static void setCurrentState(State newState, bool _isUpdating);
	static void setUpdate(bool);
	static State getCurrentState();
	static bool isUpdating();

	virtual void Init() = 0;
	virtual void Run(sf::RenderWindow&) = 0;
	

};
