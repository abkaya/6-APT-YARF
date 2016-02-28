/*
 * SDLFrog.cpp
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#include <iostream>
#include "SDLFrog.h"

using namespace std;

SDLFrog::SDLFrog()
{
}

void SDLFrog::Vis()
{
	cout << "SDLFrog:\tVisualise FROG IN SDL" << endl;
}

SDLFrog::~SDLFrog()
{
	cout << "SDLFrog.~SDLFrog():\n\t\tDestroyed an SDLFrog object. [INDIRECT]" << endl;
}
