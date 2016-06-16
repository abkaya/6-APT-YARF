/*
 * main.cpp
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 *
 * SDL2 References:
 *              [1] SDL in General:
 *                  + http://lazyfoo.net/tutorials/SDL
 *                      + SDL Game Development by Shaun Mitchell, Packt Publishing
 *                      + https://wiki.libsdl.org
 *              [2] Regulating Frame Rate
 *                      + http://lazyfoo.net/tutorials/SDL/25_capping_frame_rate/index.php
 *
 *
 * License on graphics: CC0 1.0 Universal (CC0 1.0) - Public Domain Dedication
 * https://creativecommons.org/publicdomain/zero/1.0/
 *
 * Graphics by Kenney Vleugels (www.kenney.nl)
 *
 */

#include <iostream>
#include "SDLFact.h"
#include "SDLFrog.h"
#include "Game.h"

using namespace std;
int main(int argc, char * args[])
{
	Game::Fact * F = new SDL::SDLFact();

	// Game(*F);
	Game::Game G(F);
	G.Start();

	// G.Stop();
	G.~Game();
	F->~Fact();
	cout << "main:\t\tObjects destroyed in opposite order of creation." << endl;
	return 0;
}

/*Resources for graphics and sound
 * Public domain resources!
 */
