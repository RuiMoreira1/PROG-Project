#include "gameSymbol.h"



/*
 * @brief If the player dies updates is state
 */
void Player::updateState(playerState state, char playerSymbol) {
    this->state = state;
    this->symbol = playerSymbol;
}

/*
 * @return The symbol correspondent to the class type
 */
char Player::getSymbol() const {
    return this->symbol;
}

playerState Player::getState() const {
    return this->state;
}

void Player::setWon() {
    this->won = true;
}

bool Player::getWon() const{
    return this->won;
}


/*
 * @brief If the robot dies or gets stuck updates is state
 */
void Robot::updateState(robotState state, char playerSymbol) {
    this->state = state;
    this->symbol = playerSymbol;
}

/*
 * @return The symbol correspondent to the class type
 */
char Robot::getSymbol() const {
    return this->symbol;
}

int Robot::getID() const {
    return this->ID;
}

robotState Robot::getState() const {
    return this->state;
}

Fence::Fence(Position *position, char fenceSymbol) : gameSymbol(position), symbol(fenceSymbol) {
    if( fenceSymbol == FENCE ) { this->fenceState = Electrified; this->electrocute = true; }
    else { this->fenceState = NonElectrified; this->electrocute = false; }
}


/*
 * @return The symbol correspondent to the class type
 */
char Fence::getSymbol() const {
    return this->symbol;
}

void Fence::disableFence() {
    this->fenceState = NonElectrified;
    this->electrocute = false;
}

fenceElectrified Fence::getFenceState() const{
    return this->fenceState;
}

void gameSymbol::updatePosition(Position *newPosition) {
    this->newPosition = newPosition;
}

int gameSymbol::getXPosition() {
    return this->newPosition->getXPosition();
}

int gameSymbol::getYPosition() {
    return this->newPosition->getYPosition();
}


char gameSymbol::getSymbol() const {
    return ' ';
}

gameSymbol::gameSymbol(Position *newPosition) {
    this->newPosition = newPosition;

}
