#pragma once
#include <SFML/Graphics.hpp>
#include<string>

class Button {
	int buttonID = 0;
	bool isClicked = false;
	bool isHover = false;

	sf::RectangleShape rectButton;
	sf::Text text;


public:
	// default button
	Button();
	// setting ID, size, position, title, font
	Button(int btnID, sf::Vector2f size, sf::Vector2f pos, sf::String title, sf::Font &font);
	void setPos(sf::Vector2f);
	int getButtonID();
	std::string getText();
	// is mouse over the button
	bool isMouseOver(sf::RenderWindow& window);
	void changeBgColor(sf::Color);
	void drawTo(sf::RenderWindow& window);
};
