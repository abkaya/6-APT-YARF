/*
 * Vehicle.cpp
 *
 *  Created on: 8 Mar 2016
 *      Author: abdil
 */

#include "Vehicle.h"
namespace yarf
{
Vehicle::Vehicle()
{
}

int Vehicle::GetLane()
{
	return m_lane;
}

// spawn cars initially according to their ordinal number, and give them some sway to budge in
// the spawned vehicled can sway 48 pixels ahead or behind their
// destined ordinal rank location within a lane, making for a more natural positioning
void Vehicle::SetInitPos()
{
	if (m_lane % 2 == 0) // vehicles moving to the right
	{
		position.x = -truckWidth + ordinalNumber * (gameAxisWidth / 3)
				+ (rand() % 200 - 100) / 160;
	}
	else // vehicles moving to the left
	{
		position.x = gameAxisWidth + truckWidth
				- ordinalNumber * (gameAxisWidth / 3)
				+ (rand() % 200 - 100) / 160;
	}
}

void Vehicle::SetSpeed(float speedScaleFactor)
{
	speed = speed * speedScaleFactor;
}

void Vehicle::SetSpawnPos()
{
	if (m_lane % 2 == 0) // vehicles moving to the right
	{
		if (vehicleType == 4)
			position.x = -1.3 * truckWidth;
		else
			position.x = -1.1 * carWidth;
	}
	else // vehicles moving to the left
	{
		if (vehicleType == 4)
			position.x = gameAxisWidth + 1.3 * truckWidth;
		else
			position.x = gameAxisWidth + 1.1 * carWidth;
	}
}

void Vehicle::SetDirection() //just called once -- allow it to simultaneously handle other one-time assignments.
{
	if (vehicleType == 4)
	{
		position.w = truckWidth;
		position.h = truckHeight;
	}
	else
	{
		position.w = carWidth;
		position.h = carHeight;
	}
	//arbitrary game border to delete vehicles
	borderRect.x = -1.7 * truckWidth;
	borderRect.w = gameAxisWidth + 2.7 * truckWidth;

	// gameAxisHeight=3;
	position.y = ((m_lane + 1) * gameAxisHeight / 10) + 0.15 - position.h / 2; //perfectly center the cars
	if (m_lane % 2 == 0) // if lane is even, set angle of vehicle to 180°: drive right
		angle = 180;      // to the right (counter-intuitive)
	else
		angle = 0;        // to the left (counter-intuitive)
}

bool Vehicle::IsInSpawnZone()
{
	return inSpawnZone;
}

// SDLVehicle Move() : Defines how many pixels a car will have moved by the next time a frame renders. Dependent on difficulty(W.I.P.) and FPS.
void Vehicle::Move()
{
	speed = 0.25f * (abs(m_lane - 9)) / (float) FPS;
	if (angle == 0)
	{
		position.x -= speed; //speed dependent on lane and FPS
		//check on whether or not the vehicle needs replacement (if out of boundaries)
		if ((position.x + position.w) > gameAxisWidth - 1.5 * truckWidth)
			inSpawnZone = true;
		else
			inSpawnZone = false;
	}
	else // cars moving to the right
	{
		position.x += speed;
		if (position.x < 2 * truckWidth)
			inSpawnZone = true;
		else
			inSpawnZone = false;
	}
}

//If the vehicle is out of bounds, the lane will be returned to spawn a new vehicle
// in that lane
//If the vehicle is not out of bounds, it can live on. -1 is returned.
int Vehicle::IsInTerrain()
{
	if ((position.x + position.w / 2 < borderRect.x)
			|| (position.x + position.w / 2) > (borderRect.w))
	{
		return m_lane;
	}
	else
	{
		return -1;
	}
}

Vehicle::~Vehicle()
{
}

}
