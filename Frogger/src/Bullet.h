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

namespace Game
{

class Bullet
{
public:
	Bullet();
	virtual void Vis(const int& FPS)=0;
	virtual void Move(const int& FPS)=0;
	virtual bool IsInTerrain()=0;
	virtual Rect GetRect()=0;
	virtual ~Bullet();
protected:
	int m_theta=0;
	int m_radius=0;
	int m_initTheta=0; //used to sway between theta degrees.
	int m_clockwise=1;
	Rect *m_frogRect;
	Rect m_staticCoords;
		// Rect to share
	Rect m_returnRect;

	int m_bulletSpeed=15;

	//direction: 0: north, 1: east, 2: south, 3: west
	int m_frogDirection;
	int m_bulletSrcX = 0;
	int m_bulletSrcY = 0;
	double m_bulletWidth = 12;
	double m_bulletHeight = 12;

	double m_windowWidth;
	double m_windowHeight;
	double m_heightScaleFactor;
};
}
#endif /* SRC_BULLET_H_ */

