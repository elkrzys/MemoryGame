#pragma once
#include<SFML/Graphics.hpp>
#include "DEFINITIONS.h"
#include "Score.h"
#include<string>
#include<vector>
#include<iostream>

class ScoreManager {
	Score currentScore;
	// max length of score table is 5 (3x5 vecs) MAX_SCL
	std::vector<Score> easyScores;
	std::vector<Score> mediumScores;
	std::vector<Score> hardScores;
public:
	ScoreManager();
	static void makeFile(std::string);
	void readScoresFile(std::string);
	void saveScoresFile(std::string);
	void displayCurrentScore();
	void initDisplay();
	void displayScoreWindow(std::vector<sf::Text>);
	// level, time start, time end, number of unmatched cards
	void calculateScore(int gameLevel, timePoint start, timePoint end, int unmachetdPairs);
	void sortScores();
	void addScore(int level);
	void processScoreVectors();

	template<class T>
	static bool greaterThan(const T& a, const T& b){
		return (a > b);
	}

	template<class T>
	static void sortScore(std::vector<T> &sv) {
		std::sort(sv.begin(), sv.end(), ScoreManager::greaterThan<Score>);
	}

	template<class T>
	static void processScore(std::vector<T> &sv) {
		sortScore<T>(sv);
		sv.pop_back();
	}
};