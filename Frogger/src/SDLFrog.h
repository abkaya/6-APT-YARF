/*
 * SDLFrog.h
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#ifndef SRC_SDLFROG_H_
#define SRC_SDLFROG_H_

//#include <SDL.h>
//#include <SDL_image.h>
#include <iostream>
#include <string>
#include "Frog.h"


// Extend class Frog to the extent of its possibilities. Public will be public, but privates remain private and so on.
class SDLFrog: public Frog
{
public:
	SDLFrog();
	void Vis();
	virtual ~SDLFrog();
};

#endif /* SRC_SDLFROG_H_ */
