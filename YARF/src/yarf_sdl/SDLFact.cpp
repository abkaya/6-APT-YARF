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
	pTempSurface = IMG_Load(".\\frogsrusicon.png");
	SDL_SetWindowIcon(pWindow, pTempSurface);
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
	return new SDLTerrain(pRenderer, pTexture, WIDTH, HEIGHT, heightScaleFactor,
			widthScaleFactor);
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

void SDLFact::RenderPresent(){
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
	heightScaleFactor = static_cast<float>(HEIGHT) / 480;
	delete (TerrainF);
	TerrainF = CreateTerrain();

}

void SDLFact::Stop(){
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	SDL_Quit();
}

SDLFact::~SDLFact()
{
}
}

