/*
 * main.cpp
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#include <iostream>
#include "SDLFact.h"
#include "SDLFrog.h"
#include "Game.h"
#include <SDL.h>
#include <stdio.h>
using namespace std;

#undef main // MAGIC ?

int main()
{

	Fact *F = new SDLFact();
	//Game(*F);

	Game G(F);
	G.Start();
	G.Stop();

	G.~Game();
	F->~Fact();

	cout << "main:\t\tObjects destroyed in opposite order of creation." << endl;



/*end test
 *
 */
	return 0;
}

/*Resources for graphics and sound
 * Public domain resources!
 */
