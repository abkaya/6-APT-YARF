/*
 * Game.cpp
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#include "Game.h"
#include "Fact.h"
#include "Frog.h"
#include "Window.h"
#include <iostream>

using namespace std;

Game::Game(Fact* F_)
{
	F = F_;
}

void Game::Start()
{
	cout << "Game.Start():\tGame started with a pass by reference Factory F."
			<< endl;

	//It's important to create the Window before Creating any other entity, because that'll
	//lead to nullpointer Windows/Renderer whilst using these to display other entities
	WindowF = F->CreateWindow();
	WindowF->Vis();
	cout
			<< "Game.Start():\tWindow has been called through the Abstract Factory F.\n\t\tThis code has no idea whether SDL or another library is being used."
			<< endl;

	FrogF = F->CreateFrog();
	cout
			<< "Game.Start():\tFrog has been called through the Abstract Factory F.\n\t\tThis code has no idea whether SDL or another library is being used."
			<< endl;
    FrogF->Vis();

	WindowF->Close();
}

void Game::Stop()
{
	FrogF->~Frog();
	cout << "Game.Stop():\tGame stopped, Called destructors in opposite order."
			<< endl;

	WindowF->~Window();
}

Game::~Game()
{
	cout << "Game.~Game():\tDestroyed a Game object" << endl;
}

