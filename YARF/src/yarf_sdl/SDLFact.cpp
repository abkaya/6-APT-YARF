/*
 * SDLFact.cpp
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#include <iostream>
#include "SDLFact.h"
#include "SDLFrog.h"
#include "SDLVehicle.h"
#include "SDLTerrain.h"

namespace yarf_sdl
{
SDLFact::SDLFact() :
		FPS(60)
{
	/*Initialise TTF*/
	//Initialise SDL_ttf -- and only initialise it once.
	//SDL doesn't have to be initialised yet
	if (!TTF_WasInit())
	{
		if (TTF_Init() == -1)
		{
			std::cout << "SDL_ttf could not initialize! SDL_ttf Error: "
					<< TTF_GetError() << std::endl;

		}
	}

	//Initialisation of the window happens here
	if (Init("YARF | Yet Another Reckless Frog", SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE))
	{
		bRunning = true;
	}
	//Then you can initialize the entities -- so make sure to check Fact::IsRunning()
	//Before calling Game::InitEntities()

	//Then we render the window
	HandleVisEvents();
	RenderClear();
	RenderPresent();
	//m_direction = 0; do this as well in Game.cpp
}

bool SDLFact::Init(const char * title, int xpos, int ypos, int height,
		int width, int flags)
{
	// initialise SDL -- including SDL_INIT_... HAPTIC,AUDIO,VIDEO,TIMER,JOYSTICK
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		// if succeeded create our window
		pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);

		// if the window creation succeeded create our renderer
		if (pWindow != 0)
		{
			// https://wiki.libsdl.org/SDL_CreateRenderer
			pRenderer = SDL_CreateRenderer(pWindow, -1,
					SDL_RENDERER_ACCELERATED);

			// renderer init success
			if (pRenderer != 0)
			{
				SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
				// Call InitTextures only after the Renderer is created
				InitTextures();
				// Border for the frog = game window (WIDTH & HEIGHT)
				windowRect.x = 0;
				windowRect.y = 0;
				windowRect.w = WIDTH;
				windowRect.h = HEIGHT;
				//The Terrain is in essence in its entirety independent from the Game,
				//so we'll be creating it in here.
				TerrainF = CreateTerrain();
			}
			else
			{
				// renderer init fail
				return false;
			}
		}
	}
	else
	{
		return false;    // sdl could not initialize
	}
	return true;
}

// Create the Textures needed. Only call this function after the Renderer is created in the Init() function
void SDLFact::InitTextures()
{
	pTempSurface = IMG_Load(".\\gamesprite.png");
	pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	pTempSurface = IMG_Load(".\\yarficon.png");
	SDL_SetWindowIcon(pWindow, pTempSurface);
	SDL_FreeSurface(pTempSurface);

	//Create text textures ("health: ammo: score:" and 0,1,2,3,4,5,6,7,8,9)
	font = TTF_OpenFont(".\\sans.ttf", 23); //this opens a font style and sets a size
	orange.r = 255;
	orange.g = 165;
	orange.b = 0;
	orange.a = 255;

	green.r = 54;
	green.g = 196;
	green.b = 35;
	green.a = 255;

	for (int i = 0; i < 11; i++)
	{
		if (i == 10)
			fontColor = orange;
		else
			fontColor = green;
		textSurface = TTF_RenderText_Solid(font, sMessage.c_str(), fontColor);
		if (textSurface == NULL)
		{
			std::cout << "Unable to render text surface! SDL_ttf Error: "
					<< TTF_GetError() << std::endl;
		}
		else
		{
			//Create texture from surface pixels
			textTexture = SDL_CreateTextureFromSurface(pRenderer, textSurface);
			if (textTexture == 0)
			{
				std::cout
						<< "Unable to create text from rendered surface! SDL_ttf Error: "
						<< TTF_GetError() << std::endl;
			}
			else
			{
				textRect.w = textSurface->w * widthScaleFactor;
				textRect.h = textSurface->h;
			}

			//Get rid of old surface
			SDL_FreeSurface(textSurface);
		}
	}
}

yarf::Frog* SDLFact::CreateFrog(list<yarf::Bullet *> &bullet_list)
{
	return new yarf_sdl::SDLFrog(pRenderer, pTexture, windowRect,
			widthScaleFactor, heightScaleFactor, bullet_list);
}

yarf::Vehicle* SDLFact::CreateVehicle(bool init_spawn, int lane,
		int ordinalNumber)
{
	return (new SDLVehicle(pRenderer, pTexture, init_spawn, lane, ordinalNumber,
			(rand() % 5), widthScaleFactor, heightScaleFactor));
}

Terrain* SDLFact::CreateTerrain()
{
	return new SDLTerrain(pRenderer, pTexture, WIDTH, HEIGHT - scorebarHeight,
			heightScaleFactor, widthScaleFactor);
}

bool SDLFact::IsRunning()
{
	return bRunning;
}

int SDLFact::GetTicks()
{
	return SDL_GetTicks();
}

void SDLFact::Delay(int delay_time)
{
	SDL_Delay(delay_time);
}

void SDLFact::HandleVisEvents()
{
	HandleEvents();
}

Rect SDLFact::GetFrogStates()
{
	return FrogStates;
}

void SDLFact::RenderClear()
{
	// clear the window to the RenderDrawColor set in the Init function ^
	SDL_RenderClear(pRenderer);
	TerrainF->Vis();
}

void SDLFact::RenderPresent()
{
	// show the window
	SDL_RenderPresent(pRenderer);
}

void SDLFact::HandleEvents()
{
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		// If user presses the X button, the render loop breaks
		case SDL_QUIT:
			bRunning = false;
			break;
		case SDL_KEYDOWN:
			switch ((int) event.key.keysym.sym)
			{
			case 122:    // z
				FrogStates.x = 0;	//x = frog's direction
				FrogStates.y = 1;   //y = frog state leaping

				break;
			case 100:    // d
				FrogStates.x = 1;
				FrogStates.y = 1;
				break;
			case 115:    // s
				FrogStates.x = 2;
				FrogStates.y = 1;
				break;
			case 113:    // q
				FrogStates.x = 3;
				FrogStates.y = 1;
				break;
			case 32: //space
				FrogStates.w = 1;		//.w (CreateBullet) -> 1: red bullet
				break;
			case 101: //e
				FrogStates.w = 4;		//.w (CreateBullet) -> 4: blue bullet
				break;
			case 114: //r
				FrogStates.w = 5;		//.w (CreateBullet) -> 5: red bullet
				break;
			default:
				break;
			}
			break;
		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				WIDTH = event.window.data1;
				HEIGHT = event.window.data2;
				Resize();
				break;
			default:
				break;
			}
			break;
		default:
			//cout << (int) m_event.key.keysym.sym << endl; // to discover the integer value of an event
			FrogStates.x = -1;
			FrogStates.w = 0; //don't create a bullet
			break;
		}
	}
	if (event.type != SDL_KEYDOWN)
	{
		FrogStates.y = 0;
	}
}

void SDLFact::Resize()
{
	SDL_SetWindowSize(pWindow, WIDTH, HEIGHT);
	//changing the scale factors here suffices.
	widthScaleFactor = static_cast<float>(WIDTH) / 640;
	heightScaleFactor = static_cast<float>(HEIGHT - scorebarHeight) / 480;
	delete (TerrainF);
	TerrainF = CreateTerrain();

	//update widthscale dependent values
	healthDstX=90*widthScaleFactor;
	ammoDstX=295*widthScaleFactor;
	scoreDstX=490*widthScaleFactor;
}

void SDLFact::RenderText()
{
	//
	textRect.x = 10 * widthScaleFactor;
	textRect.y = HEIGHT - 30;
	textRect.w = 480 * widthScaleFactor;
	textRect.h = scorebarHeight;

	SDL_RenderCopy(pRenderer, textTexture, NULL, &textRect);

	//renderScores()
	//this takes in 3 integers: values of
}

void SDLFact::RenderGameStats(int health, int ammo, int score)
{
	/*Workflow to make this happen
	 * 1. Find the lengths of the numbers
	 * 2. Place these numbers in an array and use the lengths to
	 * 	  place zeroes in the higher digits where necessary
	 * 3. With the numbers placed at 17pixels from each other
	 *    on the sprite sheet, it's convenient to scroll through the
	 *    number we want, by multiplying the x-coord with the numWidth(=17)
	 * 4. Once both the satisfactory SDLRect (source and dest) are achieved,
	 *
	 * 	  RENDER!
	 *
	 **/
	//get the number of digits of the numbers to display
	healthLength = GetNumberOfDigits(health);
	ammoLength = GetNumberOfDigits(ammo);
	scoreLength = GetNumberOfDigits(score);
	tempHealth=health;
	tempAmmo=ammo;
	tempScore=score;

	//place them in the arrays. (e.g. value 123 becomes {0,0,1,2,3}
	//health array
	for (int j = 4; j >= 0; j--)
	{
		if(healthLength>j+5)
			healthArr[j]=0;
		else
			healthArr[j] = tempHealth % 10;
		tempHealth /= 10;
	}
	//ammo array
	for (int j = 4; j >= 0; j--)
	{
		if(ammoLength>j+5)
			ammoArr[j]=0;
		else
			ammoArr[j] = tempAmmo % 10;
		tempAmmo /= 10;
	}
	//score array
	for (int j = 4; j >= 0; j--)
	{
		if(scoreLength>j+5)
			scoreArr[j]=0;
		else
			scoreArr[j] = tempScore % 10;
		tempScore /= 10;
	}

	RenderDigits(healthArr,healthDstX);
	RenderDigits(ammoArr,ammoDstX);
	RenderDigits(scoreArr,scoreDstX);
}

void SDLFact::RenderDigits(int numArray[], int startX){
	for(int i=0;i<5;i++){
		numSrcRect.x=numWidth*numArray[i];
		numSrcRect.y=numSrcY;
		numSrcRect.w=numWidth;
		numSrcRect.h=numHeight;
		numDstRect.x=startX+numWidth*widthScaleFactor*i;
		numDstRect.y=HEIGHT-30;
		numDstRect.w=numWidth*widthScaleFactor;
		numDstRect.h=numHeight;

		SDL_RenderCopy(pRenderer,pTexture,&numSrcRect,&numDstRect);
	}
}

int SDLFact::GetNumberOfDigits(int number)
{
	int length = 0;
	do
	{
		++length;
		number /= 10;
	} while (number);
	return length;
}

void SDLFact::Stop()
{
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	SDL_Quit();
}

SDLFact::~SDLFact()
{
}
}

