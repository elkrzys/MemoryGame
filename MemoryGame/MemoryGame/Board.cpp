#include "Board.h"
#include "ScoreManager.h"
#include "Exception.h"
#include<iostream>
#include<memory>
#include<algorithm>
#include<random>
#include<chrono>
#include<thread>

Board::Board(int _height, int _width, int _deckSize)
{
	height = _height;
	width = _width;
	deckSize = _deckSize;

	sf::String back_texture_file = "img/cards/card_back.png";
	back_texture = std::make_unique<sf::Texture>(sf::Texture());

	if (!back_texture->loadFromFile(back_texture_file))
		throw loadImageException();
}

void Board::setLevel(int _level) {
	this->pairsLeft = this->deckSize;
	this->level = _level;

	switch (this->level) {
	case 0:
		this->height = EASY_ROWS;
		this->width = EASY_COLUMNS;
		this->deckSize = EASY_DECK;
		loadCardsEasy();
		std::cout << "Load L1\n";
		break;
	case 1:
		this->height = MED_ROWS;
		this->width = MED_COLUMNS;
		this->deckSize = MED_DECK;
		loadCardsEasy();
		loadCardsMedium();
		std::cout << "Load L2\n";
		break;
	case 2:
		this->height = HARD_ROWS;
		this->width = HARD_COLUMNS;
		this->deckSize = HARD_DECK;
		loadCardsEasy();
		loadCardsMedium();
		loadCardsHard();
		std::cout << "Load L3\n";
		break;
	}
	std::cout << "exit level\n";
}

void Board::loadCardsEasy() {
	deck.push_back(std::make_shared<Card>(Card(0, std::string("img/cards/card_01.png"), back_texture)));
	deck.push_back(std::make_shared<Card>(Card(1, std::string("img/cards/card_02.png"), back_texture)));
	deck.push_back(std::make_shared<Card>(Card(2, std::string("img/cards/card_03.png"), back_texture)));
	deck.push_back(std::make_shared<Card>(Card(3, std::string("img/cards/card_04.png"), back_texture)));
	deck.push_back(std::make_shared<Card>(Card(4, std::string("img/cards/card_05.png"), back_texture)));
	deck.push_back(std::make_shared<Card>(Card(5, std::string("img/cards/card_06.png"), back_texture)));
}
void Board::loadCardsMedium() {
	deck.push_back(std::make_shared<Card>(Card(6, std::string("img/cards/card_07.png"), back_texture)));
	deck.push_back(std::make_shared<Card>(Card(7, std::string("img/cards/card_08.png"), back_texture)));
	deck.push_back(std::make_shared<Card>(Card(8, std::string("img/cards/card_09.png"), back_texture)));
	deck.push_back(std::make_shared<Card>(Card(9, std::string("img/cards/card_10.png"), back_texture)));
}
void Board::loadCardsHard() {
	deck.push_back(std::make_shared<Card>(Card(10, std::string("img/cards/card_11.png"), back_texture)));
	deck.push_back(std::make_shared<Card>(Card(11, std::string("img/cards/card_12.png"), back_texture)));
	deck.push_back(std::make_shared<Card>(Card(12, std::string("img/cards/card_13.png"), back_texture)));
	deck.push_back(std::make_shared<Card>(Card(13, std::string("img/cards/card_14.png"), back_texture)));
	deck.push_back(std::make_shared<Card>(Card(14, std::string("img/cards/card_15.png"), back_texture)));
}

void Board::setCardPosition(int i, int j, sf::Vector2u wndSize) {
	const float scrW = wndSize.x;
	const float scrH = wndSize.y;
	const float cardW = Card::width;
	const float cardH = Card::height;
	const float margin = 25.f;

	const float initialPositionX = (scrW / 2.f) - ((width * cardW + width * margin) / 2);
	const float initialPositionY = (scrH / 2.f) - ((height * cardH + height * margin) / 2);

	deck[cardsOnBoard[i*width +j].first]->setPos({ initialPositionX + j * cardW + j * margin, initialPositionY + i * cardH + i * margin});
	cardsPositions.reserve(deckSize * 2);
	cardsPositions.push_back(deck[cardsOnBoard[i * width + j].first]->getPos());
}

void Board::setCardsOnBoard() {

	cardsOnBoard.reserve(deckSize * 2);
	int k{ 0 };
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cardsOnBoard.push_back({ deck[k++]->getID(), DOWN });
			if (k == deckSize) k = 0;
		}
	}

	std::random_shuffle(cardsOnBoard.begin(), cardsOnBoard.end());
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(cardsOnBoard.begin(), cardsOnBoard.end(), std::default_random_engine(seed));

}

void Board::drawTo(sf::RenderWindow& window) {
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int currentIndex = i * width + j;
			setCardPosition(i, j, window.getSize());
				
			(cardsOnBoard[currentIndex].second == UP || cardsOnBoard[currentIndex].second == PAIRED || cardsOnBoard[currentIndex].second == UNMATCHED) ?
				 deck[cardsOnBoard[currentIndex].first]->showFace(window, cardsPositions[currentIndex]) : deck[cardsOnBoard[currentIndex].first]->showBack(window);

			//test
			/*if (currentIndex == getUnmatchedPairsPositions().first || currentIndex == getUnmatchedPairsPositions().second) {
				deck[cardsOnBoard[currentIndex].first]->showFace(window, cardsPositions[currentIndex]);
			}*/			
		}
	}
}

int Board::updateState(int index) {

	// pair position
	int pairPos{};
	// another face up card position
	int anotherUpPos{ -1 };

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {

			int currentIndex = i * width + j;
			
			// check if another wrong card is up, if not find pair
			if (cardsOnBoard[currentIndex].second == UP && cardsOnBoard[currentIndex].first != cardsOnBoard[index].first) {
				anotherUpPos = currentIndex;
				break;
			}
			else if (cardsOnBoard[currentIndex].first == cardsOnBoard[index].first && index != currentIndex)
				pairPos = currentIndex;
		}

	switch (cardsOnBoard[index].second) {
		case DOWN:
			if (anotherUpPos != -1) {
				// ok
				cardsOnBoard[index].second = UP; //<- ok
				cardsOnBoard[anotherUpPos].second = DOWN; //<-ok

				//test
				/*cardsOnBoard[index].second = UNMATCHED; 
				cardsOnBoard[anotherUpPos].second = UNMATCHED;
				setUnmatchedPairsPositions(index, anotherUpPos);*/

				anotherUpPos = -1;
				(this->unmatchedCounter)++;
			}
			else if (cardsOnBoard[pairPos].second == UP) {
				cardsOnBoard[index].second = PAIRED;
				cardsOnBoard[pairPos].second = PAIRED;
				--(this->pairsLeft);
				if (this->pairsLeft == 0) {
					std::cout << "WYGRANA\n";
					StateMachine::setCurrentState(State::GAME_WIN, true);
				}
			}
			else if (cardsOnBoard[pairPos].second == DOWN) {
				cardsOnBoard[index].second = UP;
			}
			break;
		case UNMATCHED:
			break;
	}
	return anotherUpPos;
}

void Board::Input(sf::RenderWindow& window) {
	auto mousePos = sf::Mouse::getPosition(window);

	for(int i = 0; i<height; i++)
		for (int j = 0; j < width; j++) {
			if (
				mousePos.x > cardsPositions[i*width +j].x && mousePos.x < (cardsPositions[i*width+j].x + Card::width) &&
				mousePos.y > cardsPositions[i*width +j].y && mousePos.y < (cardsPositions[i*width+j].y + Card::height)			
				) {

				updateState(i * width + j);
				
				std::cout << "Clicked Card with ID: " << deck[cardsOnBoard[i * width + j].first]->getID() << std::endl;
				std::cout << "state: " << cardsOnBoard[i * width + j].second << std::endl;
				return;
			}
		}
}

void Board::Init() {
	level = static_cast<int>(StateMachine::getCurrentState());
	this->setLevel(level);
	this->setCardsOnBoard();
}
void Board::Run(sf::RenderWindow &window) {

	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), GAME_TITLE);
	window.setFramerateLimit(30);
	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				StateMachine::setCurrentState(State::MENU_STATE, true);
				//window.close();
				break;
			case sf::Event::MouseButtonPressed:
			{
				if (event.mouseButton.button == sf::Mouse::Left) {
					this->Input(window);
				}
			}
			break;
			}
		}
		window.clear(sf::Color(43, 45, 66));
		this->drawTo(window);
		window.display();

		if (StateMachine::getCurrentState() == State::MENU_STATE
			|| StateMachine::getCurrentState() == State::GAME_WIN) break;
	}
}