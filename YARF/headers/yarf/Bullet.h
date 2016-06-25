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
	float FPS=60; 	//default | initial behaviour -- is updated before the Move() is called
	bool calibratedTPS=false;
	float theta=0;
	float radius=0;
	float initTheta=0; //used to sway between theta degrees.
	float degreeSway=1;
	float clockwise=1;
	Rect *frogRect=nullptr;
	Rect staticCoords;
		// Rect to share
	Rect returnRect;

	float bulletSpeed=0.07;
	//direction: 0: north, 1: east, 2: south, 3: west
	int frogDirection=0;
	//double widthScaleFactor;
	Rect testPosition;
	double width = 0.075;
	double height = 0.075;

};
}
#endif /* SRC_BULLET_H_ */

