/*
 * Projectile.h
 *
 *  Created on: 21 Mar 2016
 *      Author: abdil
 */

#ifndef SRC_PROJECTILE_H_
#define SRC_PROJECTILE_H_

#include <iostream>

class Projectile
{
public:
	Projectile();
	virtual void Vis(const int& FPS)=0;
	virtual void Move(const int& FPS)=0;
	virtual void TargetAngle()=0;
	virtual ~Projectile();
};

#endif /* SRC_PROJECTILE_H_ */
