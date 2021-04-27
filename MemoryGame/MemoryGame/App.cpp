#include "App.h"
#include "Exception.h"
#include<iostream>
#include<time.h>
#include<chrono>

App::App() : menu(Menu(GAME_TITLE)) {
	if (!this->font.loadFromFile(FONT_FILE)) {
		throw loadFontException();
	}
	// universal window
	this->window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), GAME_TITLE);
}

void App::Run() {
	
	scoreManager = std::make_unique<ScoreManager>();
	timePoint startGame, endGame;

	int currentGameLevel{ 0 };
	while (this->window.isOpen()) {

		if (StateMachine::isUpdating()) {
			switch (StateMachine::getCurrentState()) {
			case State::INIT_STATE:
				std::cout << "App initalization" << std::endl;
				menu.Init();
				std::cout << "Run Menu" << std::endl;
				StateMachine::setCurrentState(State::MENU_STATE, false);
				menu.Run(window);
				break;

			case State::MENU_STATE:
				std::cout << "Run Menu" << std::endl;
				StateMachine::setCurrentState(StateMachine::getCurrentState(), false);
				menu.Run(window);
				break;

			case State::GAME_EASY_STATE:
				std::cout << "Run Easy" << std::endl;
				StateMachine::setCurrentState(StateMachine::getCurrentState(), false);
				currentGameLevel = static_cast<int>(StateMachine::getCurrentState());
				board = std::make_unique<Board>(EASY_ROWS, EASY_COLUMNS, EASY_DECK);
				board->Init();
				startGame = std::chrono::system_clock::now();
				board->Run(window);
				break;

			case State::GAME_MEDIUM_STATE:
				std::cout << "Run Medium" << std::endl;
				StateMachine::setCurrentState(StateMachine::getCurrentState(), false);
				currentGameLevel = static_cast<int>(StateMachine::getCurrentState());
				board = std::make_unique<Board>(MED_ROWS, MED_COLUMNS, MED_DECK);
				board->Init();
				startGame = std::chrono::system_clock::now();
				board->Run(window);
				break;

			case State::GAME_HARD_STATE:
				std::cout << "Run Hard" << std::endl;
				StateMachine::setCurrentState(StateMachine::getCurrentState(), false);
				currentGameLevel = static_cast<int>(StateMachine::getCurrentState());
				board = std::make_unique<Board>(HARD_ROWS, HARD_COLUMNS, HARD_DECK);
				board->Init();
				startGame = std::chrono::system_clock::now();
				board->Run(window);
				break;

			case State::SHOW_SCORE_STATE:
				StateMachine::setUpdate(false);
				scoreManager->initDisplay();
				StateMachine::setCurrentState(State::MENU_STATE, true);
				menu.Init();
				menu.Run(window);
				break;

			case State::GAME_WIN:
				endGame = std::chrono::system_clock::now();
				scoreManager->readScoresFile(HIGHSCORES);
				StateMachine::setUpdate(false);
				scoreManager->calculateScore(currentGameLevel, startGame, endGame, board->unmatchedCounter);
				scoreManager->addScore(currentGameLevel);
				scoreManager->processScoreVectors();
				scoreManager->displayCurrentScore();
				StateMachine::setCurrentState(State::MENU_STATE, true);
				menu.Init();
				menu.Run(window);
				break;
			}
		}
	}
}