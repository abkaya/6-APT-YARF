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
		int ordinal_number, int vehicle_type, float &width_scale_factor,
		float &height_scale_factor)
{
	// non-leap nlx,nly
	vehicleSrcRect.x = 0;
	vehicleSrcRect.y = 64;

	widthScaleFactor = &width_scale_factor;
	heightScaleFactor = &height_scale_factor;

	ordinalNumber = abs(ordinal_number - 4);
	m_lane = lane;
	vehicleType = vehicle_type;
	pRenderer = Renderer;
	pTexture = Texture;

	vehicleSrcRect.w = carSrcWidth;
	vehicleSrcRect.h = carSrcHeight;

	carSrcWidth = carSrcWidth * (*widthScaleFactor);
	carSrcHeight = carSrcHeight * (*heightScaleFactor);

	vehicleDestRect.w = carSrcWidth;
	vehicleDestRect.h = carSrcHeight;

	//Only for initial spawn.
	//every other spawn needs to happen with precise x positions.
	if (init_spawn == true)
		SetInitPos();
	else
		SetSpawnPos();

	SetDirection();
	m_rotateVehiclePoint.y = vehicleDestRect.h / 2;
	m_rotateVehiclePoint.x = vehicleDestRect.w / 2;

	vehicleSrcRect.x += (vehicleType * 44); //44 = distance between vehicles on spritesheet
	if (vehicleType == 4)
	{
		vehicleSrcRect.w = truckSrcWidth;
		vehicleSrcRect.h = truckSrcHeight;
	}
}

//
void SDLVehicle::Vis(const int & fps)
{
	//IsInTerrain();
	//Move(FPS);
	ConvertGameToVis();
	FPS=fps;
	SDL_RenderCopyEx(pRenderer, pTexture, &vehicleSrcRect, &vehicleDestRect,
			angle, NULL, SDL_FLIP_NONE);
}

Projectile * SDLVehicle::CreateProjectile()
{
	return new SDLProjectile(pRenderer, pTexture);
}

void SDLVehicle::ConvertGameToVis() //converts the frog game coords to frog visualisation coords
{
	vehicleDestRect.w = position.w * 160 * (*widthScaleFactor);
	vehicleDestRect.h = position.h * 160 * (*heightScaleFactor);
	vehicleDestRect.x = position.x * 160 * (*widthScaleFactor);
	vehicleDestRect.y = position.y * 160 * (*heightScaleFactor);
}

// SDLVehicle Destructor
SDLVehicle::~SDLVehicle()
{
}

}
