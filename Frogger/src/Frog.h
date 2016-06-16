/*
 * Frog.h
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#ifndef SRC_FROG_H_
#define SRC_FROG_H_

#include <iostream>
#include "Rect.h"
#include "Bullet.h"

namespace Game
{
class Frog
{
public:
	Frog();
	virtual void Vis(int direction, int leaping, const int & FPS) = 0;
	virtual void Leap(int & direction) = 0;
	virtual bool IsInTerrain(Rect entityRect) = 0;
	virtual int SetDest(int direction, int & xCoord, int & yCoord) = 0;
	virtual void Kill()=0;
	virtual Rect GetRect(int frog_or_bullet) = 0;
	virtual void CreateBullet()=0;
	virtual void CreateBullet(int direction, int theta)=0;
	virtual ~Frog();
protected:
	int potato=0;

};
}
#endif /* SRC_FROG_H_ */


