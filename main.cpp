#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

template <class T>
void checkError(T);
bool mouseOver(int mx, int my, SDL_Rect r);
int turn = 0;
string checkWinrar(int* a);

int main(int argc, char* argv[])
{
	SDL_Event e;
	SDL_Window *win = SDL_CreateWindow("TicTacToe", 100, 100, 320, 400, SDL_WINDOW_SHOWN);
	checkError(win);
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	checkError(ren);
	
	//Background
	SDL_Surface *img = SDL_LoadBMP("res/bg.bmp");
	checkError(img);
	SDL_Rect bgData;
	bgData.x = 0;
	bgData.y = 3;
	bgData.w = img->w;
	bgData.h = img->h;
	SDL_Texture *bgTexture = SDL_CreateTextureFromSurface(ren, img);
	SDL_FreeSurface(img);
	
	//Empty Field
	img = SDL_LoadBMP("res/empty.bmp");
	checkError(img);
	SDL_Rect efData;
	efData.x = 0;
	efData.y = 13;
	efData.w = img->w;
	efData.h = img->h;
	SDL_Texture *efTexture = SDL_CreateTextureFromSurface(ren, img);
	SDL_FreeSurface(img);
	
	//Mouseover Field
	img = SDL_LoadBMP("res/collision.bmp");
	checkError(img);
	SDL_Texture *moTexture = SDL_CreateTextureFromSurface(ren, img);
	SDL_FreeSurface(img);
	
	//X Field
	img = SDL_LoadBMP("res/x.bmp");
	checkError(img);
	SDL_Texture *xTexture = SDL_CreateTextureFromSurface(ren, img);
	SDL_FreeSurface(img);
	
	//O Field
	img = SDL_LoadBMP("res/o.bmp");
	checkError(img);
	SDL_Texture *oTexture = SDL_CreateTextureFromSurface(ren, img);
	SDL_FreeSurface(img);
	
	//Test shit
	int fArray[9] = {	0, 0, 0,
						0, 0, 0,
						0, 0, 0};
	
	bool is_running = true;
	while(is_running)
	{
		while(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
				case SDL_QUIT:
					is_running = false;
				break;
				default:;
			}
		}
		SDL_RenderClear(ren);
		
		//Draw background
		SDL_RenderCopy(ren, bgTexture, nullptr, &bgData);
		//Draw fields
		for(int i = 0; i < 9; i++)
		{
			efData.x += 15;
			
			if(fArray[i] == 0)
			{
				SDL_RenderCopy(ren, efTexture, nullptr, &efData);
			}
			if(mouseOver(e.motion.x, e.motion.y, efData))
			{
				SDL_RenderCopy(ren, moTexture, nullptr, &efData);
				if(e.button.button == SDL_BUTTON_LEFT)
				{
					if(fArray[i] == 0)
					{
						if(turn == 0)
						{
							fArray[i] = 1;
							turn = 1;
						}
						else if(turn == 1)
						{
							fArray[i] = 2;
							turn = 0;
						}
					}
					else
					{
						cout << "The winrar is: " << checkWinrar(fArray) << "\n";
					}
				}
			}
			if(fArray[i] == 1)
			{
				SDL_RenderCopy(ren, xTexture, nullptr, &efData);
			}
			if(fArray[i] == 2)
			{
				SDL_RenderCopy(ren, oTexture, nullptr, &efData);
			}
			efData.x += efData.w+3;
			if(i == 2 || i == 5)
			{
				efData.y += efData.h + 15;
				efData.x = 0;
			}			
		}
		efData.x = 0;
		efData.y = 13;
		/*for(int i = 0; i <= 9; i++) //for loop to shot shit ionno how to explain
		{
			efData.x += 15; //this is first fields starting position then i just shot it thru loop by using MATH
			if(mouseOver(e.motion.x, e.motion.y, efData))
			{
				SDL_RenderCopy(ren, moTexture, nullptr, &efData);
				if(e.type == SDL_MOUSEBUTTONDOWN)
				{
					if(e.button.button == SDL_BUTTON_LEFT)
					{
						if(turn == 0)
						{
							SDL_RenderCopy(ren, xTexture, nullptr, &efData);
							turn = 1;
						}
						else if(turn == 1)
						{
							SDL_RenderCopy(ren, oTexture, nullptr, &efData);
							turn = 0;
						}
					}
				}
			}
			else
			{
				SDL_RenderCopy(ren, efTexture, nullptr, &efData);
			}
			efData.x += efData.w+3;
			if(i == 3 || i == 6)
			{
				efData.y += efData.h + 15;
				efData.x = 0;
			}
		}
		efData.x = 0;
		efData.y = 13;*/
		
		
		SDL_RenderPresent(ren);
		SDL_Delay(16);
	}
	
	return 0;
}

template <class T>
void checkError(T a)
{
	if(a == nullptr)
	{
		cout << SDL_GetError() << endl;
		exit(1);
	}
}

string checkWinrar(int* a)
{
	return "";
}

bool mouseOver(int mx, int my, SDL_Rect r)
{
	if(mx > r.x && mx < r.x+r.w && my > r.y && my < r.y+r.h)
	{
		return true;
	} 
	return false;
}
