/*
 * SDLFact.h
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#ifndef SRC_SDLFACT_H_
#define SRC_SDLFACT_H_

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include "Fact.h"
#include "Rect.h"
#include <list>
#include "SDLBullet.h"

//for random function and seeding it with ctime
#include <cstdlib>
#include <ctime>

namespace yarf_sdl
{
class SDLFact: public yarf::Fact
{
public:
	SDLFact();
	virtual ~SDLFact();
	bool Init(const char * title, int xPos, int yPos, int height, int width,
			int flags);
	void InitTextures(); 	// Creates all Textures. We will only pass pointers to these textures.
	void HandleEvents();	// Visualisation and keyboard interaction events -- Game Events are handled separately in Game.cpp
	bool IsRunning();
	int GetTicks();
	Rect GetFrogStates();	//passes frog states resulting from keyboard interaction, caught using HandleEvents
	void RenderClear();
	void RenderPresent();
	Terrain * CreateTerrain();
	yarf::Frog * CreateFrog(list<yarf::Bullet *> &bullet_list);
	yarf::Vehicle * CreateVehicle(bool init_spawn, int lane, int ordinalNumber);
	void Delay(int delay_time);
	void HandleVisEvents();
	void Resize();
	void Stop();
private:
	int FPS;
	Terrain * TerrainF = 0;
	int collided = 0;

	int WIDTH = 640, HEIGHT = 480;
	//the scale factor will adjust along with the width and height
	float widthScaleFactor = static_cast<float>(WIDTH) / 640;
	float heightScaleFactor = static_cast<float>(HEIGHT) / 480;

	// Border for Frog in game = gamewindow
	SDL_Rect windowRect;
	SDL_Rect vehicleBorder;

	int m_key = 0;

	// Main render loop variable. A private boolean variable
	bool bRunning = false;

	// Event handler variable
	SDL_Event event;

	// Definition of private pointer to Renderer
	SDL_Renderer * pRenderer = 0;

	// Temporary surface from which we'll create the Texture
	SDL_Surface * pTempSurface = 0;

	// Definition of private pointer to Texture
	SDL_Texture * pTexture;

	// pointer to Window declared
	SDL_Window * pWindow = 0;
	Rect FrogStates;

};
}
#endif /* SRC_SDLFACT_H_ */
