#include "maze.h"


/**
 * @brief Function to check the existence of the file wanted
 * @param number
 * @return 0 in case of success, 1 if the users wants the init menu shown again
 */
int Maze::mazeChecker(string &number, string &mazeFile, int mazeNumber) {
    string fileName = "files/MAZE_";
    cout << "Maze Number -> ";
    cin >> number; cout << endl;
    if(cin.fail() || ( number.size() > 2 )){
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "BAD INPUT DETECTED\n";
        sleep(1);
        return ERROR;
    }
    else{
        if( number == "0" ) return SHOW_INIT_MENU;
        fileName += number + ".txt";
        if( !(fileHandler::checkExistingFile(fileName) ) ) {
            cerr << "THE FILE YOU WERE LOOKING FOR DOESN'T EXIT\n";
            sleep(1);
            return ERROR;
        }
        cout << "THE MAZE YOU WERE LOOKING FOR EXISTS\n";
        mazeFile = fileName;
        mazeNumber = stoi(number);
    }
    return SUCCESS;
}

/*
 * @bried Function to build the initial maze to be displayed
 */
void Maze::mazeBuilder(string &mazeFile, int mazeRows, int mazeCol, vector<vector<gameSymbol*>> &maze, Player *player,
                       vector<Robot*> &robotVec, vector<Fence*> &fenceVec, int robotID) {
    Player temp;
    vector<string> mazed;
    fileHandler::readFile(mazed, mazeFile);
    vector<string> parsedString = Utils::parseString(mazed[0],DELIMITER);
    mazeRows = stoi(parsedString[0]);
    mazeCol = stoi(parsedString[1]);
    maze.resize(mazeRows+1, vector<gameSymbol* >(mazeCol)); //Resizing vector for the appropriate number of cols and rows
    for( int row = 0; row < mazed.size()-1; row++){
        cout << row;
        for( int col = 0; col < mazeCol; col++){
            maze[row][col] = mazeAddSymbols(mazed[row+1][col],row,col,player,robotVec, fenceVec, robotID);
            cout << maze[row][col]->getSymbol();
        }
        cout << endl;
    }
}

/*
 * @brief Add class characters and class objects to the maze
 * @param symbol - symbol identifier
 * @param xPos - 2d vector x position
 * @param yPos - 2d vector y position
 * @return gameSymbol pointer
 */
gameSymbol* Maze::mazeAddSymbols(char symbol, int xPos, int yPos, Player *player, vector<Robot*> &robotVec, vector<Fence*> &fenceVec, int robotID ) {
    try {
        if (symbol == PLAYER_ALIVE) {
            player = new Player(new Position(xPos,yPos), PLAYERALIVE);
            return player;
        }
        else if (symbol == ROBOT_ALIVE) {
            robotID++;
            auto *bot = new Robot(new Position(xPos,yPos),ALIVEROBOT, robotID);
            robotVec.push_back(bot);
            return bot;
        }
        else if (symbol == FENCE) {
            auto *fence = new Fence(new Position(xPos,yPos), FENCE);
            fenceVec.push_back(fence);
            return fence;
        }
        else if (symbol == HARMLESS_FENCE) {
            auto *fence = new Fence(new Position(xPos,yPos), HARMLESS_FENCE);
            fenceVec.push_back(fence);
            return fence;
        }
        else if (symbol == EXIT_DOOR) {
            auto *fence = new Fence(new Position(xPos,yPos), EXIT_DOOR);
            fenceVec.push_back(fence);
            return fence;
        }
        else if (symbol == CLEAR_PATH) {
            return new gameSymbol(new Position(xPos,yPos));
        }
        else throw gameSymbolNotFound(symbol);
    }
    catch( gameSymbolNotFound &exc ){
        cerr << exc.getException() << endl;
        exit(EXIT_FAILURE);
    }
}