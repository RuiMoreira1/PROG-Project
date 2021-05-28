#include <iostream>
#include "menu_control.h"
#include "game.h"
#include "maze.h"
#include <chrono>
using namespace std;

int main() {

    string str;
    string temp;
    Menu *menu = new Menu(3,true);
    Game game;
    clock_t tStart = clock();

    while(true) {
        menu->menuFlow();
        if( !menu->getLoop() ) break;
        if (game.mazeChecker(temp) != SHOW_INIT_MENU) {
            game.mazeBuilder();
            break;
        }
    }
    while(menu->getLoop()){
        while(true) if (game.playerMovementHandler() == SUCCESS) break;
        game.fillGameBoard();
        game.drawGameBoard();
        int var = game.gameEnded();
        if( var == 1 ){
            menu->LoopDisable();
            cout << "Player died\n";
        }
        else if( var == 2 ) {
            clock_t finish = clock();
            menu->LoopDisable();
            string playerName;
            game.getPlayerName(playerName);
            auto duration = (int) (finish - tStart) / CLOCKS_PER_SEC;
            fileHandler::buildFile(game.getMazeNumber(), (int) duration, playerName);
            cout << "Player won, all the bots were destroyed\n";
        }
    }

    return 0;
}
