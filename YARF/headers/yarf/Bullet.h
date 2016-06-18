/*
 * Bullet.h
 *
 *  Created on: 25 Apr 2016
 *      Author: abdil
 */

#ifndef SRC_BULLET_H_
#define SRC_BULLET_H_

#include <iostream>
#include "Rect.h"
#include "Entity.h"

namespace yarf
{

class Bullet : public Entity
{
public:
	Bullet();
	virtual void Vis(const int& FPS)=0;
	void Move();
	virtual ~Bullet();
protected:
	int FPS=60; 	//default | initial behaviour -- is updated almost instantaneously. It's a safe value
	float theta=0;
	int radius=0;
	int initTheta=0; //used to sway between theta degrees.
	int clockwise=1;
	Rect *frogRect;
	Rect staticCoords;
		// Rect to share
	Rect returnRect;

	float bulletSpeed=0.093;
	//direction: 0: north, 1: east, 2: south, 3: west
	int frogDirection;
	//double widthScaleFactor;
	Rect testPosition;
	double width = 0.075;
	double height = 0.075;

};
}
#endif /* SRC_BULLET_H_ */

