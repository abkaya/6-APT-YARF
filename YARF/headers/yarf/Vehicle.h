/*
 * Vehicle.h
 *
 *  Created on: 8 Mar 2016
 *      Author: abdil
 */

#ifndef SRC_VEHICLE_H_
#define SRC_VEHICLE_H_

#include <iostream>
#include "Rect.h"
#include "Projectile.h"
#include "Entity.h"

namespace yarf
{
class Vehicle: public Entity
{
public:
	Vehicle();
	void Move();
	int GetLane();
	// if -1 is returned, the vehicle is still within boundaries.
	// if the vehicle is not within boundaries, the function will return the lane number, on which a new vehicle will be created.
	int IsInTerrain();
	void SetDirection();
	void SetInitPos();
	void SetSpawnPos();
	bool IsInSpawnZone();
	void SetSpeed(float speedScaleFactor);

	//Pure virtual functions to be implemented by the visualisation
	virtual void Vis(const int& FPS)=0;
	virtual Projectile * CreateProjectile() = 0;
	virtual ~Vehicle();
protected:
	int vehicleType=0;
	// Lane -- used to determine whether a car is driving left or right
	// 		-- also used to determine the y position of a vehicle
	int m_lane=0;
	// Ordinal Number : which ordinal rank does this car initially have on this lane?
	// e.q.: It's the 4th vehicle on this lane. ordinalNumer=4.
	int ordinalNumber=0;
	// Angle -- used for driving left or right;
	int angle = 0;
	float carWidth=0.26875;
	float carHeight=0.15625;
	float truckWidth=0.80625;
	float truckHeight=0.19375;
	Rect borderRect;
	int FPS=60; // Default 60, it gets overridden almost instantaneously. Just a safe value to begin with.
	bool inSpawnZone= false;
	float speed=0;
};
}
#endif /* SRC_VEHICLE_H_ */
