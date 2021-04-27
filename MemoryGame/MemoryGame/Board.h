#pragma once
#include "Card.h"
#include "Level.h"
#include "StateMachine.h"

enum cardState {
	DOWN,
	UP,
	PAIRED,
	UNMATCHED // testowe
};

class Board : protected Level, public StateMachine
{
	// back texture pointer
	std::unique_ptr<sf::Texture> back_texture;
	// vector of cards that will be doubled for board
	std::vector<std::shared_ptr<Card>> deck;
	// card ID and state
	std::vector<std::pair<int, cardState>> cardsOnBoard;
	// vector of cards' positions
	std::vector<sf::Vector2f> cardsPositions;

public:
	// unmatched cards counter
	int unmatchedCounter{ 0 };

	Board() {};
	Board(int, int, int);

	// card position setter
	void setCardPosition(int, int, sf::Vector2u);
	// create board
	void setCardsOnBoard();
	// change clicked card state
	int updateState(int);
	// draw board on window
	void drawTo(sf::RenderWindow&);

	// setting game level and loading cards (from Level)
	void setLevel(int _level) override;
	inline void loadCardsEasy() override;
	inline void loadCardsMedium() override;
	inline void loadCardsHard() override;

	// init and run (from StateMachine)
	void Init() override;
	void Run(sf::RenderWindow&) override;
	// mouse operation
	void Input(sf::RenderWindow&);
};

