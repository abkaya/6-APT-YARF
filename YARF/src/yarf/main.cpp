/*
 * main.cpp
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 *
 * C++ References:
 * 				[0] The C++ Programming Language (4th edition) by Bjarne Stroustrup
 * SDL2 References:
 *              [1] SDL in General:
 *                  + http://lazyfoo.net/tutorials/SDL
 *                  + SDL Game Development by Shaun Mitchell, Packt Publishing
 *                  + https://wiki.libsdl.org
 *              [2] Regulating Frame Rate
 *                  + http://lazyfoo.net/tutorials/SDL/25_capping_frame_rate/index.php
 *
 * Graphics by Kenney Vleugels (www.kenney.nl) ---> Manipulated graphics.
 * License on graphics: CC0 1.0 Universal (CC0 1.0) - Public Domain Dedication
 * https://creativecommons.org/publicdomain/zero/1.0/
 *
 *
 */

#include <iostream>
#include "SDLFact.h"
#include "SDLFrog.h"
#include "Game.h"

using namespace std;
int main(int argc, char * args[])
{
	yarf::Fact * F = new yarf_sdl::SDLFact();
	yarf::Game * G= new yarf::Game(F);
	G->Start();
	G->Stop();
	delete(F);
	delete(G);
	return 0;
}

/*Resources for graphics and sound
 * Public domain resources!
 */
