#pragma once

///Window Functions
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Render game window
void renderGame();

///Menu Functions
void createMenu();
bool showMenu();

///Game Functions
//Handle game events on queue
bool gameHandle();

//Check game state
bool checkWinning();

//Render number of flag/mine left
void mineManager();

//Perform win/lose flag
void flagManager();

//Perform play again flag
void playAgainManager(bool &quitGame);

//secure first turn
void changeMine(int row, int col);

//Create game board
void placeMines();
