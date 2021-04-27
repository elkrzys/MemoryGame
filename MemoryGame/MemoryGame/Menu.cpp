#include "Menu.h"
#include "Board.h"
#include "ScoreManager.h"
#include "Exception.h"
#include<iostream>

Menu::Menu(sf::String title){
	if (!menuFont.loadFromFile(FONT_FILE)) throw loadFontException();
	else topBannerText.setString(title);
}

void Menu::setTopBanner(sf::Vector2f size, sf::Vector2f pos, sf::Color bannerColor, sf::Color txtColor) {

	topBanner.setSize(size);
	topBanner.setPosition({pos.x , pos.y});
	topBanner.setFillColor(bannerColor);

	topBannerText.setFont(menuFont);
	topBannerText.setCharacterSize(30);
	topBannerText.setFillColor(txtColor);	

	sf::FloatRect textRect = topBannerText.getLocalBounds();
	topBannerText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	topBannerText.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, 55));

}

void Menu::isMouseHover(sf::RenderWindow &window){
	for (int i = 0; i < countButtons; i++) {
		if (buttons[i].isMouseOver(window)) buttons[i].changeBgColor(sf::Color::Green);
		else buttons[i].changeBgColor(sf::Color(245, 183, 0));
	}
}

int Menu::isMouseClicked(sf::RenderWindow &window) {
	int clickedButtonID = -1;
	for (int i = 0; i < countButtons; i++) {
		if (buttons[i].isMouseOver(window)) {
			clickedButtonID = buttons[i].getButtonID();
			break;
		}			
	}
	if(clickedButtonID != -1)
	std::cout << "You clicked button ID: " << clickedButtonID << " name: " << buttons[clickedButtonID].getText() << std::endl;
	return clickedButtonID;
}

void Menu::setButtons(int countBtn, std::vector<sf::String> btnTexts){
	countButtons = countBtn;
	float buttonWidth = 180, buttonHeight = 40;
	buttons.resize(countButtons);
	buttons[0] = Button(0, { buttonWidth, buttonHeight }, { SCREEN_WIDTH / 2 - buttonWidth / 2, 110 }, btnTexts[0], menuFont);
	buttons[1] = Button(1, { buttonWidth, buttonHeight }, { SCREEN_WIDTH / 2 - buttonWidth / 2, 170 }, btnTexts[1], menuFont);
	buttons[2] = Button(2, { buttonWidth, buttonHeight }, { SCREEN_WIDTH / 2 - buttonWidth / 2, 230 }, btnTexts[2], menuFont);
	buttons[3] = Button(3, { buttonWidth, buttonHeight }, { SCREEN_WIDTH / 2 - buttonWidth / 2, 290 }, btnTexts[3], menuFont);
	buttons[4] = Button(4, { buttonWidth, buttonHeight }, { SCREEN_WIDTH / 2 - buttonWidth / 2, 350 }, btnTexts[4], menuFont);

}

void Menu::drawTo(sf::RenderWindow& window){
	window.draw(topBanner);
	window.draw(topBannerText);

	for (int i = 0; i < countButtons; i++) {
		buttons[i].drawTo(window);
	}
}

void Menu::Init() {
	std::cout << "INICJALIZACJA MENU" << std::endl;
	this->setTopBanner({ TOP_BANNER_WIDTH, TOP_BANNER_HEIGHT }, { SCREEN_WIDTH / 2 - TOP_BANNER_WIDTH / 2, 30 }, sf::Color(245, 183, 0), sf::Color(1, 32, 92));
	this->setButtons(5, { L"£atwy (3x4)", L"Œredni (4x5)", L"Trudny (5x6)", "Wyniki", L"Wyjœcie" });

	StateMachine::setCurrentState(State::MENU_STATE, true);
}

void Menu::Run(sf::RenderWindow &window) {
	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), GAME_TITLE);
	window.setFramerateLimit(30);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseMoved:
			{
				this->isMouseHover(window);
			}
			case sf::Event::MouseButtonPressed:
			{
				if (event.mouseButton.button == sf::Mouse::Left) {

					// TODO: osobna funckja wyboru
					switch (this->isMouseClicked(window)) {
					case 0:
						StateMachine::setCurrentState(State::GAME_EASY_STATE, true);
						//run Board easy
						break;
					case 1:
						StateMachine::setCurrentState(State::GAME_MEDIUM_STATE, true);
						//run Board medium
						break;
					case 2:
						StateMachine::setCurrentState(State::GAME_HARD_STATE, true);
						//run Board hard
						break;
					case 3:
						StateMachine::setCurrentState(State::SHOW_SCORE_STATE, true);
						//show scoreboard
						break;
					case 4:
						StateMachine::setCurrentState(State::EXIT_STATE, true);
						window.close();
						break;
					}
				}
			}
			break;
			}
		}

		window.clear(sf::Color(43, 45, 66));
		this->drawTo(window);
		window.display();
		// interrupt when state is updated
		if (StateMachine::isUpdating()) break;
	}
}