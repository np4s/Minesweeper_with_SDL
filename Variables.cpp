#include "Variables.h"
#include "Buttons.h"
#include "Texture.h"

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Screen dimension
int SCREEN_WIDTH = 600;
int SCREEN_HEIGHT = 600;
int DISTANCE_W;
int DISTANCE_H;


//The sound effects that will be used
Mix_Chunk *click = NULL;

//Globally used font
TTF_Font *gFont = NULL;
TTF_Font *gMenuFont = NULL;

//Mouse button texture
SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];
LTexture gButtonSpriteSheetTexture;

//Digit texture
SDL_Rect gDigitSprites[DIGIT_SPRITE_TOTAL];
LTexture gDigitSpriteSheetTexture;

//In game image
LTexture gBackgroundTexture;
LTexture menuTheme;
LTexture difficultyTheme;
LTexture easyTable;
LTexture mediumTable;
LTexture hardTable;
LTexture winFace;
LTexture loseFace;
LTexture backIcon;

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
//Flag
bool backMenu;

//Table's size
int BOARD_WIDTH;
int BOARD_HEIGHT;

//Board data
std::vector <std::vector<int> > curBoard (30, std::vector<int>(30) );
std::vector <std::vector<int> > realBoard (30, std::vector<int>(30) );

//Gameplay variables
int MINES;
int DIFFICULTY;
int countMineLeft;
int countTileLeft;
bool gameOver = false;
bool isWinning = false;

//In memory text stream
stringstream mineLeft;

//Check first move
bool firstMove = true;


