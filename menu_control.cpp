#include "menu_control.h"


Menu::Menu( int options, bool Loop) {
    this->options = options;
    this->Loop = Loop;
}

/**
 * @brief Get the private field options from the class
 * @return class variable options
 */
int Menu::getOptions() const {
    return this->options;
}

/**
 * @brief Static method, considering it only display a message and given that the message is always the same
 * we can make it static. Displays the menu options
 */
void Menu::showOptions() {
    cout << "Game Menu\nEnter the integer value of the option wanted\n";
    cout << "0 -> Exit || 1 -> Rules || 2 -> Play || 3 -> Winners\n";
}

/**
 * @brief Function to read the inputs from keyboard related to the menu options
 * @return 0
 */
int Menu::readOption() {
    cout << "Enter option -> ";
    cin >> options;
    if(cin.fail()){
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "BAD INPUT DETECTED\n";
        sleep(1);
        return ERROR;
    }
    else if(options != 0 && options != 1 && options != 2 && options != 3){
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "BAD INPUT DETECTED\n";
        sleep(1);
        return ERROR;
    }
    return SUCCESS;
}

/**
 * @brief Displays the game rules
 */
void Menu::displayRules(){
    string rules = "files/Rules.txt";
    fileHandler::readFile(rules);
}

/**
 * @brief GameLoop variable set to true, if the player wants to play
 */
void Menu::LoopActivate() {
    this->Loop = true;
}

/**
 * @brief GameLoop variable set to false, if the player doesn't want to play anymore
 */
void Menu::LoopDisable() {
    this->Loop = false;
}

/**
 * @brief Function that controls the menu flow
 * @return 0 in case of success, 1 otherwise
 */
int Menu::menuFlow() {
    showOptions();
    while (true) if(readOption() == SUCCESS) break;
    if( options == PLAY )
    {
        LoopActivate();
        return 0;
    }
    else if ( options == EXIT ){
        LoopDisable();
        cout << "Game ended\n";
        sleep(1);
        return 0;
    }
    else if ( options == RULES ){
        displayRules();
        return menuFlow();
    }
    else if( options == SHOW_WINNERS ){
        string winnerFile;
        cout << "Winner file number -> ";
        cin >> winnerFile;
        string temp = "files/MAZE_" + winnerFile + "_WINNERS.txt";
        fileHandler::readFile(temp);
        return menuFlow();
    }
    else return ERROR;
}

bool Menu::getLoop() const {
    return this->Loop;
}

