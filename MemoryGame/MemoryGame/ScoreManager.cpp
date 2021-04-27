#include "DEFINITIONS.h"
#include "ScoreManager.h"
#include "StateMachine.h"
#include "Button.h"
#include "Exception.h"
#include<chrono>
#include<fstream>
#include<string>
#include<sstream>
#include<iostream>
#include<algorithm>

ScoreManager::ScoreManager() {

}

void ScoreManager::makeFile(std::string filename) {
	std::ofstream file (filename, std::ios_base::out);

	if (file.good()) {
		file << "begintable" << std::endl;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < MAX_SCL; j++) {
				file << "-;0;" << i << std::endl;
			}
		file << "endtable";
		std::cout << "plik utworzono" << std::endl;
		file.close();
	}
	else 
		throw scoresFileFail();
}

void ScoreManager::readScoresFile(std::string filename) {
	std::fstream file(filename, std::ios_base::in);
	std::string line, segment;
	std::string date;
	int score, level;

	if (!file.good()) {
		std::cout << "brak pliku" << std::endl;
		ScoreManager::makeFile(filename);
		file.open(filename);
	}
	
	if (file.good()) {
		// loading scores
		std::getline(file, line);
		if (line == "begintable")
			while (getline(file, line) && line != "endtable") {
				std::vector<std::string> segments;
				std::stringstream ss(line);

				while (std::getline(ss, segment, ';')) {
					segments.push_back(segment);
				};
				level = std::stoi(segments[2]);
				score = std::stoi(segments[1]);
				date = segments[0];

				if (level == 0) easyScores.push_back(Score(score, level, date));
				else if (level == 1) mediumScores.push_back(Score(score, level, date));
				else if (level == 2) hardScores.push_back(Score(score, level, date));
			}
		else { // wrong begin flag
			ScoreManager::makeFile(filename);
			readScoresFile(filename);
		}
		std::cout << "File read success" << std::endl;
	}
	else 
		throw scoresFileFail();
	file.close();

	sortScores();
	
}

void ScoreManager::saveScoresFile(std::string filename) {
	std::fstream file(filename, std::ios_base::out);
	if (file.good()) {
		file << "begintable" << std::endl;
		for (int i = 0; i < MAX_SCL; i++)
			file << easyScores[i].getDate() << ';' << easyScores[i].getValue() << ';' << easyScores[i].getLevel() << std::endl;
		for (int i = 0; i < MAX_SCL; i++)
			file << mediumScores[i].getDate() << ';' << mediumScores[i].getValue() << ';' << mediumScores[i].getLevel() << std::endl;
		for (int i = 0; i < MAX_SCL; i++)
			file << hardScores[i].getDate() << ';' << hardScores[i].getValue() << ';' << hardScores[i].getLevel() << std::endl;
		file << "endtable";
	}
	else 
		throw scoresFileFail();
	file.close();
}

void ScoreManager::displayCurrentScore() {
	sf::Font font;
	if (!font.loadFromFile(FONT_FILE)) throw loadFontException();

	sf::RenderWindow scoreWindow(sf::VideoMode(CSCORE_SCREEN_WIDTH, CSCORE_SCREEN_HEIGHT), "Wynik");
	scoreWindow.setFramerateLimit(30);

	sf::Text score;
	score.setFont(font);
	score.setFillColor(sf::Color::White);
	std::stringstream ss;
	ss << this->currentScore.getValue();
	score.setString(ss.str());
	sf::FloatRect textRect = score.getLocalBounds();
	score.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	score.setPosition({ CSCORE_SCREEN_WIDTH / 2.0f,
		CSCORE_SCREEN_HEIGHT / 2.0f});

	while (scoreWindow.isOpen()) {
		sf::Event event;
		while (scoreWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				scoreWindow.close();
		}
		scoreWindow.clear();
		scoreWindow.draw(score);
		scoreWindow.display();
	}
}

void ScoreManager::initDisplay() {

	sf::Font font;
	if (!font.loadFromFile(FONT_FILE)) throw loadFontException();

	sf::Text scoreHeader;
	scoreHeader.setFont(font);
	scoreHeader.setFillColor(sf::Color(245, 183, 0));
	scoreHeader.setStyle(sf::Text::Bold);

	std::vector<sf::Text> scoresToDisplay;
		
	this->readScoresFile(HIGHSCORES);

	// easy
	scoreHeader.setString(L"Poziom ³atwy");
	
	scoresToDisplay.push_back(scoreHeader);
	for (int i = 0; i < MAX_SCL; i++) {
		std::stringstream ss;
		ss << easyScores[i].getDate() << ' ' << easyScores[i].getValue();
		sf::Text tmp;
		tmp.setString(ss.str());
		tmp.setFillColor(sf::Color::White);
		scoresToDisplay.push_back(tmp);
	}
	// medium
	scoreHeader.setString(L"Poziom œredni");
	scoresToDisplay.push_back(scoreHeader);
	for (int i = 0; i < MAX_SCL; i++) {
		std::stringstream ss;
		ss << mediumScores[i].getDate() << ' ' << mediumScores[i].getValue();
		sf::Text tmp;
		tmp.setString(ss.str());
		tmp.setFillColor(sf::Color::White);
		scoresToDisplay.push_back(tmp);
	}
	//hard
	scoreHeader.setString(L"Poziom trudny");
	scoresToDisplay.push_back(scoreHeader);
	for (int i = 0; i < MAX_SCL; i++) {
		std::stringstream ss;
		ss << hardScores[i].getDate() << ' ' << hardScores[i].getValue();
		sf::Text tmp;
		tmp.setString(ss.str());
		tmp.setFillColor(sf::Color::White);
		scoresToDisplay.push_back(tmp);
	}

	for (int i = 0; i < scoresToDisplay.size(); i++) {
		
		scoresToDisplay[i].setFont(font);
		scoresToDisplay[i].setCharacterSize(20);
		auto bounds = scoresToDisplay[i].getGlobalBounds();
		scoresToDisplay[i].setPosition({ (SCREEN_WIDTH / 2) - (bounds.width / 2), (float)i * 35 + 10 });
	}
	displayScoreWindow(scoresToDisplay);
}

void ScoreManager::displayScoreWindow(std::vector<sf::Text> allScores) {
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), SCORE_TITLE);
	window.setFramerateLimit(30);
	
	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				break;
			}
		}
		
		window.clear(sf::Color(43, 45, 66));
		for (int i = 0; i < allScores.size(); i++) {
			window.draw(allScores[i]);
		}
		window.display();
	}
}

void ScoreManager::calculateScore(int gameLevel, timePoint start, timePoint end, int unmatchedPairs) {
	
	std::chrono::duration<double> elapsed_seconds = end - start;

	//calculating (10000 is base score)
	int score = 10000 - (
		((125 - (gameLevel * 25)) * unmatchedPairs)
		+ (elapsed_seconds.count() * (33 - (gameLevel * 11))));
	
	if (score < 0) score = 0;

	this->currentScore.setLevel(gameLevel);
	this->currentScore.setValue(score);
	this->currentScore.setDate();

}

// all score sort
void ScoreManager::sortScores() {
	ScoreManager::sortScore<Score>(easyScores);
	ScoreManager::sortScore<Score>(mediumScores);
	ScoreManager::sortScore<Score>(hardScores);
}

void ScoreManager::addScore(int level) {
	switch (level) {
	case 0:
		easyScores.push_back(currentScore);
		break;
	case 1:
		mediumScores.push_back(currentScore);
		break;
	case 2:
		hardScores.push_back(currentScore);
		break;
	}
	std::cout << "addition complete" << std::endl;
}

void ScoreManager::processScoreVectors() {
	if (easyScores.size() > 5) {
		processScore<Score>(easyScores);
	}
	if (mediumScores.size() > 5) {
		processScore<Score>(mediumScores);
	}
	if (hardScores.size() > 5) {
		processScore<Score>(hardScores);
	}

	this->saveScoresFile(HIGHSCORES);

}