/*
 * Game.h
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#ifndef SRC_GAME_H_
#define SRC_GAME_H_
#include "Fact.h"
#include "Frog.h"
#include "Window.h"

class Game
{
public:
	Game(Fact*);
	void Start();
	void Stop();
	~Game();
private:
	Fact* F;
	Frog* FrogF;
	Window* WindowF;
};

#endif /* SRC_GAME_H_ */
