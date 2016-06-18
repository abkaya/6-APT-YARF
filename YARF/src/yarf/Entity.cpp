/*
 * Entity.cpp
 *
 *  Created on: 17 Jun 2016
 *      Author: abdil
 */

#include "Entity.h"

namespace yarf
{

Entity::Entity()
{
}

bool Entity::IsInTerrain(Rect testPosition)	//false if entity is outside the game axis[0,4]x[0,3]
{
	if ((testPosition.x < -position.w / 2)
			|| (testPosition.x + testPosition.w) > (gameAxisWidth)
			|| (testPosition.y < -position.h/2)
			|| (testPosition.y + testPosition.h)
					> (gameAxisHeight + position.w))
	{
		return false;
	}
	else
	{
		return true;
	}
}

Rect Entity::GetRect(){
	return position;
}

Entity::~Entity()
{
}

} /* namespace yarf (game) */

