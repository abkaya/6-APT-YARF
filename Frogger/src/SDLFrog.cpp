/*
 * SDLFrog.cpp
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#include "SDLFrog.h"
#include "SDLWindow.h"
using namespace std;
#define debug

SDLFrog::SDLFrog()
{
#ifdef debug
	if (g_pWindow != 0)
		cout << "SDLFrog:\tAddress to the SDL Window: " <<  g_pWindow << endl;
#endif
}

void SDLFrog::Vis()
{
	cout << "SDLFrog.Vis():\tVisualise FROG IN SDL" << endl;
}

SDLFrog::~SDLFrog()
{
	cout << "SDLFrog.~SDLFrog():\n\t\tDestroyed an SDLFrog object. [INDIRECT]"
			<< endl;
}
