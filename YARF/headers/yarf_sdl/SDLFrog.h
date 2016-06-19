/*
 * SDLFrog.h
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#ifndef SRC_SDLFROG_H_
#define SRC_SDLFROG_H_

#include <iostream>
#include <string>
#include "Frog.h"
#include "SDLFact.h"
#include "SDLBullet.h"
#include "Rect.h"
#include <list>

namespace yarf_sdl
{
// Extend class Frog to the extent of its possibilities. Public will be public, but privates remain private and so on.
class SDLFrog: public yarf::Frog
{
public:
	SDLFrog(SDL_Renderer * Renderer, SDL_Texture * Texture,
			SDL_Rect & m_windowRect, float &width_scale_factor,
			float &height_scale_factor, list<yarf::Bullet *> &bullet_list);
	void Vis(int direction, int leaping, const int & FPS);
	void LeapVis(int & direction);
	void CreateBullet();
	void CreateBullet(int direction, int theta);
	void ConvertGameToVis();
	virtual ~SDLFrog();

private:
	SDL_Texture * pTexture = 0;
	SDL_Rect frogSrcRect; 				// source rectangle
	SDL_Rect frogDestRect;				// visualisation destination rectangle
	Rect hitRect; 						// frogDestRect used to pass by reference to bullets
	SDL_Rect pWindowRect;				// window pointer will be assigned through constructor
	SDL_Point frogRotatePoint;
	SDL_Renderer * pRenderer = 0;		// renderer pointer will be assigned through constructor

	int frogSrcX = 0;					// non-leap Frog coords on the texture
	int frogSrcY = 120;

	// frog width and height on the texture
	double frogSrcWidth = 41;
	double frogSrcHeight = 46;

	float *widthScaleFactor;
	float *heightScaleFactor;

	// m_leaping can be anywhere
	int leaping = 0;

	yarf::Bullet * Bullet = 0;
	list<yarf::Bullet *> *bulletList;
};
}
#endif /* SRC_SDLFROG_H_ */

