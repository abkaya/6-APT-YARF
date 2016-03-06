/*
 * SDLFact.h
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#ifndef SRC_SDLFACT_H_
#define SRC_SDLFACT_H_

#include <string>
#include "Fact.h"
#include "Frog.h"
#include "Window.h"


// Extend class Fact to the extent of its possibilities. Public will be public, but privates remain private and so on.
class SDLFact: public Fact
{
public:
	SDLFact();
	Frog* CreateFrog();
	Window* CreateWindow();
	virtual ~SDLFact();
};

#endif /* SRC_SDLFACT_H_ */
