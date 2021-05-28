#pragma once
#include "macros.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include "fileHandler.h"

using namespace std;


/*
 * @brief Class to handle the menu option and menu flow control
 * @param options - (1 -> Rules 2 -> Play 3 -> Exit)
 */
class Menu{
private:
    int options;
    bool Loop;
public:
    Menu(  int options, bool Loop );
    int getOptions() const;
    static void showOptions();
    int readOption();
    static void displayRules();
    void LoopActivate();
    void LoopDisable();
    int menuFlow();
    bool getLoop() const ;
};