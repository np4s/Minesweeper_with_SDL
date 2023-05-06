#include <ctime>
#include "Buttons.h"
#include "Functions.h"

using namespace std;

LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;
}

void LButton::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void reveal(int row, int col)
{
    if (curBoard[row][col] == 10 || curBoard[row][col] == 11)
    {
        if (curBoard[row][col] == 11)
            return;

        curBoard[row][col] = realBoard[row][col];
        countTileLeft--;
        if (curBoard[row][col] == 0)
        {
            for (int i = -1; i <= 1; i++)
                for (int j = -1; j <= 1; j++)
                if ((i || j) && isValid(row+i, col+j))
                    reveal(row+i, col+j);
        }
    }

    return;
}

void LButton::handleEvent(SDL_Event* e)
{
	//If mouse event happened
	if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

        int i = (y - DISTANCE_BETWEEN)/TILE_SIZE;
        int j = (x - DISTANCE_BETWEEN)/TILE_SIZE;

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if(x < mPosition.x)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if(x > mPosition.x + TILE_SIZE)
		{
			inside = false;
		}
		//Mouse above the button
		else if(y < mPosition.y)
		{
			inside = false;
		}
		//Mouse below the button
		else if(y > mPosition.y + TILE_SIZE)
		{
			inside = false;
		}

		//Mouse is inside button
		if (inside)
		{
			if (e->type == SDL_MOUSEBUTTONDOWN)
            {
                //Play the sound effect
				Mix_PlayChannel(-1, click, 0);

				//Set mouse clicked
				switch (e->button.button)
				{
                    case SDL_BUTTON_LEFT:
                    {
                        if (curBoard[i][j] == 11)
                            break;

                        reveal(i, j);
                        if (realBoard[i][j] == 9)
                        {
                            gameOver = true;
                        }

                        break;
                    }
                    case SDL_BUTTON_RIGHT:
                    {
                        if (curBoard[i][j] >= 10)
                        {
                            if (curBoard[i][j] == 10)
                            {
                                curBoard[i][j] = 11;
                                countMineLeft--;
                            }
                            else
                            {
                                curBoard[i][j] = 10;
                                countMineLeft++;
                            }
                        }
                        break;
                    }
				}
            }
		}
	}
}

void LButton::render(int i, int j)
{
	//Show current button sprite
	gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y, &gSpriteClips[curBoard[i][j]]);
}

