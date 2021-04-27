#include"Score.h"
#include<chrono>
#include<ctime>
#include<Windows.h>
#include<iomanip>
#include<sstream>
#include<iostream>
using namespace std::chrono;
Score::Score(int v, int l, std::string d) {
	this->value = v;
	this->level = l;
	this->date = d;
}
int Score::getValue() {
	return this->value;
}
int Score::getLevel() {
	return this->level;
}
std::string Score::getDate() {
	return this->date;
}

void Score::setValue(int _value) {
	this->value = _value;
}
void Score::setLevel(int _level) {
	this->level = _level;
}
void Score::setDate() {
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);
	std::tm buf;
	localtime_s(&buf, &in_time_t);
	std::stringstream ss;
	ss << std::put_time(&buf, "%Y-%m-%d %X");
	this->date = ss.str();
	std::cout << "date: " << date << std::endl;
}
bool Score::operator >(const Score& ref) const{
	return (this->value > ref.value);
}

