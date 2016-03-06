/*
 * Fact.h
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#ifndef SRC_FACT_H_
#define SRC_FACT_H_

#include <string>
#include "Frog.h"
#include "Window.h"
using namespace std;

class Fact
{
public:
	Fact();
	virtual Frog* CreateFrog()=0;
	virtual Window* CreateWindow()=0;
	virtual ~Fact();
};




#endif /* SRC_FACT_H_ */
