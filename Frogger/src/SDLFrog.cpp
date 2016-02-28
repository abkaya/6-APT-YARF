/*
 * SDLFrog.cpp
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */
#include <SDL.h>
#include <stdio.h>

#include <iostream>
#include "SDLFrog.h"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDLFrog::SDLFrog()
{
}

void SDLFrog::Vis()
{
	/*test
		 * http://lazyfoo.net/tutorials/SDL/01_hello_SDL/index2.php
		 */

		//The window we'll be rendering to
		SDL_Window* window = NULL;

		//The surface contained by the window
		SDL_Surface* screenSurface = NULL;

		//Initialize SDL
		if (SDL_Init( SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//Create window
			window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
					SDL_WINDOW_SHOWN);
			if (window == NULL)
			{
				printf("Window could not be created! SDL_Error: %s\n",
						SDL_GetError());
			}
			else
			{
				//Get window surface
				screenSurface = SDL_GetWindowSurface(window);

				//Fill the surface white
				SDL_FillRect(screenSurface, NULL,
						SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

				//Update the surface
				SDL_UpdateWindowSurface(window);

				//Wait two seconds
				SDL_Delay(2000);
			}
		}
		//Destroy window
		SDL_DestroyWindow(window);

		//Quit SDL subsystems
		SDL_Quit();
	cout << "SDLFrog:\tVisualise FROG IN SDL" << endl;
}

SDLFrog::~SDLFrog()
{
	cout << "SDLFrog.~SDLFrog():\n\t\tDestroyed an SDLFrog object. [INDIRECT]" << endl;
}
