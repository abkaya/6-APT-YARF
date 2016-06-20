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
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "Fact.h"
#include "Rect.h"
#include <list>
#include <array>
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
	void InitTextures(); // Creates all Textures. We will only pass pointers to these textures.
	void HandleEvents(); // Visualisation and keyboard interaction events -- Game Events are handled separately in Game.cpp
	bool IsRunning();
	int GetTicks();
	Rect GetFrogStates(); //passes frog states resulting from keyboard interaction, caught using HandleEvents
	void RenderClear();
	void RenderPresent();
	Terrain * CreateTerrain();
	yarf::Frog * CreateFrog(list<yarf::Bullet *> &bullet_list);
	yarf::Vehicle * CreateVehicle(bool init_spawn, int lane, int ordinalNumber);
	void Delay(int delay_time);
	void HandleVisEvents();
	void Resize();
	void RenderText();
	void RenderGameStats(int health, int ammo, int score);
	int GetNumberOfDigits(int number);
	void RenderDigits(int numArray[], int startX);
	void Stop();
private:
	int FPS;
	Terrain * TerrainF = 0;
	int WIDTH = 640, HEIGHT = 480;
	int scorebarHeight = 30;
	//the scale factor will adjust along with the width and height
	float widthScaleFactor = static_cast<float>(WIDTH) / 640;
	float heightScaleFactor = static_cast<float>(HEIGHT - 30) / 480;

	SDL_Rect windowRect;
	int m_key = 0;
	bool bRunning = false;			// to perform checks on SDL running

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

	/*Text Rendering*/
	TTF_Font* font;
	// this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	SDL_Color orange;
	SDL_Color green;
	SDL_Color fontColor;

	//Making a texture for each number, instead of recreating the texture every single time we render
	SDL_Surface *textSurface;
	SDL_Texture *textTexture;
	string sMessage="Health:                          Ammo:                          Score:  ";
	SDL_Rect textRect;

	/*Rendering numbers/game stats*/
	SDL_Rect numSrcRect;
	SDL_Rect numDstRect;
	int numSrcX=0;
	int numSrcY=94;

	int numWidth=17;
	int numHeight=25;

	int healthDstX=90*widthScaleFactor;
	int ammoDstX=295*widthScaleFactor;
	int scoreDstX=490*widthScaleFactor;
	int numDstY=HEIGHT-30;

	int healthArr[5];
	int healthLength;
	int ammoArr[5];
	int ammoLength;
	int scoreArr[5];
	int scoreLength;

	int tempHealth;
	int tempAmmo;
	int	tempScore;
};
}
#endif /* SRC_SDLFACT_H_ */
