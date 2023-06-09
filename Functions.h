#pragma once
#include<time.h>

///Window Functions
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();
bool loadMenuMedia();
bool loadGameBoardMedia();

//Frees media and shuts down SDL
void close();

//Render game window
void renderGame();

///Menu rendering Functions
void createMenu();
bool renderMenu();

///Help Screen
bool createHelp();

///Selecting Difficulty
void createDifficulty();
bool renderDifficulty();

///Back button
bool backHandle();

///Game Functions
//Set game variables
void setDifficulty(int Level);

//Handle game events on queue
bool gameHandle();

//Check game state
bool checkWinning();

//Render number of flag/mine left
void mineManager();

//Perform win/lose flag
void flagManager();

//Render timer
void timeManager();

//Perform play again flag
void playAgainManager(bool &quitGame);

//secure first turn
void changeMine(int row, int col);

//Create game board
void initGame();

//Check if cell is within board
bool isValid(int row, int col);
