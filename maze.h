#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "fileHandler.h"
#include "gameSymbol.h"
#include "utils.h"
#include "unistd.h"

using namespace std;

class Maze {
public:
    int mazeChecker(string &number, string &mazeFile, int mazeNumber);
    void mazeBuilder(string &mazeFile, int mazeRows, int mazeCol, vector<vector<gameSymbol*>> &maze
                    ,Player *player ,vector<Robot*> &robotVec, vector<Fence*> &fenceVec, int robotID);
    gameSymbol* mazeAddSymbols(char symbol, int xPos, int yPos, Player *player, vector<Robot*> &robotVec, vector<Fence*> &fenceVec, int robotID );
};


