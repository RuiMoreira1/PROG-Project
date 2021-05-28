#pragma once
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include "fileHandler.h"
#include "gameSymbol.h"
#include "menu_control.h"
#include "maze.h"

using namespace std;

class Game {
private:
    Menu *menu = new Menu(3,true);
    Maze mazeD;
    int *mazeRows = new int;
    int *mazeCol = new int;
    int robotID = 0;
    string mazeFile;
    string mazeNumber;
    vector<Robot*> robotVec;
    vector<Fence*> fenceVec;
    Player *player;
    gameSymbol* defaultSymbol = new gameSymbol();
    vector< vector< gameSymbol *> > maze;
public:
    string getMazeFile() const;
    int mazeChecker(string &mazeNumber);
    void mazeBuilder();
    gameSymbol* mazeAddSymbols(char symbol, int xPos, int yPos);
    int playerMovementHandler();
    bool validPlay(char str, int xPos, int yPos);
    int movePlayer(char str, int xPos, int yPos);
    int playerCollisionDetector(int xPos, int yPos);
    int movePlayerHelper(int xPos, int yPos);
    void robotMovement(Robot *rbot, int PxPos, int PyPos, int RxPos, int RyPos);
    int robotCollisionDetector(int xPos, int yPos, int ID);
    void moveRobotHelper(int xPos, int yPos, Robot *rbot);
    void fillGameBoard();
    void drawGameBoard();
    string getPlayerName(string &str);
    int gameEnded();
    string getMazeNumber() const ;

    void gameLoop();
};

