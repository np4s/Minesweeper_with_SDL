#include "Variables.h"
#include "Buttons.h"

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//The sound effects that will be used
Mix_Chunk *click = NULL;

//Globally used font
TTF_Font *gFont = NULL;

//Mouse button texture
SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];
LTexture gButtonSpriteSheetTexture;

//In game image
LTexture gBackgroundTexture;
LTexture menuTheme;
LTexture levelTheme;
LTexture easyTable;
LTexture mediumTable;
LTexture hardTable;

//In game text
LTexture gTextTextureW;
LTexture gTextTextureL;
LTexture gMineLeftTexture;
LTexture gPlayAgainTexture;
LTexture gPlay;
LTexture gExit;
LTexture gPlayColor;
LTexture gExitColor;
LTexture gEasy;
LTexture gMedium;
LTexture gHard;
LTexture gEasyColor;
LTexture gMediumColor;
LTexture gHardColor;

///Game variables
//Gameplay variables
int countMineLeft = MINES;
int countTileLeft = SIDE * SIDE;
bool gameOver = false;
bool isWinning = false;

//In memory text stream
stringstream mineLeft;

//Board with mine
int realBoard[SIDE][SIDE];

//Board for showing
int curBoard[SIDE][SIDE];

//Check first move
bool firstMove = true;

//Check if cell is within board
bool isValid(int row, int col)
{
    return (row >= 0 && col >= 0 && row < SIDE && col < SIDE);
}

