#include "Texture.h"
#include "Constants.h"
#include "Variables.h"
#include "Functions.h"
#include "Timer.h"

using namespace std;

//Buttons
vector< vector<LButton> > gButtons (30, vector<LButton>(30));
LButton goBack;

//Timer
LTimer timer;

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
        if(!gTextTexturePlay.loadFromRenderedText("PLAY", textColor))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }

        if(!gTextTextureExit.loadFromRenderedText("EXIT", textColor))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }

        if(!gTextTextureEasy.loadFromRenderedText("EASY", textColor))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }

        if(!gTextTextureMedium.loadFromRenderedText("MEDIUM", textColor))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }

        if(!gTextTextureHard.loadFromRenderedText("HARD", textColor))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }

        if(!gTextTextureChallenge.loadFromRenderedText("CHALLENGE", textColor))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }

        textColor = { 0, 0, 0 };
        if(!gTextTexturePlayColor.loadFromRenderedText("PLAY", textColor))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }

        if(!gTextTextureExitColor.loadFromRenderedText("EXIT", textColor))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }

        if(!gTextTextureHelp.loadFromRenderedText("HELP", textColor))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }

        if(!gTextTextureEasyColor.loadFromRenderedText("EASY", textColor))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }

        if(!gTextTextureMediumColor.loadFromRenderedText("MEDIUM", textColor))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }

        if(!gTextTextureHardColor.loadFromRenderedText("HARD", textColor))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }

        textColor = { 139, 0, 0 };
        if(!gTextTextureChallengeColor.loadFromRenderedText("CHALLENGE", textColor))
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

    if (!helpTheme.loadFromFile("Image/helpBackground.png"))
    {
        cout << "Failed to load background texture!\n";
        success = false;
    }

    return success;
}

void close()
{
    //Free image textures
    gButtonSpriteSheetTexture.free();
    gDigitSpriteSheetTexture.free();
    menuTheme.free();
    helpTheme.free();
    difficultyTheme.free();
    easyTable.free();
    mediumTable.free();
    hardTable.free();
    winFace.free();
    loseFace.free();
    backIcon.free();

    //Free text textures
    gTextTexturePlay.free();
    gTextTextureExit.free();
    gTextTextureHelp.free();
    gTextTexturePlayColor.free();
    gTextTextureExitColor.free();
    gTextTextureEasy.free();
    gTextTextureMedium.free();
    gTextTextureHard.free();
    gTextTextureEasyColor.free();
    gTextTextureMediumColor.free();
    gTextTextureHardColor.free();
    gTextTextureChallenge.free();
    gTextTextureChallengeColor.free();

    //Free global font
    TTF_CloseFont(gFont);
    gFont = NULL;

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
    gTextTexturePlay.render( ( SCREEN_WIDTH - gTextTexturePlay.getWidth() ) / 2, 325 );
    gTextTextureExit.render( ( SCREEN_WIDTH - gTextTextureExit.getWidth() ) / 2, 400 );
    gTextTextureHelp.render(500, 550);

    SDL_RenderPresent(gRenderer);
}

bool renderMenu()
{
    //Returns Play(true) or Exit(false)
    bool inPlay = false;
    bool inExit = false;
    bool inHelp = false;
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

                if (x > ( SCREEN_WIDTH - gTextTexturePlay.getWidth() ) / 2 && x < ( SCREEN_WIDTH - gTextTexturePlay.getWidth() ) / 2 + gTextTexturePlay.getWidth() && y > 325 && y < 325 + gTextTexturePlay.getHeight())
                {
                    inPlay = true;
                }
                else inPlay = false;

                if (x > ( SCREEN_WIDTH - gTextTextureExit.getWidth() ) / 2 && x < ( SCREEN_WIDTH - gTextTextureExit.getWidth() ) / 2 + gTextTextureExit.getWidth() && y > 400 && y < 400 + gTextTextureExit.getHeight())
                {
                    inExit = true;
                }
                else inExit = false;

                if (x > 500 && x < 500 + gTextTextureHelp.getWidth() && y > 550 && y < 550 + gTextTextureHelp.getHeight())
                {
                    inHelp = true;
                }
                else inHelp = false;

                if (e.type == SDL_MOUSEMOTION)
                {
                    if (inPlay == true)
                    {
                        gTextTexturePlayColor.render( ( SCREEN_WIDTH - gTextTexturePlay.getWidth() ) / 2, 325 );
                    }
                    else
                        gTextTexturePlay.render( ( SCREEN_WIDTH - gTextTexturePlay.getWidth() ) / 2, 325 );

                    if (inExit == true)
                    {
                        gTextTextureExitColor.render( ( SCREEN_WIDTH - gTextTextureExit.getWidth() ) / 2, 400 );
                    }
                    else
                        gTextTextureExit.render( ( SCREEN_WIDTH - gTextTextureExit.getWidth() ) / 2, 400 );
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

                        if (inHelp == true)
                            if (!createHelp())
                                return false;
                    }
                }
            }

            SDL_RenderPresent(gRenderer);
        }
    }
}

///Help screen
bool createHelp()
{
    SDL_RenderClear(gRenderer);

    helpTheme.render(0, 0);
    backIcon.render(40, 35);

    SDL_RenderPresent(gRenderer);

    SDL_Event e;

    while (!backMenu)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
            {
                return false;
            }
            goBack.handleBackEvent(&e);
        }
    }

    createMenu();
    backMenu = false;
    return true;
}

///Selecting Difficulty
void createDifficulty()
{
    SDL_RenderClear(gRenderer);

    difficultyTheme.render(0, 0);
    gTextTextureEasy.render(260, 200);
    gTextTextureMedium.render(240, 275);
    gTextTextureHard.render(260, 350);
    gTextTextureChallenge.render(220, 425);
    backIcon.render(40, 35);

    SDL_RenderPresent(gRenderer);
}

bool renderDifficulty()
{
    challengeMode = false;

    bool quit = false;
    bool inEasy = false;
    bool inMedium = false;
    bool inHard = false;
    bool inChallenge = false;
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

            goBack.handleBackEvent(&e);
            if (backMenu == true)
                    return true;

            if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEMOTION)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);

                if (x > 260 && x < 260 + gTextTextureEasy.getWidth() && y > 200 && y < 200 + gTextTextureEasy.getHeight())
                {
                    inEasy = true;
                }
                else inEasy = false;

                if (x > 240 && x < 240 + gTextTextureMedium.getWidth() && y > 275 && y < 275 + gTextTextureMedium.getHeight())
                {
                    inMedium = true;
                }
                else inMedium = false;

                if (x > 260 && x < 260 + gTextTextureHard.getWidth() && y > 350 && y < 350 + gTextTextureHard.getHeight())
                {
                    inHard = true;
                }
                else inHard = false;

                if (x > 220 && x < 220 + gTextTextureChallenge.getWidth() && y > 425 && y < 425 + gTextTextureChallenge.getHeight())
                {
                    inChallenge = true;
                }
                else inChallenge = false;

                if (e.type == SDL_MOUSEMOTION)
                {
                    if (inEasy == true)
                    {
                        gTextTextureEasyColor.render(260, 200);
                    }
                    else
                        gTextTextureEasy.render(260, 200);

                    if (inMedium == true)
                    {
                        gTextTextureMediumColor.render(240, 275);
                    }
                    else
                        gTextTextureMedium.render(240, 275);

                    if (inHard == true)
                    {
                        gTextTextureHardColor.render(260, 350);
                    }
                    else
                        gTextTextureHard.render(260, 350);

                    if (challengeMode == false)
                    {
                        if (inChallenge == true)
                        {
                            gTextTextureChallengeColor.render(220, 425);
                        }
                        else
                            gTextTextureChallenge.render(220, 425);
                    }

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

                        if (inChallenge == true)
                        {
                            challengeMode ^= 1;
                            if (challengeMode == true)
                                gTextTextureChallengeColor.render(220, 425);
                            else
                                gTextTextureChallenge.render(220, 425);
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
        TIME_LIMIT = 15;

        break;
    }

    case MEDIUM:
    {
        SCREEN_WIDTH = 488;
        SCREEN_HEIGHT = 580;
        MINES = 40;
        BOARD_WIDTH = 16;
        BOARD_HEIGHT = 16;
        TIME_LIMIT = 60;

        break;
    }

    case HARD:
    {
        SCREEN_WIDTH = 880;
        SCREEN_HEIGHT = 582;
        MINES = 99;
        BOARD_WIDTH = 30;
        BOARD_HEIGHT = 16;
        TIME_LIMIT = 360;

        break;
    }
    }

    DISTANCE_W = (SCREEN_WIDTH - BOARD_WIDTH * TILE_SIZE) / 2;
    DISTANCE_H = (SCREEN_HEIGHT - BOARD_HEIGHT * TILE_SIZE) / 2 + 45;
    countMineLeft = MINES;
    countTileLeft = BOARD_WIDTH * BOARD_HEIGHT;

    SDL_SetWindowSize(gWindow, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void renderGame()
{
    //Clear screen
    SDL_RenderClear(gRenderer);
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    //Render background
    switch (DIFFICULTY)
    {
    case EASY:
    {
        easyTable.render(0,0);
        break;
    }

    case MEDIUM:
    {
        mediumTable.render(0,0);
        break;
    }

    case HARD:
    {
        hardTable.render(0,0);
        break;
    }
    }

    //Set buttons' positions
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            gButtons[i][j].setPosition(j * TILE_SIZE + DISTANCE_W, i * TILE_SIZE + DISTANCE_H);
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

    //Render timer
    timeManager();

    //Render mine/flag left
    mineManager();

    //Perform win/lose flag
    flagManager();

    //Update screen
    SDL_RenderPresent(gRenderer);
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

        //User requests back to menu
        goBack.handleBackEvent(&e);

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
    return (countTileLeft == MINES);
}

void mineManager()
{
    //Render text
    if (!gameOver && !isWinning)
    {
        if (countMineLeft < 10)
        {
            gDigitSpriteSheetTexture.render(SCREEN_WIDTH / 2 - 40, 32, &gDigitSprites[0]);
            gDigitSpriteSheetTexture.render(SCREEN_WIDTH / 2 - 40 + TILE_SIZE, 32, &gDigitSprites[max(0, countMineLeft)]);
        }
        else
        {
            gDigitSpriteSheetTexture.render(SCREEN_WIDTH / 2 - 40, 32, &gDigitSprites[countMineLeft/10]);
            gDigitSpriteSheetTexture.render(SCREEN_WIDTH / 2 - 40 + TILE_SIZE, 32, &gDigitSprites[countMineLeft%10]);
        }
    }

}

void flagManager()
{
    //Check if win
    if (isWinning && !gameOver)
    {
        timer.pause();

        //Render win face
        winFace.render((SCREEN_WIDTH - winFace.getWidth()) / 2, 32);
    }

    //Check if lose
    if (gameOver)
    {
        timer.pause();

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

void timeManager()
{
    int currentTime = timer.getTicks() / 1000;

    if (challengeMode == true && currentTime == TIME_LIMIT)
        gameOver = true;

    if (challengeMode == true)
        currentTime = TIME_LIMIT - currentTime;

    for (int i = 1; i < 4; i++)
    {
        int x = currentTime % 10;
        currentTime /= 10;
        gDigitSpriteSheetTexture.render(SCREEN_WIDTH - 24 - TILE_SIZE*i, 32, &gDigitSprites[x]);
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

                    //Recreate board
                    srand(time(NULL));
                    initGame();

                    //Recreate flag
                    gameOver = false;
                    isWinning = false;
                    quitGame = false;
                }
            }
        }

        if (e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT) quitGame = true;

        goBack.handleBackEvent(&e);
        if (backMenu == true)
        {
            //Recreate flag
            gameOver = false;
            isWinning = false;
            quitGame = false;
        }
    }
}

void initGame()
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

//    //Cheater
//    for (int i = 0; i < BOARD_HEIGHT; i++)
//    {
//        for (int j = 0; j < BOARD_WIDTH; j++)
//            cout << realBoard[i][j];
//        cout << endl;
//    }

    timer.start();
    firstMove = true;
}

void changeMine(int row, int col)
{
    int adjMine = 0;
    realBoard[row][col] = 0;

    //First click always 0 tile
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (isValid(row+i, col+j))
            {
                if (realBoard[row+i][col+j] == 9)
                {
                    adjMine++;
                    realBoard[row+i][col+j] = 0;
                }
            }

    //Placing mines
    for (int x = 0; x < BOARD_HEIGHT && adjMine > 0; x++)
        for (int y = 0; y < BOARD_WIDTH && adjMine > 0; y++)
            if (realBoard[x][y] != 9 && (abs(row-x) + abs(col-y) > 2))
            {
                realBoard[x][y] = 9;
                adjMine--;
            }

    //Recalculate adjacent mines
    for (int x = 0; x < BOARD_HEIGHT; x++)
        for (int y = 0; y < BOARD_WIDTH; y++)
            if (realBoard[x][y] != 9)
            {
                realBoard[x][y] = 0;

                for (int dx = -1; dx <= 1; dx++)
                    for (int dy = -1; dy <= 1; dy++)
                        if ((dx || dy) && isValid(x+dx, y+dy) && realBoard[x+dx][y+dy] == 9)
                            realBoard[x][y]++;

            }
}

bool isValid(int row, int col)
{
    return (row >= 0 && col >= 0 && row < BOARD_HEIGHT && col < BOARD_WIDTH);
}
