#pragma once
#include<string>
#include<chrono>
#include<SFML/Graphics.hpp>

// SCREEN
// main screen size
constexpr int SCREEN_WIDTH = 720;
constexpr int SCREEN_HEIGHT = 640;

// current score screen size
constexpr int CSCORE_SCREEN_WIDTH = 260;
constexpr int CSCORE_SCREEN_HEIGHT = 180;

// FILES
// game font file
const std::string FONT_FILE = "bahnschrift.ttf";
const std::string HIGHSCORES = "highscores.txt";

// game title
const std::string GAME_TITLE = "Gra Memory";
const std::wstring SCORE_TITLE = L"Tabela wyników";

// BOARD SIZE
// easy
constexpr int EASY_ROWS = 3;
constexpr int EASY_COLUMNS = 4;
constexpr int EASY_DECK = 6;
// medium
constexpr int MED_ROWS = 4;
constexpr int MED_COLUMNS = 5;
constexpr int MED_DECK = 10;
// hard
constexpr int HARD_ROWS = 5;
constexpr int HARD_COLUMNS = 6;
constexpr int HARD_DECK = 15;

// time - needed to use game timer
typedef std::chrono::system_clock::time_point timePoint;

// max vector length of certain score level
constexpr int MAX_SCL = 5;

//button size
constexpr int BUTTON_WIDTH = 180;
constexpr int BUTTON_HEIGHT = 40;

constexpr int TOP_BANNER_WIDTH = 300;
constexpr int TOP_BANNER_HEIGHT = 50;



