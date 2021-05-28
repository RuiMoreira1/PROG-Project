#include "game.h"


/**
 * @brief Function to check the existence of the file wanted
 * @param number
 * @return 0 in case of success, 1 if the users wants the init menu shown again
 */
int Game::mazeChecker(string &number) {
    string fileName = "files/MAZE_";
    cout << "Maze Number -> ";
    cin >> number; cout << endl;
    if(cin.fail() || ( number.size() > 2 )){
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "BAD INPUT DETECTED\n";
        sleep(1);
        return mazeChecker(number);
    }
    else{
        if( number == "0" ) return SHOW_INIT_MENU;
        fileName += number + ".txt";
        if( !(fileHandler::checkExistingFile(fileName) ) ) {
            cerr << "THE FILE YOU WERE LOOKING FOR DOESN'T EXIT\n";
            sleep(1);
            return mazeChecker(number);
        }
        cout << "THE MAZE YOU WERE LOOKING FOR EXISTS\n";
        this->mazeFile = fileName;
        mazeNumber = number;
    }
    return 0;
}

/*
 * @bried Function to build the initial maze to be displayed
 */
void Game::mazeBuilder() {
    vector<string> mazed;
    fileHandler::readFile(mazed, mazeFile);
    vector<string> parsedString = Utils::parseString(mazed[0],DELIMITER);
    *mazeRows = stoi(parsedString[0]);
    *mazeCol = stoi(parsedString[1]);
    maze.resize(*mazeRows+1, vector<gameSymbol* >(*mazeCol)); //Resizing vector for the appropriate number of cols and rows
    for( int row = 0; row < mazed.size()-1; row++){
        cout << row;
        for( int col = 0; col < *mazeCol; col++){
            maze[row][col] = mazeAddSymbols(mazed[row+1][col],row,col);
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
gameSymbol* Game::mazeAddSymbols(char symbol, int xPos, int yPos) {
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

/*
 * @brief Handle the player movement
 */
int Game::playerMovementHandler() {
    string move; string keyStrokes = "QWEADXCS";
    cout << "Player pos (x,y): " << player->getXPosition() << " ," << player->getYPosition() << endl;
    cout << "Available keys ( Q/W/E/A/D/Z/X/C/S )\n";
    cout << "Player Move -> ";
    cin >> move; cout << endl;
    move[0] = toupper(move[0]);
    if( cin.fail() ){
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "BAD INPUT DETECTED\n";
        return ERROR;
    }
    else if( !Utils::conditionReducer(move[0], keyStrokes) ){
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Not a valid keystroke\n";
        sleep(1);
        return ERROR;
    }
    else if( !validPlay(move[0], player->getXPosition(), player->getYPosition()) ){
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Movement out of boundaries\n";
        sleep(1);
        return ERROR;
    }


    if( movePlayer(move[0], player->getXPosition(), player->getYPosition() ) == ERROR) return ERROR;
    cout << "Player pos (x,y): " << player->getXPosition() << " ," << player->getYPosition() << endl;
    for(Robot* &iter : robotVec){
        if(iter->getState() == DEADROBOT || iter->getState() == STUCKROBOT ) continue;
        robotMovement(iter,player->getXPosition(), player->getYPosition(), iter->getXPosition(), iter->getYPosition());
    }
    return SUCCESS;
}

/*
 * @brief Checks if the player is not moving to a place out of boundaries
 * @param symbol - symbol identifier
 * @param xPos - 2d vector x position
 * @param yPos - 2d vector y position
 * @return false in case of fall play, true otherwise
 */
bool Game::validPlay( char str, int xPos, int yPos ) {
    switch (str) {
        case PLAYER_Q:
            return !(xPos - 1 < 0 || yPos - 1 < 0);
        case PLAYER_W:
            return xPos - 1 >= 0;
        case PLAYER_E:
            return !( xPos -1 < 0 || yPos + 1 > *mazeCol-1 );
        case PLAYER_A:
            return yPos - 1 >= 0;
        case PLAYER_D:
            return yPos + 1 <= *mazeCol;
        case PLAYER_Z:
            return !( yPos - 1 < 0 || xPos + 1 > *mazeRows );
        case PLAYER_X:
            return xPos + 1 <= *mazeRows;
        case PLAYER_C:
            return !( xPos + 1 > *mazeRows || yPos + 1 > *mazeCol);
        default:
            break;
    }
    return true;
}

/*
 * @brief Player Movement function after checking if the play is valid
 * @param symbol - symbol identifier
 * @param xPos - 2d vector x position
 * @param yPos - 2d vector y position
 */
int Game::movePlayer(char str, int xPos, int yPos) {
    switch (str) {
        case PLAYER_Q:
            return movePlayerHelper(xPos - 1, yPos - 1);
        case PLAYER_W:
            return movePlayerHelper(xPos - 1, yPos);
        case PLAYER_E:
            return movePlayerHelper(xPos - 1, yPos + 1);
        case PLAYER_A:
            return movePlayerHelper(xPos, yPos - 1);
        case PLAYER_D:
            return movePlayerHelper(xPos, yPos + 1);
        case PLAYER_Z:
            return movePlayerHelper(xPos + 1, yPos - 1);
        case PLAYER_X:
            return movePlayerHelper(xPos + 1, yPos);
        case PLAYER_C:
            return movePlayerHelper(xPos + 1, yPos + 1);
        default:
            return ERROR;
    }

}

/*
 * @brief Helper function to reduce code
 * @param xPos - 2d vector x position
 * @param yPos - 2d vector y position
 */
int Game::movePlayerHelper(int xPos, int yPos){
    int var = playerCollisionDetector(xPos, yPos);
    if( var == 0 || var == 2 ){
        cout << "Good Job on killing yourself!\n";
        player->updateState(PLAYERDEAD, PLAYER_DEAD);
        return SUCCESS;
    }
    else if( var == 1 || var == 3 ){
        cerr << "Invalid Movement\n";
        sleep(1);
        return ERROR;
    }
    else if( var == 5 ){
        cout << "Player found an exit\n";
        player->setWon();
        return SUCCESS;
    }
    else {
        player->updatePosition(new Position(xPos, yPos));
        return SUCCESS;
    }
}

/*
 * @brief Detect player collisions
 * @param xPos - 2d vector x position
 * @param yPos - 2d vector y position
 * @return true upon collision, false otherwise
 */
int Game::playerCollisionDetector(int xPos, int yPos) {
    for(Robot* &it : robotVec){
        if( it->getXPosition() == xPos && it->getYPosition() == yPos ){
            if( it->getState() == ALIVEROBOT ) return 0;
            else return 1;
        }
    }
    for(Fence* &it : fenceVec){
        if( it->getYPosition() == yPos && it->getXPosition() == xPos){
            if( it->getFenceState() == Electrified ) return 2;
            else if( it->getSymbol() == EXIT_DOOR ) return 5;
            else return 3;
        }
    }
    return 4;
}

/**
 * @brief Robot automatic movement function
 * @param rbot - Robot object
 * @param PxPos - player x position
 * @param PyPos - player y position
 * @param RxPos - robot x position
 * @param RyPos - robot y position
 */
void Game::robotMovement(Robot *rbot, int PxPos, int PyPos, int RxPos, int RyPos) {
    if( PxPos == RxPos ) {
        if( PyPos > RyPos ) moveRobotHelper(RxPos, RyPos + 1, rbot);
        else moveRobotHelper(RxPos, RyPos - 1, rbot);
    }
    else if( PyPos == RyPos ) {
        if( PxPos > RxPos ) moveRobotHelper(RxPos + 1, RyPos, rbot);
        else moveRobotHelper(RxPos - 1, RyPos, rbot);
    }
    else if( PyPos > RyPos && PxPos > RxPos ){
        moveRobotHelper(RxPos + 1, RyPos + 1, rbot);
    }
    else if( PyPos < RyPos && PxPos < RxPos ){
        moveRobotHelper(RxPos - 1, RyPos - 1, rbot);
    }
    else if( PyPos < RyPos && PxPos > RxPos ){
        moveRobotHelper(RxPos + 1, RyPos - 1, rbot);
    }
    else if( PyPos > RyPos && PxPos < RxPos){
        moveRobotHelper(RxPos - 1, RyPos + 1, rbot);
    }
    else{
        cout << "Movement not found xD!\n";
    }
}

/**
 * @brief Helper funtion to reduce code
 * @param xPos - robot x position
 * @param yPos - robot y postion
 * @param rbot - Robot object
 */
void Game::moveRobotHelper(int xPos, int yPos, Robot *rbot){
    int var = robotCollisionDetector(xPos, yPos, rbot->getID());
    if( var == 2 ){
        cout << "Robot collided with fence\n";
        rbot->updateState(DEADROBOT, ROBOT_DEAD);
    }
    else if( var == 1 ){
        cout << "Robots collided\n";
        rbot->updateState(STUCKROBOT, ROBOT_STUCK);
        rbot->updatePosition(new Position(xPos,yPos));
    }
    else if( var == 3 ){
        cout << "Robot killed player!\n";
        player->updateState(PLAYERDEAD, PLAYER_DEAD);
    }
    else if(var == 4){
        cout << "Robot tried to move against a disabled/NonElectrified fence cell\n";
        rbot->updateState(STUCKROBOT, ROBOT_STUCK);
        rbot->updatePosition(new Position(xPos,yPos));
    }
    else rbot->updatePosition(new Position(xPos,yPos));
}

/**
 *
 * @param xPos - robot x position
 * @param yPos - robot y postion
 * @param ID - robot identifier
 * @return 1 upon robot-robot collision 2 upon robot-fence collision 3 robot-player collision 0 no collision occurred
 */
int Game::robotCollisionDetector(int xPos, int yPos, int ID) {
    for(Robot* &it : robotVec){
        if( it->getXPosition() == xPos && it->getYPosition() == yPos && it->getID() != ID){
            it->updateState(DEADROBOT, ROBOT_DEAD);
            return 1;
        }
    }
    for(Fence* &it : fenceVec){
        if( it->getYPosition() == yPos && it->getXPosition() == xPos ){
            if( it->getFenceState() == Electrified ){
                it->disableFence();
                return 2;
            }
            else {
                it->disableFence();
                return 4;
            }
        }
    }
    if( xPos == player->getXPosition() && yPos == player->getYPosition() ) return 3;
    return 0;
}

/**
 * @brief Fill the board with the update positions the robot vector is always displayed later so when the
 *  robot occupies a cell place it displays on top of the cell
 */
void Game::fillGameBoard() {
    auto* gg = new gameSymbol();
    for(int i = 0; i < maze.size(); i++){
        for( int j = 0; j < maze[i].size(); j++){
            maze[i][j] = gg;
        }
    }
    for(Fence* it: fenceVec){
        maze[it->getXPosition()][it->getYPosition()] = it;
    }
    for(Robot* iter : robotVec){
        maze[iter->getXPosition()][iter->getYPosition()] = iter;
    }
    maze[player->getXPosition()][player->getYPosition()] = player;
}

/**
 * @brief draw the board to the console
 */
void Game::drawGameBoard() {
    for( int i = 0; i < maze.size(); i++ ){
        for( int j = 0; j < maze[i].size(); j++ ){
            cout << maze[i][j]->getSymbol();
        }
        cout << endl;
    }
}

/**
 * @brief Check if the game has ended
 * @return 1 if ended with the player dead, 2 ended with all robots killed, 0 proceed with the game
 */
int Game::gameEnded() {
    if( player->getState() == PLAYERDEAD ) return 1;
    if(player->getWon()) return 0;
    return 2;
}

/**
 * @brief
 * @return mazefile
 */
string Game::getMazeFile() const {
    return this->mazeFile;
}

/**
 * @brief Get player name to use in winner file
 * @param str - playername
 * @return string playername
 */
string Game::getPlayerName(string &str) {
    cout << "Player Name -> ";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    getline(cin, str, '\n');
    if(str.length() > 15){
       cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n');
       return getPlayerName(str);
    }
    return str;
}


string Game::getMazeNumber() const {
    return this->mazeNumber;
}




