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

using namespace std;

class Vehicle
{
public:
	Vehicle();
	virtual void Vis(const int& FPS)=0;
	virtual void Move(const int& FPS)=0;
	virtual Rect GetRect()=0;
	virtual int GetLane()=0;
	virtual int IsInTerrain()=0;
	virtual void SetDirection()=0;
	virtual void SetInitPos()=0;
	virtual void SetSpawnPos()=0;
	virtual Projectile * CreateProjectile() = 0;
	virtual void SetPauseMovements(bool pause_movements)=0;
	virtual bool IsInSpawnZone()=0;
	virtual ~Vehicle();
};

#endif /* SRC_VEHICLE_H_ */
