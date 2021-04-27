#pragma once

#include<iostream>
#include<string>
#include<exception>
#include<Windows.h>

class loadFontException : public std::exception {
public:
	virtual const char* what() const throw() {
		return "Nie wczytano czcionki";
	}
};

class loadImageException : public std::exception {
	virtual const char* what() const throw() {
		return "Nie wczytano obrazka";
	}
};

class scoresFileFail : public std::exception {
	virtual const char* what() const throw() {
		return "Nie wczytano pliku z wynikami";
	}
};

class ExceptionWindow {
public:
	static void callExceptionWindow(std::string &msg) {
		std::wstring w_msg = std::wstring(msg.begin(), msg.end());
		const wchar_t* wndMsg = w_msg.c_str();
			MessageBoxW(NULL, wndMsg, L"B³¹d!", MB_ICONEXCLAMATION | MB_OK);
	}
};