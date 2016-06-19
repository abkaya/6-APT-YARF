/*
 * Frog.h
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#ifndef SRC_FROG_H_
#define SRC_FROG_H_

#include <iostream>
#include "Fact.h"
#include "Rect.h"
#include "Bullet.h"
#include "Entity.h"

namespace yarf
{
class Frog: public Entity
{
public:
	Frog();
	//non-virtual functions  || purely game related
	int MoveToDirection(int direction);
	void Kill();

	//pure virtual functions
	virtual void Vis(int direction, int leaping, const int & FPS) = 0;
	virtual void LeapVis(int & direction)=0;
	virtual void CreateBullet()=0;
	virtual void CreateBullet(int direction, int theta)=0;
	virtual ~Frog(); 			//doesn't have to be pure virtual.
protected:
	int frogDirection=0; 		//0 north, 1 east, 2 south, 4 west
private:
	Rect testPosition;
	float width=0.2;
	float height=0.1875;
	float jumpDistance=0.3;
};
}
#endif /* SRC_FROG_H_ */


