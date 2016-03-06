/*
 * SDLFact.cpp
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#include <iostream>
#include "SDLFact.h"
#include "SDLFrog.h"
#include "SDLWindow.h"

using namespace std;

SDLFact::SDLFact()
{
}

Frog* SDLFact::CreateFrog()
{
	return new SDLFrog();
}

Window* SDLFact::CreateWindow()
{
	return new SDLWindow();
}

SDLFact::~SDLFact()
{
	cout << "SDLFact.~SDLFact():\n\t\tDestroyed an SDLFact object. [INDIRECT]"
			<< endl;
}
