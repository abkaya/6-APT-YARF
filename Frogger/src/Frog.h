/*
 * Frog.h
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#ifndef SRC_FROG_H_
#define SRC_FROG_H_

#include <string>
#include <iostream>
using namespace std;

class Frog
{
public:
	Frog();
	virtual void Vis()=0;
	virtual ~Frog();
};

#endif /* SRC_FROG_H_ */
