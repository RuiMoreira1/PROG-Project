#pragma once

#define ERROR -1
#define SUCCESS 0
#define SHOW_INIT_MENU 1

#define DELIMITER 'x'

//MENU OPTIONS

#define EXIT 0
#define PLAY 2
#define RULES 1
#define SHOW_WINNERS 3


//GAME SYMBOLS && STATES

#define ROBOT_ALIVE 'R'
#define ROBOT_DEAD 'r'
#define ROBOT_STUCK 'r'
#define PLAYER_ALIVE 'H'
#define PLAYER_DEAD 'h'
#define FENCE '*'
#define HARMLESS_FENCE '+'
#define EXIT_DOOR 'O'
#define CLEAR_PATH ' '
#define ALIVE true
#define DEAD false


//PLAYER MOVEMENT

#define PLAYER_Q 'Q'
#define PLAYER_S 'S'
#define PLAYER_W 'W'
#define PLAYER_E 'E'
#define PLAYER_A 'A'
#define PLAYER_D 'D'
#define PLAYER_X 'X'
#define PLAYER_Z 'Z'
#define PLAYER_C 'C'

typedef enum robotState { DEADROBOT, ALIVEROBOT, STUCKROBOT } robotState;

typedef enum playerState { PLAYERALIVE, PLAYERDEAD} playerState;

typedef enum fence { Electrified, NonElectrified } fenceElectrified;




