/*
 * Rect.h
 *
 *  Created on: 14 Mar 2016
 *      Author: abdil
 *
 *  Holds the x-coord, y-coord, width, height and direction faced in degrees; theta, t
 */

#ifndef SRC_RECT_H_
#define SRC_RECT_H_

class Rect
{
public:
	Rect();
	virtual ~Rect();
	float x=0,y=0,w=0,h=0;
	int theta=0;
};

#endif /* SRC_RECT_H_ */
