/*
 * SDLBullet.cpp
 *
 *  Created on: 25 Apr 2016
 *      Author: abdil
 */

#include "SDLBullet.h"
#include <math.h>
#define PI 3.14159265

namespace SDL
{
SDLBullet::SDLBullet(SDL_Renderer * Renderer, SDL_Texture * Texture,
		SDL_Rect & WindowRect, int window_width, int window_height,
		double height_scale_factor, Rect &frog_position, int frog_direction,
		int bullet_theta)
{
	m_initTheta = bullet_theta;
	m_theta = bullet_theta;
	m_frogRect = &frog_position;
	m_frogDirection = frog_direction;
	m_pWindowRect = WindowRect;
	m_pRenderer = Renderer;
	m_pTexture = Texture;

	m_bulletSrcRect.x = 0; //m_bulletSrcX;
	m_bulletSrcRect.y = 0; //m_bulletSrcY;
	if (m_frogDirection == 5)
		m_bulletSrcRect.x = 12;
	if (m_frogDirection == 4)
		m_bulletSrcRect.x = 24;
	m_windowWidth = window_width;
	m_windowHeight = window_height;
	m_heightScaleFactor = height_scale_factor;

	m_bulletSrcRect.w = m_bulletWidth;
	m_bulletSrcRect.h = m_bulletHeight;
	m_bulletDestRect.x = frog_position.x
			+ static_cast<double>(0.36 * frog_position.w);
	m_bulletDestRect.y = frog_position.y
			+ static_cast<double>(0.36 * frog_position.h);

	m_bulletWidth = m_bulletWidth * height_scale_factor;
	m_bulletHeight = m_bulletHeight * height_scale_factor;

	m_bulletDestRect.w = m_bulletWidth;
	m_bulletDestRect.h = m_bulletHeight;

	m_staticCoords = GetRect(); //called once. Now we have the  initial and non-changing
								//coords we need to use in Move();
								//to prevent the sine wave to "slide off" from its "DC offset". (+1 for misplaced EE jargon)
}

Rect SDLBullet::GetRect()
{
	m_returnRect.x = m_bulletDestRect.x;
	m_returnRect.y = m_bulletDestRect.y;
	m_returnRect.w = m_bulletDestRect.w;
	m_returnRect.h = m_bulletDestRect.h;
	return m_returnRect;
}

void SDLBullet::Vis(const int & FPS)
{
	SDL_RenderCopy(m_pRenderer, m_pTexture, &m_bulletSrcRect,
			&m_bulletDestRect);
}

void SDLBullet::Move(const int & FPS)
{
	switch (m_frogDirection)
	{
	case 0:                           // North
		m_theta = m_theta + m_bulletSpeed;
		m_bulletDestRect.y -= m_bulletSpeed;
		m_bulletDestRect.x = 10 * ceil(m_heightScaleFactor)
				* sin(m_theta * (PI / 180)) + m_staticCoords.x;
		break;
	case 1:                           // East
		m_theta = m_theta + m_bulletSpeed;
		m_bulletDestRect.x += m_bulletSpeed;
		m_bulletDestRect.y = 10 * ceil(m_heightScaleFactor)
				* sin(m_theta * (PI / 180)) + m_staticCoords.y;
		break;
	case 2:                           // South
		m_theta = m_theta + m_bulletSpeed;
		m_bulletDestRect.y += m_bulletSpeed;
		m_bulletDestRect.x = 10 * ceil(m_heightScaleFactor)
				* sin(m_theta * (PI / 180)) + m_staticCoords.x;
		break;
	case 3:                           // West
		m_theta = m_theta + m_bulletSpeed;
		m_bulletDestRect.x -= m_bulletSpeed;
		m_bulletDestRect.y = 10 * ceil(m_heightScaleFactor)
				* sin(m_theta * (PI / 180)) + m_staticCoords.y;
		break;
	case 4:
		m_radius = m_radius + m_bulletSpeed;
		if (m_theta > (m_initTheta + 1) && m_clockwise == 1)
			m_clockwise = -1;
		if (m_theta < (m_initTheta - 1) && m_clockwise == -1)
			m_clockwise = 1;
		m_theta = m_theta + m_clockwise;
		m_bulletDestRect.x = m_staticCoords.x
				+ m_radius * cos(m_theta * (PI / 180));
		m_bulletDestRect.y = m_staticCoords.y
				+ m_radius * sin(m_theta * (PI / 180));
		break;
	case 5:
		m_theta++;
		m_bulletDestRect.x = m_frogRect->x
				+ static_cast<double>(0.37 * (m_frogRect->w))
				+ m_frogRect->w * 0.65 * cos(m_theta % 360);
		m_bulletDestRect.y = m_frogRect->y
				+ static_cast<double>(0.30 * (m_frogRect->w))
				+ m_frogRect->w * 0.65 * sin(m_theta % 360);
		break;
	case -1:
		break;
	default:
		break;
	}
}

bool SDLBullet::IsInTerrain()
{
	if (m_bulletDestRect.x > m_windowWidth + m_frogRect->w
			|| m_bulletDestRect.x < -m_frogRect->w
			|| m_bulletDestRect.y < -m_frogRect->w
			|| m_bulletDestRect.y > m_windowHeight + m_frogRect->w)
		return 0;
	else
		return 1;
}

SDLBullet::~SDLBullet()
{

}
}
