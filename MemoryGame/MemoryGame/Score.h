#pragma once
#include<string>

// single score class
class Score {
	int value;
	int level;
	std::string date;
public:
	Score() {};
	// value, level, date
	Score(int, int, std::string);
	int getValue();
	int getLevel();
	std::string getDate();
	void setValue(int);
	void setLevel(int);
	void setDate();
	bool operator >(const Score& ref) const;
};