/*
 * Border.h
 *
 *  Created on: 8 Mar 2016
 *      Author: abdil
 */

#ifndef SRC_TERRAIN_H_
#define SRC_TERRAIN_H_

#include <iostream>

using namespace std;

class Terrain
{
public:
	Terrain();
	virtual void Vis() = 0;
	virtual ~Terrain();
};

#endif /* SRC_TERRAIN_H_ */
