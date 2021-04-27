#include "Card.h"
#include"Exception.h"
#include<iostream>

Card::Card(int _id, std::string _face_texture_file, std::unique_ptr<sf::Texture> & _back_texture_ptr) 
{
	ID = _id;

	if (!(face_texture).loadFromFile(_face_texture_file)) {
		throw loadImageException();
		return;
	}
	back_texture = *_back_texture_ptr;
}

void Card::setPos(sf::Vector2f pos) {
	sprite.setPosition(pos);
}

sf::Vector2f Card::getPos() {
	return sprite.getPosition();
}

int Card::getID() { 
	return this->ID; 
}

void Card::setMargin(sf::Vector2f mm) {
	sprite.move(mm.x, mm.y);
}

void Card::showFace(sf::RenderWindow &window, sf::Vector2f pos) {
	sprite.setPosition(pos);
	sprite.setTexture(face_texture);
	window.draw(sprite);
}

void Card::showBack(sf::RenderWindow& window) {
	sprite.setTexture(back_texture);
	window.draw(sprite);
}