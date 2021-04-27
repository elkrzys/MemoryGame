#pragma once
#include "Menu.h"
#include "Board.h"
#include "StateMachine.h"
#include "ScoreManager.h"
#include "DEFINITIONS.h"

class App{
	Menu menu;
	std::unique_ptr<Board> board;
	std::unique_ptr<ScoreManager> scoreManager;
	sf::RenderWindow window;

	sf::Font font;
public:
	App();
	// main loop
	void Run();
};