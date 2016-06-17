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
	SDLFrog::SDLFrog(SDL_Renderer * Renderer, SDL_Texture * Texture,
		SDL_Rect & WindowRect, int window_width, int window_height,
		double height_scale_factor, list<yarf::Bullet *> &bullet_list)
{
	m_bulletList = &bullet_list;
	m_pWindowRect = WindowRect;
	// cout << WindowRect << endl;
	m_pRenderer = Renderer;
	m_angle = 0;
	m_pTexture = Texture;

	// non-leap nlx,nly
	m_frogSrcRect.x = nlx;
	m_frogSrcRect.y = nly;

	m_windowWidth = window_width;
	m_windowHeight = window_height;
	m_heightScaleFactor = height_scale_factor;

	m_frogSrcRect.w = m_frogWidth;
	m_frogSrcRect.h = m_frogHeight;

	m_frogWidth = m_frogWidth * m_heightScaleFactor;
	m_frogHeight = m_frogHeight * m_heightScaleFactor;

	m_frogDestRect.w = m_frogWidth;
	m_frogDestRect.h = m_frogHeight;

	m_frogDestRect.x = m_windowWidth / 2;               // Frog start x position
	m_frogDestRect.y = m_windowHeight - m_frogHeight;   // Frog start y position

	// the point around which we will rotate the frog in order to maintain a correct position on the terrain's lanes when going forth and back.
	m_frogRotatePoint.x = m_frogDestRect.w / 2;    // Remains default
	m_frogRotatePoint.y = m_frogDestRect.h / 3; // y-point moved closer to the head of the frog

	m_jumpLength *= m_heightScaleFactor;

	//Bullet = CreateBullet();
}

void SDLFrog::Vis(int direction, int leaping, const int & FPS)
{
	for (auto* bullet : *m_bulletList)
	{
		bullet->Vis(FPS);
		bullet->Move(FPS);
	}
	if ((m_leaping != 0) || ((m_leaping == 0) && (leaping == 1)))
	{
		// Render the leaping state of frog for about 250ms.
		//This is just about enough for a human to get the sense of a leaping frog.
		m_leaping = (m_leaping + 1) % (FPS / 4);
		Leap(direction);
	}
	else
	{
		//render the frog when there hasn't been a jump initiated in the last 250ms
		m_angle = SetDest(direction, m_frogDestRect.x, m_frogDestRect.y);
		SDL_RenderCopyEx(m_pRenderer, m_pTexture, &m_frogSrcRect,
				&m_frogDestRect, m_angle, &m_frogRotatePoint, SDL_FLIP_NONE);
	}
}

bool SDLFrog::IsInTerrain(Rect entityRect)
{
	if ((entityRect.x < m_pWindowRect.x - m_frogWidth / 2)
			|| (entityRect.x + entityRect.w) > (m_pWindowRect.w)
			|| (entityRect.y < m_pWindowRect.y)
			|| (entityRect.y + entityRect.h)
					> (m_pWindowRect.h + m_frogWidth / 2))
	{
		cout << "Detected unruly Frog!" << endl;
		cout << "(" << entityRect.x << "," << entityRect.y << ") ["
				<< entityRect.x + entityRect.w << ","
				<< entityRect.y + entityRect.h << "]" << endl;
		return false;
	}
	else
	{
		return true;
	}
}

void SDLFrog::Leap(int & direction)
{
	//Frog update basically initiates a jump
	//private source rectangle of the frog
	m_frogSrcRect.x = 42;
	m_angle = SetDest(direction, m_frogDestRect.x, m_frogDestRect.y);
	SDL_RenderCopyEx(m_pRenderer, m_pTexture, &m_frogSrcRect, &m_frogDestRect,
			m_angle, &m_frogRotatePoint, SDL_FLIP_NONE);
	m_frogSrcRect.x = 0;
}

Rect SDLFrog::GetRect()
{
	m_hitRect.x = m_frogDestRect.x;
	m_hitRect.y = m_frogDestRect.y;
	m_hitRect.w = m_frogDestRect.w;
	m_hitRect.h = static_cast<double>(m_frogDestRect.h
			- 20 * m_heightScaleFactor);
	return m_hitRect;
}

void SDLFrog::Kill()
{
	m_angle=0;
	m_frogDirection=0;
	m_frogDestRect.x = m_windowWidth / 2;               // Frog start x position
	m_frogDestRect.y = m_windowHeight - m_frogHeight;   // Frog start y position
}


int SDLFrog::SetDest(int direction, int & xCoord, int & yCoord)
{
	m_testRect.x = m_frogDestRect.x;
	m_testRect.y = m_frogDestRect.y;
	m_testRect.w = m_frogDestRect.w;
	m_testRect.h = m_frogDestRect.h;
	switch (direction)
	{
	case 0:                           // North
		m_testRect.y -= m_jumpLength;
		if (IsInTerrain(m_testRect) == true)
		{
			yCoord -= m_jumpLength;    // move up
		}
		m_angle = 0;
		m_frogDirection = 0;
		break;
	case 1:                           // East
		m_testRect.x += m_jumpLength;
		if (IsInTerrain(m_testRect) == true)
		{
			xCoord += m_jumpLength;    // move to the right;
		}
		m_angle = 90;
		m_frogDirection = 1;
		break;
	case 2:                           // South
		m_testRect.y += m_jumpLength;
		if (IsInTerrain(m_testRect) == true)
		{
			yCoord += m_jumpLength;    // move down
		}
		m_angle = 180;
		m_frogDirection = 2;
		break;
	case 3:                           // West
		m_testRect.x -= m_jumpLength;
		if (IsInTerrain(m_testRect) == true)
		{
			xCoord -= m_jumpLength;    // move to the left
		}
		m_angle = 270;
		m_frogDirection = 3;
		break;
	case -1:
		break;
	default:
		break;
	}
	return m_angle;
}

void SDLFrog::CreateBullet() //regular single direction bullets
{
	GetRect(); //update m_hitRect
	m_bulletList->push_back(
			new yarf_sdl::SDLBullet(m_pRenderer, m_pTexture, m_pWindowRect,
					m_windowWidth, m_windowHeight, m_heightScaleFactor,
					m_hitRect, m_frogDirection, -1));
}

void SDLFrog::CreateBullet(int direction, int theta) //bullets moving on a circle
{
	GetRect(); //update m_hitRect
	m_bulletList->push_back(
			new yarf_sdl::SDLBullet(m_pRenderer, m_pTexture, m_pWindowRect,
					m_windowWidth, m_windowHeight, m_heightScaleFactor,
					m_hitRect, direction, theta));
}

SDLFrog::~SDLFrog()
{
	cout << "SDLFrog.~SDLFrog():\n\t\tDestroyed an SDLFrog object. [INDIRECT]"
			<< endl;
}

}
