#include "Texture.h"
#include "Constants.h"
#include "Variables.h"
#include "Functions.h"
#include "Functions.h"

using namespace std;

//Buttons
vector< vector<LButton> > gButtons;

///Window Functions
bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {

            cout << "Warning: Linear texture filtering not enabled!";
        }

        //Create window
        gWindow = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL)
        {
            cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
            success = false;
        }
        else
        {
            //Create vsynced renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(gRenderer == NULL)
            {
                cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
                success = false;
            }
            else
            {
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags))
                {
                    cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
                    success = false;
                }

                //Initialize SDL_mixer
                if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
                    success = false;
                }

                //Initialize SDL_ttf
                if(TTF_Init() == -1)
                {
                    cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load sound effects
    click = Mix_LoadWAV("Sounds/click.wav");
    if (click == NULL)
    {
        cout << "Failed to load click sound effect! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }

    //Load sprites
    if (!gButtonSpriteSheetTexture.loadFromFile("Image/Tiles.png"))
    {
        cout << "Failed to load button sprites texture!\n";
        success = false;
    }
    else
    {
        //Set sprites
        for(int i = 0; i < BUTTON_SPRITE_TOTAL; i++)
        {
            gSpriteClips[i].x = i * TILE_SIZE;
            gSpriteClips[i].y = 0;
            gSpriteClips[i].w = TILE_SIZE;
            gSpriteClips[i].h = TILE_SIZE;
        }
    }

    //Load digits
    if (!gDigitSpriteSheetTexture.loadFromFile("Image/Digits.png"))
    {
        cout << "Failed to load digit sprites texture!\n";
        success = false;
    }
    else
    {
        //Set digits
        for (int i = 0; i < DIGIT_SPRITE_TOTAL; i++)
        {
            gDigitSprites[i].x = i * TILE_SIZE;
            gDigitSprites[i].y = 0;
            gDigitSprites[i].w = TILE_SIZE;
            gDigitSprites[i].h = 46;
        }
    }

    //Load tables
    if (!easyTable.loadFromFile("Image/easy.png"))
    {
        cout << "Failed to load easy board" << endl;
        success = false;
    }

    if (!mediumTable.loadFromFile("Image/medium.png"))
    {
        cout << "Failed to load medium board" << endl;
        success = false;
    }

    if (!hardTable.loadFromFile("Image/hard.png"))
    {
        cout << "Failed to load hard board" << endl;
        success = false;
    }

    //Load icons
    if (!winFace.loadFromFile("Image/winFace.png"))
    {
        cout << "Failed to load win face" << endl;
        success = false;
    }

    if (!loseFace.loadFromFile("Image/loseFace.png"))
    {
        cout << "Failed to load lose face" << endl;
        success = false;
    }

    if (!backIcon.loadFromFile("Image/backIcon.png"))
    {
        cout << "Failed to load easy board" << endl;
        success = false;
    }
    return success;
}

bool loadMenuMedia()
{
    //Loading success flag
    bool success = true;

    //Open the font
    gFont = TTF_OpenFont("Font/DTM-Sans.ttf", 35);
    if(gFont == NULL)
    {
        cout << "Failed to load DTM-Sans font! SDL_ttf Error: " << TTF_GetError() << endl;
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 140, 140, 140 };
        if(!gPlay.loadFromRenderedText("PLAY", textColor))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }

        if(!gExit.loadFromRenderedText("EXIT", textColor))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }

        if(!gEasy.loadFromRenderedText("EASY", textColor))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }

        if(!gMedium.loadFromRenderedText("MEDIUM", textColor))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }

        if(!gHard.loadFromRenderedText("HARD", textColor))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }

        textColor = { 0, 0, 0 };
        if(!gPlayColor.loadFromRenderedText("PLAY", textColor))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }

        if(!gExitColor.loadFromRenderedText("EXIT", textColor))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }

        if(!gEasyColor.loadFromRenderedText("EASY", textColor))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }

        if(!gMediumColor.loadFromRenderedText("MEDIUM", textColor))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }

        if(!gHardColor.loadFromRenderedText("HARD", textColor))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }
    }

    //Load scene
    if (!menuTheme.loadFromFile("Image/MenuBackground.png"))
    {
        cout << "Failed to load background texture!\n";
        success = false;
    }

    if (!difficultyTheme.loadFromFile("Image/difficultyBackground.png"))
    {
        cout << "Failed to load background texture!\n";
        success = false;
    }

    return success;
}

void close()
{
    //Free loaded textures
    gButtonSpriteSheetTexture.free();
    gMineLeftTexture.free();
    gBackgroundTexture.free();
    gTextTextureW.free();
    gTextTextureL.free();

    //Free global font
    TTF_CloseFont(gFont);
    TTF_CloseFont(gMenuFont);
    gFont = NULL;
    gMenuFont = NULL;

    //Free the sound effects
    Mix_FreeChunk(click);
    click = NULL;

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

///Menu rendering Functions
void createMenu()
{
    SDL_RenderClear(gRenderer);

    menuTheme.render(0, 0);
    gPlay.render( ( SCREEN_WIDTH - gPlay.getWidth() ) / 2, 325 );
    gExit.render( ( SCREEN_WIDTH - gExit.getWidth() ) / 2, 400 );

    SDL_RenderPresent(gRenderer);

    return;
}

bool renderMenu()
{
    //Returns Play(true) or Exit(false)
    bool inPlay = false;
    bool inExit = false;
    bool quit = false;
    SDL_Event e;

    createMenu();
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
            {
                return false;
            }

            if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEMOTION)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);

                if (x > ( SCREEN_WIDTH - gPlay.getWidth() ) / 2 && x < ( SCREEN_WIDTH - gPlay.getWidth() ) / 2 + gPlay.getWidth() && y > 325 && y < 325 + gPlay.getHeight())
                {
                    inPlay = true;
                }
                else inPlay = false;

                if (x > ( SCREEN_WIDTH - gExit.getWidth() ) / 2 && x < ( SCREEN_WIDTH - gExit.getWidth() ) / 2 + gExit.getWidth() && y > 400 && y < 400 + gExit.getHeight())
                {
                    inExit = true;
                }
                else inExit = false;

                if (e.type == SDL_MOUSEMOTION)
                {
                    if (inPlay == true)
                    {
                        gPlayColor.render( ( SCREEN_WIDTH - gPlay.getWidth() ) / 2, 325 );
                    }
                    else
                        gPlay.render( ( SCREEN_WIDTH - gPlay.getWidth() ) / 2, 325 );

                    if (inExit == true)
                    {
                        gExitColor.render( ( SCREEN_WIDTH - gExit.getWidth() ) / 2, 400 );
                    }
                    else
                        gExit.render( ( SCREEN_WIDTH - gExit.getWidth() ) / 2, 400 );
                }

                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        if (inPlay == true)
                        {
                            return true;
                        }

                        if (inExit == true)
                        {
                            return false;
                        }
                    }
                }
            }

            SDL_RenderPresent(gRenderer);
        }
    }
}

void createDifficulty()
{
    SDL_RenderClear(gRenderer);

    difficultyTheme.render(0, 0);
    gEasy.render(260, 200);
    gMedium.render(240, 275);
    gHard.render(260, 350);
    backIcon.render(40, 35);

    SDL_RenderPresent(gRenderer);

    return;
}

bool renderDifficulty()
{
    bool quit = false;
    bool inEasy = false;
    bool inMedium = false;
    bool inHard = false;
    SDL_Event e;

    createDifficulty();
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
            {
                return false;
            }

            if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEMOTION)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);

                if (x > 260 && x < 260 + gEasy.getWidth() && y > 200 && y < 200 + gEasy.getHeight())
                {
                    inEasy = true;
                }
                else inEasy = false;

                if (x > 240 && x < 240 + gMedium.getWidth() && y > 275 && y < 275 + gMedium.getHeight())
                {
                    inMedium = true;
                }
                else inMedium = false;

                if (x > 260 && x < 260 + gHard.getWidth() && y > 350 && y < 350 + gHard.getHeight())
                {
                    inHard = true;
                }
                else inHard = false;

                if (e.type == SDL_MOUSEMOTION)
                {
                    if (inEasy == true)
                    {
                        gEasyColor.render(260, 200);
                    }
                    else
                        gEasy.render(260, 200);

                    if (inMedium == true)
                    {
                        gMediumColor.render(240, 275);
                    }
                    else
                        gMedium.render(240, 275);

                    if (inHard == true)
                    {
                        gHardColor.render(260, 350);
                    }
                    else
                        gHard.render(260, 350);
                }

                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        if (inEasy == true)
                        {
                            setDifficulty(EASY);
                            quit = true;
                        }

                        if (inMedium == true)
                        {
                            setDifficulty(MEDIUM);
                            quit = true;
                        }

                        if (inHard == true)
                        {
                            setDifficulty(HARD);
                            quit = true;
                        }
                    }
                }
            }

            SDL_RenderPresent(gRenderer);
        }
    }

    return true;
}

///Game Functions
void setDifficulty(int Level)
{
    DIFFICULTY = Level;

    switch (DIFFICULTY)
    {
    case EASY:
    {
        SCREEN_WIDTH = 294;
        SCREEN_HEIGHT = 386;
        MINES = 10;
        BOARD_WIDTH = 9;
        BOARD_HEIGHT = 9;

        break;
    }

    case MEDIUM:
    {
        SCREEN_WIDTH = 488;
        SCREEN_HEIGHT = 580;
        MINES = 40;
        BOARD_WIDTH = 16;
        BOARD_HEIGHT = 16;

        break;
    }

    case HARD:
    {
        SCREEN_WIDTH = 880;
        SCREEN_HEIGHT = 582;
        MINES = 99;
        BOARD_WIDTH = 30;
        BOARD_HEIGHT = 16;

        break;
    }
    }

    DISTANCE_W = (SCREEN_WIDTH - BOARD_WIDTH * TILE_SIZE) / 2;
    DISTANCE_H = (SCREEN_HEIGHT - BOARD_HEIGHT * TILE_SIZE) / 2 + 45;
    countMineLeft = MINES;
    countTileLeft = BOARD_WIDTH * BOARD_HEIGHT;

    realBoard.resize(BOARD_HEIGHT, vector<int> (BOARD_WIDTH));
    curBoard.resize(BOARD_HEIGHT, vector<int> (BOARD_WIDTH));
    gButtons.resize(BOARD_HEIGHT, vector<LButton> (BOARD_WIDTH));


    SDL_SetWindowSize(gWindow, SCREEN_WIDTH, SCREEN_HEIGHT);

    return;
}

void renderGame()
{
    //Clear screen
    SDL_RenderClear(gRenderer);
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    //Render background and set buttons' positions
    switch (DIFFICULTY)
    {
    case EASY:
    {
        easyTable.render(0,0);
        for (int i = 0; i < BOARD_HEIGHT; i++)
        {
            for (int j = 0; j < BOARD_WIDTH; j++)
            {
                gButtons[i][j].setPosition(j * TILE_SIZE + DISTANCE_W, i * TILE_SIZE + DISTANCE_H);
            }
        }

        break;
    }

    case MEDIUM:
    {
        mediumTable.render(0,0);
        for (int i = 0; i < BOARD_HEIGHT; i++)
        {
            for (int j = 0; j < BOARD_WIDTH; j++)
            {
                gButtons[i][j].setPosition(j * TILE_SIZE + DISTANCE_W, i * TILE_SIZE + DISTANCE_H);
            }
        }

        break;
    }

    case HARD:
    {
        hardTable.render(0,0);
        for (int i = 0; i < BOARD_HEIGHT; i++)
        {
            for (int j = 0; j < BOARD_WIDTH; j++)
            {
                gButtons[i][j].setPosition(j * TILE_SIZE + DISTANCE_W, i * TILE_SIZE + DISTANCE_H);
            }
        }

        break;
    }
    }

    //Render buttons
    for(int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            gButtons[i][j].render(i, j);
        }
    }

    //Render back button
    backIcon.render(40, 35);

    //Render mine/flag left
    mineManager();

    //Perform win/lose flag
    flagManager();

    //Update screen
    SDL_RenderPresent(gRenderer);

    return;
}

bool gameHandle()
{
    //Event handler
    SDL_Event e;

    while(SDL_PollEvent(&e) != 0)
    {
        //User requests quit
        if(e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
            return true;

        //Handle button events
        for (int i = 0; i < BOARD_HEIGHT; i++)
        {
            for (int j = 0; j < BOARD_WIDTH; j++)
            {
                gButtons[i][j].handleEvent(&e);
            }
        }
        isWinning = checkWinning();
    }

    return false;
}

bool checkWinning()
{
    bool win = false;
    if (countTileLeft == MINES)
    {
        win = true;
    }
    return win;
}

void mineManager()
{
    //Render text
    if (!gameOver && !isWinning)
    {
        if (countMineLeft < 10)
        {
            gDigitSpriteSheetTexture.render(SCREEN_WIDTH / 2 - TILE_SIZE, 32, &gDigitSprites[0]);
            gDigitSpriteSheetTexture.render(SCREEN_WIDTH / 2, 32, &gDigitSprites[max(0, countMineLeft)]);
        }
        else
        {
            gDigitSpriteSheetTexture.render(SCREEN_WIDTH / 2 - TILE_SIZE, 32, &gDigitSprites[countMineLeft/10]);
            gDigitSpriteSheetTexture.render(SCREEN_WIDTH / 2, 32, &gDigitSprites[countMineLeft%10]);
        }
    }
    return;
}

void flagManager()
{
    //Check if win
    if (isWinning && !gameOver)
    {
        //Render win face
        winFace.render((SCREEN_WIDTH - winFace.getWidth()) / 2, 32);
    }

    //Check if lose
    if (gameOver)
    {
        //Render lose face
        loseFace.render((SCREEN_WIDTH - loseFace.getWidth()) / 2, 32);

        for(int i = 0; i < BOARD_HEIGHT; i++)
        {
            for (int j = 0; j < BOARD_WIDTH; j++)
            {
                curBoard[i][j] = realBoard[i][j];
                gButtons[i][j].render(i, j);
            }
        }
    }
}

void playAgainManager(bool &quitGame)
{
    //Event handler
    SDL_Event e;

    bool inFace = false;

    //Handle events on queue
    while(SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEMOTION)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);

            if (x > (SCREEN_WIDTH - loseFace.getWidth()) / 2 && x < (SCREEN_WIDTH - loseFace.getWidth()) / 2 + loseFace.getWidth() && y > 32 && y < 32 + loseFace.getHeight())
            {
                inFace = true;
            }
            else
                inFace = false;

            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                //User requests play again
                if (inFace == true)
                {
                    //Stop the music
                    Mix_HaltMusic();

                    //Recreate constants
                    countMineLeft = MINES;
                    countTileLeft = BOARD_HEIGHT * BOARD_WIDTH;

                    //Recreate flag
                    gameOver = false;
                    isWinning = false;
                    quitGame = false;
                }
            }
        }

        else if (e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT) quitGame = true;
    }
}

void placeMines()
{
    //Initialize boards
    for (int i = 0; i < BOARD_HEIGHT; i++)
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            curBoard[i][j] = 10;
            realBoard[i][j] = 0;
        }

    //Placing mines
    for (int i = 0; i < MINES;)
    {
        int random = rand() % (BOARD_HEIGHT*BOARD_WIDTH);
        int x = random / BOARD_HEIGHT;
        int y = random % BOARD_WIDTH;

        if (!isValid(x, y))
            continue;

        if (realBoard[x][y] != 9)
        {
            for (int dx = -1; dx <= 1; dx++)
                for (int dy = -1; dy <= 1; dy++)
                    if ((dx || dy) && isValid(x+dx, y+dy) && realBoard[x+dx][y+dy] != 9)
                        realBoard[x+dx][y+dy]++;

            realBoard[x][y] = 9;
            i++;
        }
    }

    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
            cout << realBoard[i][j];
        cout << endl;
    }
    return;
}

void changeMine(int row, int col)
{
    realBoard[row][col] = 0;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if ((i || j) && isValid(row+i, col+j))
            {
                if (realBoard[row+i][col+j] == 9)
                    realBoard[row][col]++;
                else
                    realBoard[row+i][col+j]--;
            }

    for (int x = 0; x < BOARD_HEIGHT; x++)
        for (int y = 0; y < BOARD_WIDTH; y++)
            if (realBoard[x][y] != 9)
            {
                realBoard[x][y] = 9;
                for (int dx = -1; dx <= 1; dx++)
                    for (int dy = -1; dy <= 1; dy++)
                        if ((dx || dy) && isValid(x+dx, y+dy) && realBoard[x+dx][y+dy] != 9)
                            realBoard[x+dx][y+dy]++;
                break;
            }
    return;
}

bool isValid(int row, int col)
{
    return (row >= 0 && col >= 0 && row < BOARD_HEIGHT && col < BOARD_WIDTH);
}
