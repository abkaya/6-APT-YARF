/*
 * main.cpp
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 *
 * SDL2 References:
 * 		[1] SDL in General:
 * 		    + http://lazyfoo.net/tutorials/SDL
 * 			+ SDL Game Development by Shaun Mitchell, Packt Publishing
 * 			+ https://wiki.libsdl.org/
 * 		[2] Regulating Frame Rate
 * 			+ http://lazyfoo.net/tutorials/SDL/25_capping_frame_rate/index.php
 */

#include <iostream>
#include "SDLFact.h"
//#include "SDLFrog.h"
//#include "SDLWindow.h"
#include "Game.h"
#include <SDL.h>
using namespace std;


int main(int argc, char* args[])
{

	Fact *F = new SDLFact();
	//Game(*F);

	Game G(F);
	G.Start();
	G.Stop();

	G.~Game();
	F->~Fact();

	cout << "main:\t\tObjects destroyed in opposite order of creation." << endl;

	return 0;
}

/*Resources for graphics and sound
 * Public domain resources!
 */

