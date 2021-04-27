#pragma once
#include "DEFINITIONS.h"
class Level {
protected:
	// rows and columns
	int height{ 0 }, width{ 0 };
	int deckSize{ 0 };
	int pairsLeft;
	// difficulty (0-2)
	int level{ 0 };
public:
	virtual void setLevel(int _level) = 0;
	virtual void loadCardsEasy() = 0;
	virtual void loadCardsMedium() = 0;
	virtual void loadCardsHard() = 0;

};