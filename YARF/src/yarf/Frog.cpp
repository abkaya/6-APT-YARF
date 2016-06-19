/*
 * Frog.cpp
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#include "Frog.h"

namespace yarf{
Frog::Frog(){
	position.x=gameAxisWidth/2-width/2;
	position.y=gameAxisHeight-1.1*width;
	position.w=width;
	position.h=height;
}

void Frog::Kill(){
	position.theta=0;
	position.x=gameAxisWidth/2-width/2;
	position.y=gameAxisHeight-1.1*width;

}

int Frog::MoveToDirection(int direction)
{
	testPosition.x = position.x;
	testPosition.y = position.y;
	testPosition.w = position.w;
	testPosition.h = position.h;
	switch (direction)
	{
	case 0:                           // North
		testPosition.y -= jumpDistance;
		if (IsInTerrain(testPosition) == true)
		{
			position.y -= jumpDistance;    // move up
		}
		position.theta = 0;
		frogDirection = 0;
		break;
	case 1:                           // East
		testPosition.x += jumpDistance;
		if (IsInTerrain(testPosition) == true)
		{
			position.x += jumpDistance;    // move to the right;
		}
		position.theta = 90;
		frogDirection = 1;
		break;
	case 2:                           // South
		testPosition.y += jumpDistance;
		if (IsInTerrain(testPosition) == true)
		{
			position.y += jumpDistance;    // move down
		}
		position.theta = 180;
		frogDirection = 2;
		break;
	case 3:                           // West
		testPosition.x -= jumpDistance;
		if (IsInTerrain(testPosition) == true)
		{
			position.x -= jumpDistance;    // move to the left
		}
		position.theta = 270;
		frogDirection = 3;
		break;
	case -1:
		break;
	default:
		break;
	}
	return position.theta;
}

Frog::~Frog(){
}
}
