#include "Texture.h"
#include "Constants.h"
#include "Variables.h"
#include "Functions.h"
#include "Functions.h"

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

    //Open the font
    gFont = TTF_OpenFont("Font/DTM-Sans.ttf", 40);
    if(gFont == NULL)
    {
        cout << "Failed to load DTM-Sans font! SDL_ttf Error: " << TTF_GetError() << endl;
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 140, 140, 140 };
        if(!gTextTextureW.loadFromRenderedText("YOU WIN :D", textColor))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }

        if(!gTextTextureL.loadFromRenderedText("YOU LOSE :(", textColor))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }

        if(!gPlayAgainTexture.loadFromRenderedText("Press R to play again!", textColor))
        {
            cout << "Failed to render text texture!\n";
            success = false;
        }

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

        textColor = { 255, 0, 0 };
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
    }

    //Load scene
    if (!gBackgroundTexture.loadFromFile("Image/Background.png"))
    {
        cout << "Failed to load background texture!\n";
        success = false;
    }

    //Load sprites
    if(!gButtonSpriteSheetTexture.loadFromFile("Image/Tiles.png"))
    {
        cout << "Failed to load sprites texture!\n";
        success = false;
    }
    else
    {
        //Set sprites
        for(int i = 0; i < BUTTON_SPRITE_TOTAL; i++)
        {
            gSpriteClips[i].x = i * 32;
            gSpriteClips[i].y = 0;
            gSpriteClips[i].w = TILE_SIZE;
            gSpriteClips[i].h = TILE_SIZE;
        }
        //Set buttons position
        for (int i = 0; i < SIDE; i++)
        {
            for (int j = 0; j < SIDE; j++)
            {
                gButtons[i][j].setPosition(j * TILE_SIZE + DISTANCE_BETWEEN, i * TILE_SIZE + DISTANCE_BETWEEN);
            }
        }
    }

    //Load tables
	if (!easyTable.loadFromFile("Image/easy.png"))
	{
        cout << "Failed to load easy board" << endl;
        success = false;
	}

    //Load sound effects
    click = Mix_LoadWAV("Sounds/click.wav");
    if(click == NULL)
    {
        cout << "Failed to load click sound effect! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }

    return success;
}

//bool loadMenuMedia()
//{
//    bool success = true;
//
//    //Menu background
//
//}

void close()
{
    //Free loaded images
    gButtonSpriteSheetTexture.free();
    gMineLeftTexture.free();
    gBackgroundTexture.free();
    gTextTextureW.free();
    gTextTextureL.free();

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

void renderGame()
{
    //Clear screen
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    //Render background
    gBackgroundTexture.render(0, 0);

    //Render buttons
    for(int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            gButtons[i][j].render(i, j);
        }
    }
    //Render mine/flag left
    mineManager();

    //Perform win/lose flag
    flagManager();

    //Update screen
    SDL_RenderPresent(gRenderer);

    return;
}

///Menu Functions
void createMenu()
{
    menuTheme.render(0, 0);
    gPlay.render(250, 400);
    gExit.render(450, 400);
    SDL_RenderPresent(gRenderer);
    return;
}

bool showMenu()
{
    //Returns Play(false) or Exit(true)
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
                return true;
            }

            if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEMOTION)
            {
                int x, y;
				SDL_GetMouseState(&x, &y);

                if (x > 300 && x < 300 + gPlay.getWidth() && y > 400 && y < 400 + gPlay.getHeight())
                {
                    inPlay = true;
                }
                else inPlay = false;

                if (x > 450 && x < 450 + gExit.getWidth() && y > 400 && y < 400 + gExit.getWidth())
                {
                    inExit = true;
                }
                else inExit = false;

                if (e.type == SDL_MOUSEMOTION)
                {
                    if (inPlay == true)
                    {
                        gPlayColor.render(250, 400);
                    }
                    else
                        gPlay.render(250, 400);

                    if (inExit == true)
                    {
                        gExitColor.render(450, 400);
                    }
                    else
                        gExit.render(450, 400);
                }

                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        if (inPlay == true)
                        {
                            return false;
                        }

                        if (inExit == true)
                        {
                            return true;
                        }
                    }
                }
            }

            SDL_RenderPresent(gRenderer);
        }
    }

    return false;
}

///Game Functions
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
        for (int i = 0; i < SIDE; i++)
        {
            for (int j = 0; j < SIDE; j++)
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
        //Set text color
        SDL_Color textColor = { 140, 140, 140, 255 };

        //Erase the buffer
        mineLeft.str ("");
        mineLeft << "Mine left: " << countMineLeft;
        if(!gMineLeftTexture.loadFromRenderedText(mineLeft.str().c_str(), textColor))
        {
            cout << "Unable to render mine left texture!\n";
        }

        //Render text
        gMineLeftTexture.render((SCREEN_WIDTH - gMineLeftTexture.getWidth()) / 2, 0);
    }
}

void flagManager()
{
    //Check if win
    if (isWinning && !gameOver)
    {
        //Render win text
        gTextTextureW.render((SCREEN_WIDTH - gTextTextureW.getWidth()) / 2, 0);

        //Render playAgain
        gPlayAgainTexture.render(( SCREEN_WIDTH - gPlayAgainTexture.getWidth() ) / 2, SCREEN_HEIGHT - gPlayAgainTexture.getHeight() );
    }

    //Check if lose
    if (gameOver)
    {
        //Render lose text
        gTextTextureL.render((SCREEN_WIDTH - gTextTextureL.getWidth()) / 2, 0);

        for(int i = 0; i < SIDE; i++)
        {
            for (int j = 0; j < SIDE; j++)
            {
                curBoard[i][j] = realBoard[i][j];
                gButtons[i][j].render(i, j);
            }
        }
        //Render play again
        gPlayAgainTexture.render( ( SCREEN_WIDTH - gPlayAgainTexture.getWidth() ) / 2, SCREEN_HEIGHT - gPlayAgainTexture.getHeight() );
    }
}

void playAgainManager(bool &quitGame)
{
    //Event handler
    SDL_Event e;

    //Handle events on queue
    while(SDL_PollEvent(&e) != 0)
    {
        //User requests play again
        if(e.key.keysym.sym == SDLK_r)
        {
            //Stop the music
            Mix_HaltMusic();

            //Recreate constants
            countMineLeft = MINES;
            countTileLeft = SIDE * SIDE;

            //Recreate flag
            gameOver = false;
            isWinning = false;
            quitGame = false;
        }
        else if (e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT) quitGame = true;
    }
}

void placeMines()
{
    //Initialize boards
    int mine = 0;
    for (int i = 0; i < SIDE; i++)
        for (int j = 0; j < SIDE; j++)
        {
            curBoard[i][j] = 10;
            realBoard[i][j] = 0;
        }

    //Placing mines
    for (int i = 0; i < MINES;)
    {
        int random = rand() % (SIDE*SIDE);
        int x = random / SIDE;
        int y = random % SIDE;

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

    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
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

    for (int x = 0; x < SIDE; x++)
        for (int y = 0; y < SIDE; y++)
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
