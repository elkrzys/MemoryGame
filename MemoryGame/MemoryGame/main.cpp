#include <SFML/Graphics.hpp>
#include"Button.h"
#include"Menu.h"
#include"Board.h"
#include"StateMachine.h"
#include"App.h"
#include"Exception.h"
//#include<stdexcept>
#include<iostream>

int main()
{
    try {
        App app;
        app.Run();
    }
    catch (std::exception &e) {
        std::string msg = e.what();
        ExceptionWindow::callExceptionWindow(msg); // CALL WINDOWS MESSAGE BOX
        std::cout << e.what();
    }


    return 0;
}