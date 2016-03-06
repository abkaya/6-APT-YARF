/*
 * SDLWindow.cpp
 *
 *  Created on: 29 Feb 2016
 *      Author: abdil
 *----------------------------------------------------------------------
 * 	SDL Wiki and References:
 *  SDL Tutorial used: http://lazyfoo.net/tutorials/SDL/
 *
 *  Public Domain 2D Characters, Labeled for reuse with modification
 *
 *  --------------------------------------------------------------------
 */

#include "SDLWindow.h"

//Definition of global pointer to Window
SDL_Window* g_pWindow = 0;

SDLWindow::SDLWindow()
{
}

void SDLWindow::Vis()
{
	cout << "SDLWindow:\tMake WINDOW IN SDL" << endl;

	if (Init("Chapter 1: Setting up SDL",
	SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT,
			SDL_WINDOW_SHOWN))
	{
		m_bRunning = true;
	}

	//Regulating Frame Rate
	//	-- Reference : [2] in main.cpp
	while (m_bRunning)
	{
		m_frameStart = SDL_GetTicks();

		HandleEvents();
		Update();
		Render();

		//The time needed to execute the 3 previous functions is taken into consideration
		//when calculating the appropriate delay in order to reach the aimed FPS
		m_frameTime = SDL_GetTicks() - m_frameStart;

		if (m_frameTime < DELAY_TIME)
		{
			SDL_Delay((int) (DELAY_TIME - m_frameTime));
		}
	}

	Close();
}

void SDLWindow::Close()
{
	// set a delay before quitting
	//SDL_Delay(5000);
	// clean up SDL
	SDL_DestroyWindow(g_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

bool SDLWindow::Init(const char* title, int xpos, int ypos, int height,
		int width, int flags)
{
	// initialise SDL -- including SDL_INIT_... HAPTIC,AUDIO,VIDEO,TIMER,JOYSTICK
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		// if succeeded create our window
		g_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);
		// if the window creation succeeded create our renderer
		if (g_pWindow != 0)
		{
			//https://wiki.libsdl.org/SDL_CreateRenderer
			m_pRenderer = SDL_CreateRenderer(g_pWindow, -1,
					SDL_RENDERER_ACCELERATED);

			// renderer init success
			if (m_pRenderer != 0)
			{
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
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
		return false; // sdl could not initialize
	}
	return true;
}

void SDLWindow::Render()
{
	// clear the window to the RenderDrawColor set in the Init function ^
	SDL_RenderClear(m_pRenderer);
	// show the window
	SDL_RenderPresent(m_pRenderer);
}

void SDLWindow::Update()
{

}


void SDLWindow::HandleEvents()
{
	if (SDL_PollEvent (&m_event))
	{
		switch (m_event.type)
		{
		//If user presses the X button, the render loop breaks
		case SDL_QUIT:
			m_bRunning = false;
			break;
		default:
			break;
		}
	}
}

SDLWindow::~SDLWindow()
{
	cout
			<< "SDLWindow.~SDLWindow():\n\t\tDestroyed an SDLWindow object. [INDIRECT]"
			<< endl;
}
