#pragma once
#include <SFML/Graphics.hpp>

class Card {
	int ID;
	sf::Texture face_texture;
	sf::Texture back_texture;
	sf::Sprite sprite;
public:
	static constexpr float width = 75.f;
	static constexpr float height = 100.f;
	Card() : ID(-1) {};
	// id, face texture, pointer to back texture
	Card(int _id, std::string _face_texture_file, std::unique_ptr<sf::Texture> & _back_texture_ptr); 
	void showFace(sf::RenderWindow &, sf::Vector2f);
	void showBack(sf::RenderWindow&);
	void setPos(sf::Vector2f);
	int getID();
	// set margins
	void setMargin(sf::Vector2f);
	// return card position
	sf::Vector2f getPos();
};
