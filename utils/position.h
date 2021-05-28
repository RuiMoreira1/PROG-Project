#pragma once

class Position{
private:
    int x,y;
public:
    Position( int x, int y ) {
        this->x = x;
        this->y = y;
    }

    explicit Position( Position *position ){
        this->x = position->getXPosition();
        this->y = position->getYPosition();
    }

    int getYPosition() const { return this->y; }
    int getXPosition() const { return this->x; }

    void setPosition(Position *position) { this->x = position->getXPosition(); this->y = position->getYPosition(); }


};