/*
 * SDLVehicle.h
 *
 *  Created on: 8 Mar 2016
 *      Author: abdil
 */

#ifndef SRC_SDLVEHICLE_H_
#define SRC_SDLVEHICLE_H_

#include <iostream>
#include <string>
#include "Vehicle.h"
#include "SDLFact.h"
#include <math.h>
#include "Rect.h"

namespace yarf_sdl
{
class SDLVehicle: public yarf::Vehicle
{
public:
	SDLVehicle(SDL_Renderer * Renderer, SDL_Texture * Texture, bool init_spawn,
			int lane,
			int ordinal_number, //ordinal number = 1st, 2nd, 3rd.. vehicle in the initial lane.
			int vehicle_type, float &width_scale_factor,
			float &height_scale_factor);
	void Vis(const int & fps); // Passing the FPS by reference

	Projectile * CreateProjectile();
	void ConvertGameToVis();
	virtual ~SDLVehicle();

private:
	SDL_Texture * pTexture = 0;	//pointers to renderer and texture (of a sprite sheet)
	SDL_Renderer * pRenderer = 0;
	SDL_Rect vehicleSrcRect;				//used to render

	// another rectangle to copy to
	SDL_Rect vehicleDestRect;

	// test rectangle used whilst checking for entity going outside of the game window
	Rect m_testRect;

	// Rect to share
	Rect m_rect;
	SDL_Rect m_pBorderRect;

	//Vehicle# width & height on texture
	double carSrcWidth = 43;
	double carSrcHeight = 25;

	double truckSrcWidth = 129;
	double truckSrcHeight = 31;

	//window width & height
	double windowWidth;
	double windowHeight;

	float *heightScaleFactor;
	float *widthScaleFactor;

	SDL_Point m_rotateVehiclePoint;
};
}
#endif /* SRC_SDLVEHICLE_H_ */

//~ Formatted by Jindent --- http://www.jindent.com
