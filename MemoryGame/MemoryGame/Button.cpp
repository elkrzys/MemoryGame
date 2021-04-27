#include "DEFINITIONS.h"
#include "Button.h"
#include<iostream>

Button::Button() {
	rectButton.setSize({ BUTTON_WIDTH, BUTTON_HEIGHT });
}
Button::Button(int btnID, sf::Vector2f size, sf::Vector2f pos, sf::String title, sf::Font &font) 
	: buttonID(btnID)
{
	rectButton.setSize(size);
	rectButton.setPosition(pos);
	rectButton.setFillColor(sf::Color(245, 183, 0)); //default color before hover
	text.setFont(font);
	text.setCharacterSize(20);
	text.setString(title);
	text.setFillColor(sf::Color(1, 32, 92)); //default background color
	//set text position to center
	sf::FloatRect textRect = text.getLocalBounds();
	sf::FloatRect btnRect = rectButton.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	
	text.setPosition({ pos.x + btnRect.width / 2, pos.y + btnRect.height / 2 });
}
int Button::getButtonID() {
	return this->buttonID;
}
std::string Button::getText() {
	return this->text.getString();
}
void Button::setPos(sf::Vector2f pos) {
	rectButton.setPosition(pos);
}
bool Button::isMouseOver(sf::RenderWindow &window) {
	auto mousePos = sf::Mouse::getPosition(window);
	auto translatedMousePos = window.mapPixelToCoords(mousePos);
	if (rectButton.getGlobalBounds().contains(translatedMousePos))
		return true;
	else 
		return false;
}
void Button::changeBgColor(sf::Color color) {
	rectButton.setFillColor(color);
}
void Button::drawTo(sf::RenderWindow& window) {
	window.draw(rectButton);
	window.draw(text);
}