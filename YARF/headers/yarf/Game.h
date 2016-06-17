/*
 * Game.h
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#ifndef SRC_GAME_H_
#define SRC_GAME_H_
#include "Fact.h"

namespace yarf
{
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
	Bullet* BulletF;

	const int FPS;
	const double DELAY_TIME = 1000 / FPS;
    double    m_frameStart = 0;
    double    m_frameTime  = 0;
};
}
#endif /* SRC_GAME_H_ */