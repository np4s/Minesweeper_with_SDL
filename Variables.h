#pragma once

#include <SDL_mixer.h>
#include <sstream>
#include "Texture.h"
#include "Constants.h"
#include "Buttons.h"

///Window variables
//The window we'll be rendering to
extern SDL_Window* gWindow;

//The window renderer
extern SDL_Renderer* gRenderer;

//Screen dimension
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int DISTANCE_BETWEEN;

//The sound effects that will be used
extern Mix_Chunk *click;

//Globally used font
extern TTF_Font *gFont;
extern TTF_Font *gMenuFont;

//Mouse button texture
extern SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];
extern LTexture gButtonSpriteSheetTexture;

//In game image
extern LTexture gBackgroundTexture;
extern LTexture menuTheme;
extern LTexture difficultyTheme;
extern LTexture easyTable;
extern LTexture mediumTable;
extern LTexture hardTable;

//In game text
extern LTexture gTextTextureW;
extern LTexture gTextTextureL;
extern LTexture gMineLeftTexture;
extern LTexture gPlayAgainTexture;
extern LTexture gPlay;
extern LTexture gExit;
extern LTexture gPlayColor;
extern LTexture gExitColor;
extern LTexture gEasy;
extern LTexture gMedium;
extern LTexture gHard;
extern LTexture gEasyColor;
extern LTexture gMediumColor;
extern LTexture gHardColor;

///Game variables
//Table's size
extern int SIDE;

//Board data
extern std::vector <std::vector<int> > curBoard;
extern std::vector <std::vector<int> > realBoard;

//Gameplay variables
extern int MINES;
extern int DIFFICULTY;
extern int countMineLeft;
extern int countTileLeft;
extern bool gameOver;
extern bool isWinning;

//In memory text stream
extern stringstream mineLeft;

//Check first move
extern bool firstMove;



