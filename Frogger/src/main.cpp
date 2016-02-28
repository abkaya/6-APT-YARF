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
using namespace std;

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
}
