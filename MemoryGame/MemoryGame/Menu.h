#pragma once
#include<SFML/Graphics.hpp>
#include"Button.h"
#include"StateMachine.h"
#include<vector>

class Menu : protected StateMachine {
	int countButtons = 0;
	std::vector<Button> buttons;
	sf::Font menuFont;
	sf::RectangleShape topBanner;
	sf::Text topBannerText;

public:
	//title
	Menu(sf::String title);
	//size, posistion, banner color, text color
	void setTopBanner(sf::Vector2f size, sf::Vector2f pos, sf::Color bannerColor, sf::Color txtColor);
	void isMouseHover(sf::RenderWindow& window);
	int isMouseClicked(sf::RenderWindow &window);
	// count, text
	void setButtons(int countBtn, std::vector<sf::String> btnTexts);
	void drawTo(sf::RenderWindow &window);

	void Init() override;
	void Run(sf::RenderWindow& window) override;
	

};
