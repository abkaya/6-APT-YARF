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
			SDL_Rect & m_windowRect, int window_width, int window_height,
			double height_scale_factor, list<yarf::Bullet *> &bullet_list);
	void Vis(int direction, int leaping, const int & FPS);
	bool IsInTerrain(Rect entityRect);
	void Leap(int & direction);
	void Kill();
	Rect GetRect();
	int SetDest(int direction, int & xCoord, int & yCoord);
	void CreateBullet();
	void CreateBullet(int direction, int theta);
	virtual ~SDLFrog();

private:
	SDL_Texture * m_pTexture = 0;

	// source rectangle
	SDL_Rect m_frogSrcRect;

	// another rectangle to copy to
	SDL_Rect m_frogDestRect;

	// Rect to share
	Rect m_hitRect;

	SDL_Rect m_pWindowRect;

	// test rectangle used whilst checking for entity going outside of the game window
	Rect m_testRect;

	// The angle to rotate the frog to before rendering
	int m_angle = 0;
	int m_frogDirection = 0; //0 north, 1 east, 2 south, 4 west
	SDL_Point m_frogRotatePoint;
	SDL_Renderer * m_pRenderer = 0;

	// non-leap Frog coords on the texture
	int nlx = 0;
	int nly = 120;

	// frog width and height for both leaping and not leaping
	double m_frogWidth = 41;
	double m_frogHeight = 46;

	double m_windowWidth;
	double m_windowHeight;
	double m_heightScaleFactor;

	// m_leaping can be anywhere
	int m_leaping = 0;

	// jump pixels
	int m_jumpLength = 65;

	yarf::Bullet * Bullet = 0;
	list<yarf::Bullet *> *m_bulletList;
protected:
	int b;
};
}
#endif /* SRC_SDLFROG_H_ */

