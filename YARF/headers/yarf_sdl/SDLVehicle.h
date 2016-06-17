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
class SDLVehicle: public Vehicle
{
public:
	SDLVehicle(SDL_Renderer * Renderer, SDL_Texture * Texture, bool init_spawn, int lane,
			int ordinalNumber, //ordinal number = 1st, 2nd, 3rd.. vehicle in the initial lane.
			int vehicleType, int window_width, int window_height,
			double width_scale_factor, double height_scale_factor);
	void Vis(const int & FPS); // Passing the FPS by reference is used to quickly calculate how many

	// This function is currently used in order to put vehicles on the next lane as soon as a border is hit.
	// We're going to change this to a function which returns an integer.
	// if -1 is returned, the vehicle is still within boundaries.
	// if the vehicle is not within boundaries, the function will return the lane number, on which a new vehicle will be created.
	int IsInTerrain();
	void SetDirection();
	void SetInitPos();
	void SetSpawnPos();
	Rect GetRect();
	int GetLane();
	Projectile * CreateProjectile();
	// pixels a vehicle has to move in order to traverse at a constant pixels/second speed despite of the FPS
	void Move(const int & FPS);
	void SetPauseMovements(bool pause_movements);
	bool IsInSpawnZone();

	virtual ~SDLVehicle();

private:

	// vehicle type
	int m_vehicleType;
	SDL_Surface * m_pTempSurface = 0;
	SDL_Texture * m_pTexture = 0;

	//
	SDL_Rect m_vehicleSrcRect;

	// another rectangle to copy to
	SDL_Rect m_vehicleDestRect;

	// test rectangle used whilst checking for entity going outside of the game window
	Rect m_testRect;

	// Rect to share
	Rect m_rect;
	SDL_Rect m_pBorderRect;

	SDL_Renderer * m_pRenderer = 0;

	// Angle -- used for driving left or right;
	int m_angle = 0;

	// Lane -- used to determine whether a car is driver left or right
	// 		-- also used to determine the y position of a vehicle
	int m_lane;

	// Ordinal Number : which ordinal rank does this car initially have on this lane?
	// e.q.: It's the 4th vehicle on this lane. ordinalNumer=4.
	int m_ordinalNumber;

	//Vehicle# width & height
	double m_carWidth = 43;
	double m_carHeight = 25;

	double m_truckWidth = 129;
	double m_truckHeight = 31;

	//window width & height
	double m_windowWidth;
	double m_windowHeight;

	double m_heightScaleFactor;
	double m_widthScaleFactor;

	bool m_pauseMovements = false;
	bool m_inSpawnZone= false;

	SDL_Point m_rotateVehiclePoint;
};
}
#endif /* SRC_SDLVEHICLE_H_ */

//~ Formatted by Jindent --- http://www.jindent.com
