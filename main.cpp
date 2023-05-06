#include "Texture.h"
#include "Constants.h"
#include "Variables.h"
#include "Functions.h"

using namespace std;

int main(int argc, char* args[])
{
    //Start up SDL and create window
    if(!init())
    {
        cout << "Failed to initialize!\n";
    }
    else
    {
        //Load media
        if(!loadMedia())
        {
            cout << "Failed to load media!\n";
        }
        else
        {
            if (!loadMenuMedia())
            {
                cout << "Failed to load media!\n";
            }
            else
            {
                if (renderMenu())
                {
                    if (renderDifficulty())
                    {
                            //While application is running
                            bool quit = false;
                            while(!quit)
                            {
                                srand(time(NULL));
                                placeMines();

                                //While game is not over yet
                                while (!gameOver && !quit && !isWinning)
                                {
                                    quit = gameHandle();
                                    renderGame();
                                }

                                //Check play again flag
                                playAgainManager(quit);
                            }
                    }
                }
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}

