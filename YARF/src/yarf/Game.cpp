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

Game::Game(Fact * factory) :
		TPS(60)
{
	F = factory;

}
void Game::Start()
{
	cout << "Game.Start():\tGame started with a pass by reference Factory F."
			<< endl;

	// It's important to create the Window before Creating any other entity, because that'll
	// lead to nullpointer Windows/Renderer whilst using these to display other entities

	cout
			<< "Game.Start():\tWindow has been called through the Abstract Factory F.\n\t\tThis code has no idea whether SDL or another library is being used."
			<< endl;

	if(F->IsRunning())
		InitEntities();
	while (F->IsRunning())
	{
		m_frameStart = F->GetTicks();

		// Events will be caught within (1000/FPS)ms
		Update();

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

// Most of the Entities need the renderer, so it makes sense to initialise entities
// after the renderer has initialised succesfully
// We will check on that, using F->IsRunning()
void Game::InitEntities()
{

	FrogF = F->CreateFrog(bullet_list);

	//Seeding the random generator in order to generate a random type of car for ever time the program is ran:
	//This is done using the current time string
	srand(static_cast<unsigned int>(time(0)));

	//We need a way to denote the ordinal number
	//"this is the n'th vehicle on this lane"
	//We want 3 vehicles on each lane by default.
	//there are 8 lanes, for any gives Width or Height of the window.

	//spawn 1 vehicle on each lane, then continue doing so, but moving on the
	//x-scale by moving the ordinalnumber up.
	int k = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			vehicle_list.push_back(F->CreateVehicle(true, i, j));
			//check for colliding cars, because we just created a new vehicle.
			RemoveCollidingVehicle(true);
			k++;
		}
	}
}

void Game::Update()
{
	F->HandleVisEvents();
	BulletVehicleCollision();		//comes before frog><vehicle collision
									//which makes the green forceshield more effective
	DetectCollision();				//collision between frog><vehicles
	IsVehicleInTerrain();
	IsBulletInTerrain();
	ManageVehicleNumber();
		UpdateFrogStates();
	F->RenderClear();
	FrogF->MoveToDirection(m_direction);
	FrogF->Vis(m_direction, m_leaping, TPS);

	for (vehicle_it_1 = vehicle_list.begin();
			vehicle_it_1 != vehicle_list.end(); ++vehicle_it_1)
	{
		(*vehicle_it_1)->Vis(TPS);
		(*vehicle_it_1)->Move();
	}
	F->RenderPresent();
}

void Game::UpdateFrogStates()
{
	FrogStates = F->GetFrogStates();
	m_direction = FrogStates.x;
	m_leaping = FrogStates.y;
	switch ((int)(FrogStates.w))
	{
	case 1:
		FrogF->CreateBullet();		//red bullet
		break;
	case 4:
		m_theta = 0;
		for (m_theta = 0; m_theta < 360; m_theta = m_theta + 10) //electric bullet every 10°
		{
			//"4" is the bullet/frog direction parameter, this time used to denote the electric bullet type
			FrogF->CreateBullet(4, m_theta);
		}
		break;
	case 5:
		m_theta = 0;
		for (m_theta = 0; m_theta < 360; m_theta = m_theta + 36) //forceshield bullet every 36°
		{
			//"5" is the bullet/frog direction parameter, this time used to denote the green defence bullet type
			FrogF->CreateBullet(5, m_theta);
		}
		break;
	default:
		break;
	}


}

void Game::DetectCollision()
{
	// Because from now on vehicles will be destroyed, we're going to check whether or not the  object exists.
	for (vehicle_it_1 = vehicle_list.begin();
			vehicle_it_1 != vehicle_list.end(); ++vehicle_it_1)
	{
		leftA = FrogF->GetRect().x;
		rightA = FrogF->GetRect().x + FrogF->GetRect().w;

		leftB = (*vehicle_it_1)->GetRect().x;
		rightB = (*vehicle_it_1)->GetRect().x + (*vehicle_it_1)->GetRect().w;

		topA = FrogF->GetRect().y;
		bottomA = FrogF->GetRect().y + FrogF->GetRect().h;

		topB = (*vehicle_it_1)->GetRect().y;
		bottomB = (*vehicle_it_1)->GetRect().y + (*vehicle_it_1)->GetRect().h;

		if (leftA < rightB && rightA > leftB && topA < bottomB
				&& bottomA > topB)
			FrogF->Kill();
	}
}

bool Game::IsSpawnAvailable(int lane)
{
	for (auto* vehicle : vehicle_list)
	{
		if (vehicle->GetLane() == lane && vehicle->IsInSpawnZone() == true)
		{
			return false;
		}
	}
	return true;
}

void Game::RemoveCollidingVehicle(bool initial_spawns)
{
	//check whether or not vehicle overlaps with any of the other vehicles.
	//Horizontal collision detection suffices.
	//Two vehicles are not allowed to stick to each other either, hence the
	// ...x -+ 20*m_widthScaleFactor

	for (vehicle_it_2 = vehicle_list.begin();
			vehicle_it_2 != vehicle_list.end()
					&& vehicle_it_2 != --vehicle_list.end(); ++vehicle_it_2)
	{
		if ((*vehicle_it_2)->GetLane() == (*(--vehicle_list.end()))->GetLane())
		{
			leftA = (*(--vehicle_list.end()))->GetRect().x;	//- 70*m_widthScaleFactor;
			rightA = (*(--vehicle_list.end()))->GetRect().x
					+ (*(--vehicle_list.end()))->GetRect().w;//+ 70*m_widthScaleFactor;

			leftB = (*vehicle_it_2)->GetRect().x;
			rightB = (*vehicle_it_2)->GetRect().x
					+ (*vehicle_it_2)->GetRect().w;

			if (leftA < rightB && rightA > leftB)
			{

				delete (*(--vehicle_list.end()));
				vehicle_list.erase(--vehicle_list.end()); //erase calls the destructor before removing it from the list;
			}
		}
	}
}

void Game::SpawnVehicle(int lane)
{
	if (IsSpawnAvailable(lane) == true)
	{
		vehicle_list.push_back(F->CreateVehicle(false, lane, -1));
		RemoveCollidingVehicle(false);
	}
}

void Game::IsVehicleInTerrain()
{
	vehicle_it_1 = vehicle_list.begin();
	while (vehicle_it_1 != vehicle_list.end())
	{
		if ((*vehicle_it_1)->IsInTerrain() != -1)
		{
			//IsInTerrain() returns the car that hit the edge its lane number, so the newly
			//created car is put on that same lane.
			F->CreateVehicle(false, (*vehicle_it_1)->GetLane(), -1);
			delete ((*(vehicle_it_1)));
			//remove pointer to removed vehicle from list and add continue checking other vehicles
			//Make sure to not remain on that iterator value, because it's not
			//leading anywhere right now.
			vehicle_list.erase(vehicle_it_1++);
			//check for colliding vehicles, because we just created a new vehicle.
			RemoveCollidingVehicle(false);
		}
		else
			vehicle_it_1++; //continue checking the next car
	}
}

void Game::ManageVehicleNumber()
{
	int i; // lane number
	int v = 0; //number of vehicles
	for (i = 0; i < 8; i++)
	{
		v = 0;
		for (auto* vehicle : vehicle_list)
		{
			if (vehicle->GetLane() == i)
				v++;
		}
		if (v < 3)
			SpawnVehicle(i);
	}
}

/*Bullets
 * auto iteration referenced and found in: §20.3.1, p585 of The C++ Programming
 * Language (4th edition) by Bjarne Stroustrup
 */

void Game::BulletVehicleCollision()
{
	bool collided = false;
	for (auto* vehicle : vehicle_list)
	{
		for (auto* bullet : bullet_list)
		{
			if (collided == false)
			{
				leftA = vehicle->GetRect().x;
				rightA = vehicle->GetRect().x + vehicle->GetRect().w;

				leftB = bullet->GetRect().x;
				rightB = bullet->GetRect().x + bullet->GetRect().w;

				topA = vehicle->GetRect().y;
				bottomA = vehicle->GetRect().y + vehicle->GetRect().h;

				topB = bullet->GetRect().y;
				bottomB = bullet->GetRect().y + bullet->GetRect().h;

				if (leftA < rightB && rightA > leftB && topA < bottomB
						&& bottomA > topB)
				{
					delete (vehicle);
					vehicle_list.remove(vehicle);
					delete (bullet);
					bullet_list.remove(bullet);
					collided = true;
					score += 10;
					cout << "Score: " << score << endl;
				}
			}
		}
	}
}

void Game::IsBulletInTerrain()
{
	bullet_it = bullet_list.begin();
	while (bullet_it != bullet_list.end())
	{
		if ((*(bullet_it))->IsInTerrain((*(bullet_it))->GetRect()) == false)
		{
			delete ((*(bullet_it)));
			bullet_list.erase(bullet_it++);
		}
		else
			bullet_it++;
	}
}

void Game::Stop()
{
	//Deleting the bullets first
	 for (auto* bullet : bullet_list)
	 {
	 delete (bullet);
	 bullet_list.remove(bullet);
	 }

	 //Delete all vehicles
	 for (auto* vehicle : vehicle_list)
	 {
	 delete (vehicle);
	 vehicle_list.remove(vehicle);
	 }

	 //Delete the Frog
	 delete (FrogF);

	 //Call for the SDL Renderer and Window to be Deleted

}
Game::~Game()
{
}

}
