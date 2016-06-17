/*
 * SDLVehicle.cpp
 *
 *  Created on: 8 Mar 2016
 *      Author: abdil
 */

#include "SDLVehicle.h"
#include "SDLProjectile.h"
#include <cmath>

namespace yarf_sdl
{

// direction: 1= right, 0 = left
SDLVehicle::SDLVehicle(SDL_Renderer * Renderer, SDL_Texture * Texture,
		bool init_spawn,
		int lane,    // instead of y, give lane number. 1-8.
		int ordinalNumber, int vehicleType, int window_width, int window_height,
		double width_scale_factor, double height_scale_factor)
{
	// non-leap nlx,nly
	m_vehicleSrcRect.x = 0;
	m_vehicleSrcRect.y = 64;

	m_windowWidth = window_width;
	m_windowHeight = window_height;
	m_widthScaleFactor = width_scale_factor;
	m_heightScaleFactor = height_scale_factor;

	m_ordinalNumber = abs(ordinalNumber - 4 * m_widthScaleFactor);
	m_lane = lane;
	m_vehicleType = vehicleType;
	m_pRenderer = Renderer;
	m_pTexture = Texture;

	m_vehicleSrcRect.w = m_carWidth;
	m_vehicleSrcRect.h = m_carHeight;

	m_carWidth = m_carWidth * m_heightScaleFactor;
	m_carHeight = m_carHeight * m_heightScaleFactor;

	m_vehicleDestRect.w = m_carWidth;
	m_vehicleDestRect.h = m_carHeight;

	//Only for initial spawn.
	//every other spawn needs to happen with precise x positions.
	if (init_spawn == true)
		SetInitPos();
	else
		SetSpawnPos();

	SetDirection();
	m_rotateVehiclePoint.y = m_vehicleDestRect.h / 2;
	m_rotateVehiclePoint.x = m_vehicleDestRect.w;
	m_vehicleSrcRect.x += (m_vehicleType * 44); //44 = distance between vehicles on spritesheet
	if (m_vehicleType == 4)
	{
		m_vehicleSrcRect.w = m_truckWidth;
		m_vehicleSrcRect.h = m_truckHeight;

		m_truckWidth = m_truckWidth * m_heightScaleFactor;
		m_truckHeight = m_truckHeight * m_heightScaleFactor;

		m_vehicleDestRect.w = m_truckWidth;
		m_vehicleDestRect.h = m_truckHeight;
	}
	m_pBorderRect.x = -1.7 * m_truckWidth;
	m_pBorderRect.w = m_windowWidth + 1.7 * m_truckWidth;
}
Rect SDLVehicle::GetRect()
{
	m_rect.x = m_vehicleDestRect.x;
	m_rect.y = m_vehicleDestRect.y;
	m_rect.w = m_vehicleDestRect.w;
	m_rect.h = m_vehicleDestRect.h;
	return m_rect;
}

int SDLVehicle::GetLane()
{
	return m_lane;
}

void SDLVehicle::SetDirection()
{
	// First car starts at y=84 default. Adjusted with the scale factor and multiplied with the terrain
	//block height wihch happens to be 1/10 of the height of the window.
	m_vehicleDestRect.y = static_cast<double>(84 * m_heightScaleFactor)
			+ (m_lane * m_windowHeight / 10);

	if (m_lane % 2 == 0) // if lane is even, set angle of vehicle texture to 180°: drive right
	{
		m_angle = 180;      // to the right
	}
	else
	{
		m_angle = 0;        // to the left
	}
}

// spawn cars initially according to their ordinal number, and give them some sway to budge in
// the spawned vehicled can sway 48 pixels ahead or behind their
// destined ordinal rank location within a lane, making for a more natural positioning
void SDLVehicle::SetInitPos()
{
	if (m_lane % 2 == 0) // vehicles moving to the right
	{
		m_vehicleDestRect.x = -m_truckWidth
				+ m_ordinalNumber
						* (m_windowWidth
								/ static_cast<double>(2.5 * m_widthScaleFactor))
				+ rand() % 200 - 100;
	}
	else // vehicles moving to the left
	{
		m_vehicleDestRect.x = m_windowWidth + m_truckWidth
				- m_ordinalNumber
						* (m_windowWidth
								/ static_cast<double>(2.5 * m_widthScaleFactor))
				+ rand() % 200 - 100;
	}
}

void SDLVehicle::SetSpawnPos()
{
	if (m_lane % 2 == 0) // vehicles moving to the right
	{
		if (m_vehicleType == 4)
			m_vehicleDestRect.x = -1.3 * m_truckWidth;
		else
			m_vehicleDestRect.x = -m_carWidth;
	}
	else // vehicles moving to the left
	{
		if (m_vehicleType == 4)
			m_vehicleDestRect.x = m_windowWidth + 1.3*m_truckWidth;
		else
			m_vehicleDestRect.x = m_windowWidth + m_carWidth;
	}
}

//
void SDLVehicle::Vis(const int & FPS)
{
	IsInTerrain();
	Move(FPS);
	SDL_RenderCopyEx(m_pRenderer, m_pTexture, &m_vehicleSrcRect,
			&m_vehicleDestRect, m_angle, NULL, SDL_FLIP_NONE);
}

int SDLVehicle::IsInTerrain()
{
	if ((m_vehicleDestRect.x + m_vehicleDestRect.w / 2 < m_pBorderRect.x)
			|| (m_vehicleDestRect.x + m_vehicleDestRect.w / 2)
					> (m_pBorderRect.w))
	{
		/*
		 m_lane++;
		 m_lane = m_lane % 8;    // place the vehicle on the next lane. (Circular)
		 SetDirection();
		 */

		return m_lane;
	}
	else
	{
		return -1;
	}
}

Projectile * SDLVehicle::CreateProjectile()
{
	return new SDLProjectile(m_pRenderer, m_pTexture);
}

// SDLVehicle Move() : Defines how many pixels a car will have moved by the next time a frame renders. Dependent on difficulty(W.I.P.) and FPS.
void SDLVehicle::Move(const int & FPS)
{
	if (m_angle == 0)
	{
		m_vehicleDestRect.x -= ceil((40 * (abs(m_lane - 9)) / (double) FPS)); // In order to get a constant speed of (m_lane * 20) pixels/second

		if ((m_vehicleDestRect.x + m_vehicleDestRect.w) > m_windowWidth-1.5*m_truckWidth)
			m_inSpawnZone = true;
		else
			m_inSpawnZone = false;
		// despite of the FPS (FPS<=100). Ceil and ast to double to prevent pixel addition to result in + or - 0 at 100FPS.
	}
	else // cars moving to the right
	{
		m_vehicleDestRect.x += ceil((40 * (abs(m_lane - 9)) / (double) FPS));
		if (m_vehicleDestRect.x < 2*m_truckWidth)
			m_inSpawnZone = true;
		else
			m_inSpawnZone = false;
	}
}

void SDLVehicle::SetPauseMovements(bool pause_movements)
{
	m_pauseMovements = pause_movements;
}

bool SDLVehicle::IsInSpawnZone()
{
	return m_inSpawnZone;
}

// SDLVehicle Destructor
SDLVehicle::~SDLVehicle()
{
}

}
