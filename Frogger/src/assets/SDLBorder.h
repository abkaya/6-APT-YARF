/*
 * SDLBorder.h
 *
 *  Created on: 7 Mar 2016
 *      Author: abdil
 */
/*
#ifndef SRC_SDLBORDER_H_
#define SRC_SDLBORDER_H_

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "Border.h"
#include "SDLWindow.h"

class SDLBorder: public Border
{
public:
	SDLBorder(SDL_Renderer* Renderer);
	void Vis();
	virtual ~SDLBorder();
private:
	SDL_Renderer* m_pRenderer;

	SDL_Surface* m_pTempSurface;
	//Private pointer to the SDL_Texture variable. This is our frog.
	SDL_Texture* m_pStaticBorder;
	// the first rectangle
	SDL_Rect m_sourceRectangle;
	// another rectangle to copy to
	SDL_Rect m_destinationRectangle;
};

#endif /* SRC_ASSETS_SDLBORDER_H_ */
*/
