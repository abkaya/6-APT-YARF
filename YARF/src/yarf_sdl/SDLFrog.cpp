/*
 * SDLFrog.cpp
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#include "SDLFrog.h"
#include <time.h>

namespace yarf_sdl
{
SDLFrog::SDLFrog(SDL_Renderer *Renderer, SDL_Texture *Texture,
		SDL_Rect & WindowRect, int window_width, int window_height,
		float &width_scale_factor, float &height_scale_factor, list<yarf::Bullet *> &bullet_list)
{
	m_bulletList = &bullet_list;
	pWindowRect = WindowRect;
	m_pRenderer = Renderer;
	m_pTexture = Texture;

	frogSrcRect.x = frogSrcX;
	frogSrcRect.y = frogSrcY;

	windowWidth = window_width; //to be removed once bullets are converted to game
	windowHeight = window_height; //to be removed once bullets are converted to game
	heightScaleFactor = &height_scale_factor;
	widthScaleFactor = &width_scale_factor;

	frogSrcRect.w = frogSrcWidth;
	frogSrcRect.h = frogSrcHeight;

	ConvertGameToVis();
/*
	// the point around which we will rotate the frog in order to maintain a correct position on the terrain's lanes when going forth and back.
	// this does only affects hitbox accuracy in a positive way, because the hitbox should
	// and does work on the default frog, not on the leaping frog.
	frogRotatePoint.x = frogDestRect.w / 2;   	// Remains default
	frogRotatePoint.y = frogDestRect.h / 2; 	// y-point moved closer to the head of the frog*/
}

void SDLFrog::Vis(int direction, int leap, const int & FPS)
{
	hitRect=GetRect(); //To update the position of the frog -- passing it to bullets
	ConvertGameToVis();
	for (auto* bullet : *m_bulletList)
	{
		bullet->Vis(FPS);
		bullet->Move();
	}
	if ((leaping != 0) || ((leaping == 0) && (leap == 1)))
	{
		// Render the leaping state of frog for about 250ms.
		//This is just about enough for a human to get the sense of a leaping frog.
		leaping = (leaping + 1) % (FPS / 4);
		LeapVis(direction);
	}
	else
	{
		//render the frog when there hasn't been a jump initiated in the last 250ms
		SDL_RenderCopyEx(m_pRenderer, m_pTexture, &frogSrcRect,
				&frogDestRect, position.theta, NULL,
				SDL_FLIP_NONE);
	}
}

void SDLFrog::ConvertGameToVis() 	//converts the frog game coords to frog visualisation coords
{
	frogDestRect.w = position.w * 160 * (*widthScaleFactor);
	frogDestRect.h = position.h * 160 * (*heightScaleFactor);
	frogDestRect.x = position.x * 160 * (*widthScaleFactor);
	frogDestRect.y = position.y * 160 * (*heightScaleFactor);
}

void SDLFrog::LeapVis(int & direction) //visualising the leaping frog, rather than default frog
{
	hitRect=GetRect();
	ConvertGameToVis();
	frogSrcRect.x = 42;
	SDL_RenderCopyEx(m_pRenderer, m_pTexture, &frogSrcRect, &frogDestRect,
			position.theta, NULL, SDL_FLIP_NONE);
	frogSrcRect.x = 0;
}

// regular single direction bullets
void SDLFrog::CreateBullet()
{
	hitRect=GetRect(); //update hitRect and pass by reference
	m_bulletList->push_back(
			new yarf_sdl::SDLBullet(m_pRenderer, m_pTexture, pWindowRect,
					windowWidth, windowHeight, *widthScaleFactor, *heightScaleFactor,
					hitRect, frogDirection, -1));
}

// bullets moving on a circle
void SDLFrog::CreateBullet(int direction, int theta)
{
	hitRect=GetRect(); //update hitRect and pass by reference
	m_bulletList->push_back(
			new yarf_sdl::SDLBullet(m_pRenderer, m_pTexture, pWindowRect,
					windowWidth, windowHeight, *widthScaleFactor, *heightScaleFactor,
					hitRect, direction, theta));
}

SDLFrog::~SDLFrog()
{
}

}
