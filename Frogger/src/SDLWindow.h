/*
 * SDLWindow.h
 *
 *  Created on: 29 Feb 2016
 *      Author: abdil
 */

#ifndef SRC_SDLWINDOW_H_
#define SRC_SDLWINDOW_H_

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "Window.h"
#include <stdio.h>

//global pointer to Window declared
extern SDL_Window* g_pWindow;

// Extend class Window to the extent of its possibilities. Public will be public, but privates remain private and so on.
class SDLWindow: public Window
{
public:
	SDLWindow();
	void Vis();
	void Close();
	bool Init(const char* title, int xPos, int yPos, int height, int width, int flags);
	void Update();
	void Render();
	void HandleEvents();
	virtual ~SDLWindow();
private:
	const int FPS = 60;
	const double DELAY_TIME = 1000 / FPS;
	const int WIDTH = 640;
	const int HEIGHT = 480;

	//Definition of private pointer to Renderer
	SDL_Renderer* m_pRenderer = 0;
	//Main render loop variable. A private boolean variable
	bool m_bRunning = false;
	//Event handler variable
	SDL_Event m_event;

	double m_frameStart=0;
	double m_frameTime=0;



};

#endif /* SRC_SDLWINDOW_H_ */
