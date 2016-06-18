/*
 * Game.cpp
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#include "Game.h"
#include <iostream>

namespace yarf
{

Game::Game(Fact * factory) : FPS(60)
{
    F = factory;
}
void Game::Start()
{
    cout << "Game.Start():\tGame started with a pass by reference Factory F." << endl;

    // It's important to create the Window before Creating any other entity, because that'll
    // lead to nullpointer Windows/Renderer whilst using these to display other entities
    FrogF = F -> GetFrog();

    cout << "Game.Start():\tWindow has been called through the Abstract Factory F.\n\t\tThis code has no idea whether SDL or another library is being used."
         << endl;

    while(F->IsRunning()){
    	m_frameStart = F->GetTicks();

        // Events will be caught within (1000/FPS)ms https://wiki.libsdl.org/SDL_Scancode
    	F->Vis();

        // The time needed to execute the 3 previous functions is taken into consideration
        // when calculating the appropriate delay in order to reach the aimed FPS
        m_frameTime = F->GetTicks() - m_frameStart;
        if (m_frameTime < DELAY_TIME)
        {
            F->Delay((int) (DELAY_TIME - m_frameTime));
        }
    }
    F->Resize();
    // WindowF->Close(); << Do NOT call this from Game. SDLWindow can handle it internally. Consider removing the function
}
void Game::Stop()
{
    F->Resize();
}
Game::~Game()
{
}

}
