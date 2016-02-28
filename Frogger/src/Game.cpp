/*
 * Game.cpp
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#include "Game.h"
#include "Fact.h"
#include "Frog.h"
#include <iostream>
using namespace std;

Game::Game(Fact* F_)
{
	F = F_;
}

void Game::Start()
{
	cout << "Game.Start():\tGame started with a pass by reference Factory F." << endl;
	FrogF = F->CreateFrog();
	cout << "Game.Start():\tFrog has been called through the Abstract Factory F.\n\t\tThis code has no idea whether SDL or another library is being used." << endl;
	FrogF->Vis();
}

void Game::Stop(){
	FrogF->~Frog();
	cout << "Game.Stop():\tGame stopped, Called destructors in opposite order." << endl;
}

Game::~Game()
{
	//Calling the FrogG Destructor in her
	cout << "Game.~Game():\tDestroyed a Game object" << endl;
}

