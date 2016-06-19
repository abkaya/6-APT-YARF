/*
 * Bullet.cpp
 *
 *  Created on: 25 Apr 2016
 *      Author: abdil
 */

#include "Bullet.h"
#include <math.h>
#define PI 3.14159265

namespace yarf
{
Bullet::Bullet()
{
}

void Bullet::Move()
{
	if (calibratedTPS == false)
	{
		bulletSpeed = bulletSpeed * (60 / FPS);
		degreeSway = degreeSway * (60 / FPS);
		clockwise=degreeSway;
		calibratedTPS = true;
	}
	switch(frogDirection)
	{
	case 0:                           // Sinusoidal red bullet : North
		theta = theta + bulletSpeed;
		position.y -= bulletSpeed / 2;
		//sinusoidal sway between half of frog width
		position.x = (frogRect->w / 2) * sin((theta * PI) * 2) + staticCoords.x; //Coords of Frog upon bullet being shot
		break;
	case 1:                           // Sinusoidal red bullet : East
		theta = theta + bulletSpeed;
		position.x += bulletSpeed / 2;
		//sinusoidal sway between half of frog width
		position.y = (frogRect->w / 2) * sin((theta * PI) * 2) + staticCoords.y; //Coords of Frog upon bullet being shot
		break;
	case 2:                           // Sinusoidal red bullet : South
		theta = theta + bulletSpeed;
		position.y += bulletSpeed / 2;
		//sinusoidal sway between half of frog width
		position.x = (frogRect->w / 2) * sin((theta * PI) * 2) + staticCoords.x; //Coords of Frog upon bullet being shot
		break;
	case 3:                           // Sinusoidal red bullet : West
		theta = theta + bulletSpeed;
		position.x -= bulletSpeed / 2;
		//sinusoidal sway between half of frog width
		position.y = (frogRect->w / 2) * sin((theta * PI) * 2) + staticCoords.y; //Coords of Frog upon bullet being shot
		break;

		// The bullet behaves in such way that it sways between +2 degree and -2 degree
		// of the initial theta m_initTheta.
		// I have set the bullet to be called from 0 to 360 degrees, every 10 degrees
		// The result is 36 blue bullet, each swaying +2 and -2 degree, whilst the radius
		// is growing with the bulletSpeed.
		// and this is being updated every time Move() is called.
	case 4:
		//growing radius
		radius = radius + bulletSpeed / 2;
		//logic for the bullet to know when to sway the other way
		if (theta > (initTheta + 2) && clockwise == degreeSway)
			clockwise = -degreeSway;
		if (theta < (initTheta - 2) && clockwise == -degreeSway)
			clockwise = degreeSway;
		theta = theta + clockwise;
		position.x = staticCoords.x + radius * cos(theta * (PI / 180));
		position.y = staticCoords.y + radius * sin(theta * (PI / 180));
		break;
	case 5:
		theta++;
		position.x = frogRect->x + (0.33 * (frogRect->w))
				+ frogRect->w * 0.65 * cos((int) (theta) % 360);
		position.y = frogRect->y + (0.30 * (frogRect->h))
				+ frogRect->h * 0.65 * sin((int) (theta) % 360);
		break;
	case -1:
		break;
	default:
		break;
	}
}

Bullet::~Bullet()
{
}
}
