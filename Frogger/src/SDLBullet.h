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

namespace SDL
{
class SDLBullet: public Game::Bullet
{
public:
	SDLBullet(SDL_Renderer * Renderer, SDL_Texture * Texture,
			SDL_Rect & m_windowRect, int window_width, int window_height,
			double height_scale_factor, Rect &frog_position, int frog_direction, int bullet_theta);
	void Vis(const int& FPS);
	void Move(const int& FPS);
	bool IsInTerrain();
	Rect GetRect();
	virtual ~SDLBullet();
private:
	SDL_Texture * m_pTexture = 0;

	// source rectangle
	SDL_Rect m_bulletSrcRect;

	// another rectangle to copy to
	SDL_Rect m_bulletDestRect;
	SDL_Rect m_pWindowRect;

	// The angle to rotate the frog to before rendering
	//int m_angle = 0;
	SDL_Point m_frogRotatePoint;
	SDL_Renderer * m_pRenderer = 0;
};
}
#endif /* SRC_SDLBULLET_H_ */
