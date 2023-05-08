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
extern int DISTANCE_W;
extern int DISTANCE_H;

//The sound effects that will be used
extern Mix_Chunk *click;

//Globally used font
extern TTF_Font *gFont;

//Button texture
extern SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];
extern LTexture gButtonSpriteSheetTexture;

//Digit texture
extern SDL_Rect gDigitSprites[DIGIT_SPRITE_TOTAL];
extern LTexture gDigitSpriteSheetTexture;

//In game image
extern LTexture menuTheme;
extern LTexture helpTheme;
extern LTexture difficultyTheme;
extern LTexture easyTable;
extern LTexture mediumTable;
extern LTexture hardTable;
extern LTexture winFace;
extern LTexture loseFace;
extern LTexture backIcon;

//In game text
extern LTexture gTextTexturePlay;
extern LTexture gTextTextureExit;
extern LTexture gTextTextureHelp;
extern LTexture gTextTexturePlayColor;
extern LTexture gTextTextureExitColor;
extern LTexture gTextTextureEasy;
extern LTexture gTextTextureMedium;
extern LTexture gTextTextureHard;
extern LTexture gTextTextureEasyColor;
extern LTexture gTextTextureMediumColor;
extern LTexture gTextTextureHardColor;
extern LTexture gTextTextureChallenge;
extern LTexture gTextTextureChallengeColor;

///Game variables
//Flag
extern bool backMenu;

//Table's size
extern int BOARD_WIDTH;
extern int BOARD_HEIGHT;

//Board data
extern std::vector <std::vector<int> > curBoard;
extern std::vector <std::vector<int> > realBoard;

//Gameplay variables
extern int MINES;
extern int DIFFICULTY;
extern int TIME_LIMIT;
extern int countMineLeft;
extern int countTileLeft;
extern bool gameOver;
extern bool isWinning;
extern bool firstMove;
extern bool challengeMode;



