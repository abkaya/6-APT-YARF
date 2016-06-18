/*
 * SDLBullet.h
 *
 *  Created on: 25 Apr 2016
 *      Author: abdil
 */

#ifndef SRC_SDLBULLET_H_
#define SRC_SDLBULLET_H_

#include <iostream>
#include <string>
#include "Bullet.h"
#include "SDLFrog.h"
#include "SDLFact.h"
#include "Rect.h"

namespace yarf_sdl
{
class SDLBullet: public yarf::Bullet
{
public:
	SDLBullet(SDL_Renderer * Renderer, SDL_Texture * Texture,
			SDL_Rect & m_windowRect, int window_width, int window_height, double &width_scale_factor,
			double &height_scale_factor, Rect &frog_position, int frog_direction, int bullet_theta);
	void Vis(const int& FPS);
	void ConvertGameToVis();
	virtual ~SDLBullet();
private:
	SDL_Texture * pTexture = 0;
	SDL_Rect pWindowRect;
	SDL_Rect bulletSrcRect;				// source rectangle
	SDL_Rect bulletDestRect;			// bullet vis. destination rectangle
	SDL_Point frogRotatePoint;
	SDL_Renderer * pRenderer = 0;

	double windowWidth;
	double windowHeight;
	double *widthScaleFactor;
	double *heightScaleFactor;
	int bulletSrcX = 0;
	int bulletSrcY = 0;
	int bulletSrcWidth=12;
	int bulletSrcHeight=12;
};
}
#endif /* SRC_SDLBULLET_H_ */
