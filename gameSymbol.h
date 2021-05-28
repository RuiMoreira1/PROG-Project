#pragma once
#include "macros.h"
#include <vector>
#include "position.h"

class gameSymbol {
private:
    Position *newPosition;
    char symbol = CLEAR_PATH;
public:
    gameSymbol() = default;
    gameSymbol(Position *newPosition);
    void updatePosition(Position *newPosition);
    int getXPosition();
    int getYPosition();
    virtual char getSymbol() const;
};


class Player: public gameSymbol{
private:
    playerState state;
    char symbol = PLAYER_ALIVE;
    bool won = false;
public:
    Player() = default;
    Player(Position *position, playerState state) : gameSymbol(position) { this->state = state; }
    void updateState(playerState state, char playerSymbol);
    char getSymbol() const override;
    void setWon();
    bool getWon() const;
    playerState getState() const;
};

class Robot: public gameSymbol{
private:
    int ID;
    robotState state;
    char symbol = ROBOT_ALIVE;
public:
    Robot(Position *position, robotState state, int ID) : gameSymbol(position) , state(state), ID(ID) {}
    void updateState(robotState state, char playerSymbol);
    int getID() const;
    char getSymbol() const override;
    robotState getState() const;

};

class Fence: public gameSymbol{
private:
    char symbol;
    bool electrocute;
    fenceElectrified fenceState;
public:
    Fence(Position *position, char fenceSymbol);
    char getSymbol() const override;
    void disableFence();
    fenceElectrified getFenceState() const;
};