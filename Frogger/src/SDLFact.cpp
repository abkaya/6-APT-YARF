/*
 * SDLFact.cpp
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#include <iostream>
#include "SDLFrog.h"
#include "SDLFact.h"

using namespace std;

SDLFact::SDLFact() {

}

Frog* SDLFact::CreateFrog() {
	return new SDLFrog();
}

SDLFact::~SDLFact() {
	cout << "SDLFact.~SDLFact():\n\t\tDestroyed an SDLFact object. [INDIRECT]" << endl;
}
