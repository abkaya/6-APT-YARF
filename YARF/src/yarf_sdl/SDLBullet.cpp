/*
 * SDLBullet.cpp
 *
 *  Created on: 25 Apr 2016
 *      Author: abdil
 */

#include "SDLBullet.h"

namespace yarf_sdl
{
SDLBullet::SDLBullet(SDL_Renderer * Renderer, SDL_Texture * Texture,
		SDL_Rect & WindowRect, int window_width, int window_height, double &width_scale_factor,
		double &height_scale_factor, Rect &frog_position, int frog_direction,
		int bullet_theta)
{
	initTheta = bullet_theta;
	theta = bullet_theta;
	frogRect = &frog_position;
	frogDirection = frog_direction;
	pWindowRect = WindowRect;
	pRenderer = Renderer;
	pTexture = Texture;

	bulletSrcRect.x = 0; //m_bulletSrcX;
	bulletSrcRect.y = 0; //m_bulletSrcY;
	if (frogDirection == 5)
		bulletSrcRect.x = 12;
	if (frogDirection == 4)
		bulletSrcRect.x = 24;
	windowWidth = window_width;
	windowHeight = window_height;
	widthScaleFactor = &width_scale_factor;
	heightScaleFactor = &height_scale_factor;

	bulletSrcRect.w = bulletSrcWidth;
	bulletSrcRect.h = bulletSrcHeight;
	bulletDestRect.x = (*(frogRect)).x
			+ static_cast<double>(0.36 * (*(frogRect)).w);
	bulletDestRect.y = (*(frogRect)).y
			+ static_cast<double>(0.36 * (*(frogRect)).h);

	staticCoords.x=frogRect->x+0.35*frogRect->w;
	staticCoords.y=frogRect->y+0.30*frogRect->w;
	staticCoords.w=width;
	staticCoords.h=height;
	staticCoords.theta=bullet_theta;
	position=staticCoords;
	//called once. Now we have the  initial and non-changing
	//coords we need to use in Move();
	//to prevent the sine wave to "slide off" from its "DC offset". (+1 for misplaced EE jargon)

	ConvertGameToVis();
}

void SDLBullet::Vis(const int & fps)
{
	FPS=fps;
	ConvertGameToVis();
	SDL_RenderCopy(pRenderer, pTexture, &bulletSrcRect, &bulletDestRect);
}

void SDLBullet::ConvertGameToVis() //converts the frog game coords to frog visualisation coords
{
	bulletDestRect.w = position.w * 160 * (*widthScaleFactor);
	bulletDestRect.h = position.h * 160 * (*heightScaleFactor);
	bulletDestRect.x = position.x * 160 * (*widthScaleFactor);
	bulletDestRect.y = position.y * 160 * (*heightScaleFactor);

	std::cout<<bulletDestRect.x << " , " << bulletDestRect.y << std::endl;
}

SDLBullet::~SDLBullet()
{

}
}
