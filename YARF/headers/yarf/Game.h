/*
 * Game.h
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#ifndef SRC_GAME_H_
#define SRC_GAME_H_
#include "Fact.h"
//for random function and seeding it with ctime
#include <cstdlib>
#include <ctime>

namespace yarf
{
class Game
{
public:
	Game(Fact*);
	void Start();
	void Stop();
	void Update();				//will used as an update game function
								//old render has to stay though
	void InitEntities();
	void IsVehicleInTerrain();
	void IsBulletInTerrain();
	void RemoveCollidingVehicle(bool initial_spawns);
	void BulletVehicleCollision();
	void DetectCollision();
	bool IsSpawnAvailable(int lane);
	void ManageVehicleNumber();
	void SpawnVehicle(int lane);
	void UpdateFrogStates();
	~Game();
private:
	yarf::Fact* F = nullptr;
	yarf::Frog* FrogF = nullptr;

	const int TPS;
	const double DELAY_TIME = 1000 / TPS;
	double m_frameStart = 0;
	double m_frameTime = 0;

	//collision detection left and right
	float leftA = 0, rightA = 0, leftB = 0, rightB = 0, bottomA = 0, topA = 0,
			bottomB = 0, topB = 0;

	bool m_spawnAvailable = false;

	list<yarf::Bullet *> bullet_list;
	list<yarf::Bullet *>::iterator bullet_it;

	//using a list of vehicles to conveniently delete and create vehicles
	list<yarf::Vehicle *> vehicle_list;
	list<yarf::Vehicle *>::iterator vehicle_it_1;

	//second iterator used to check on colliding cars upon creation.
	list<yarf::Vehicle *>::iterator vehicle_it_2;

	//int m_tempDir;
	int m_theta = 0;
	int score = 0;
	Rect FrogStates; //x=direction, y=leaping, w= shooting(1(red), 4(blue), 5(green)), h=unused)

	int m_direction = 0;
	int m_leaping = 0;

};
}
#endif /* SRC_GAME_H_ */
