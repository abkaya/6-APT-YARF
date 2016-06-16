/*
 * SDLFact.cpp
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#include <iostream>
#include "SDLFact.h"
#include "SDLFrog.h"
#include "SDLVehicle.h"
#include "SDLTerrain.h"

namespace SDL
{
SDLFact::SDLFact() :
		FPS(60)
{
	//Initialisation of the window happens here
	cout << "SDLWindow:\tMake WINDOW IN SDL" << endl;
	if (Init("Frogs R Us", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE))
	{
		m_bRunning = true;
	}
	//Then we visualise
	Vis();
	m_direction = 0;
	cout
			<< "Game.Start():\tFrog has been called through the Abstract Factory F.\n\t\tThis code has no idea whether SDL or another library is being used."
			<< endl;
}
bool SDLFact::Init(const char * title, int xpos, int ypos, int height,
		int width, int flags)
{
	// initialise SDL -- including SDL_INIT_... HAPTIC,AUDIO,VIDEO,TIMER,JOYSTICK
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		// if succeeded create our window
		g_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);

		// if the window creation succeeded create our renderer
		if (g_pWindow != 0)
		{
			// https://wiki.libsdl.org/SDL_CreateRenderer
			m_pRenderer = SDL_CreateRenderer(g_pWindow, -1,
					SDL_RENDERER_ACCELERATED);

			// renderer init success
			if (m_pRenderer != 0)
			{
				SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
				// Call InitTextures only after the Renderer is created
				InitTextures();
				// Call InitEntities only after the Renderer exists.
				InitEntities();
			}
			else
			{
				// renderer init fail
				return false;
			}
		}
	}
	else
	{
		return false;    // sdl could not initialize
	}
	return true;
}

// Create the Textures needed. Only call this function after the Renderer is created in the Init() function
void SDLFact::InitTextures()
{

	m_pTempSurface = IMG_Load(".\\gamesprite.png");
	m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pTempSurface);
	m_pTempSurface = IMG_Load(".\\frogsrusicon.png");
	SDL_SetWindowIcon(g_pWindow, m_pTempSurface);
}

// Most of the Entities need the renderer, so it makes sense to initialise entities
// after the renderer has initialised succesfully
void SDLFact::InitEntities()
{
	// Borders
	// Border for the frog = game window (WIDTH & HEIGHT)
	m_windowRect.x = 0;
	m_windowRect.y = 0;
	m_windowRect.w = WIDTH;
	m_windowRect.h = HEIGHT;

	FrogF = CreateFrog();
	TerrainF = CreateBorder();

	//Seeding the random generator in order to generate a random type of car for ever time the program is ran:
	//This is done using the current time string
	srand(static_cast<unsigned int>(time(0)));

	//We need a way to denote the ordinal number
	//"this is the n'th vehicle on this lane"
	//We want 4 vehicles on each lane by default for 640px width. From there it depends
	//on the widthScaleFactor.
	//there are 8 lanes, for any gives Width or Height of the window.

	//spawn 1 vehicle on each lane, then continue doing so, but moving on the
	//x-scale by moving the ordinalnumber up.
	int k = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4 * m_widthScaleFactor; j++)
		{
			vehicle_list.push_back(
					new SDLVehicle(m_pRenderer, m_pTexture, true, i, j,
							(rand() % 5), WIDTH, HEIGHT, m_widthScaleFactor,
							m_heightScaleFactor));
			//check for colliding cars, because we just created a new vehicle.
			RemoveCollidingVehicle(true);
			k++;
		}
	}
}

void SDLFact::DetectCollision()
{
	// Because from now on vehicles will be destroyed, we're going to check whether or not the  object exists.
	for (vehicle_it_1 = vehicle_list.begin();
			vehicle_it_1 != vehicle_list.end(); ++vehicle_it_1)
	{
		leftA = FrogF->GetRect(0).x;
		rightA = FrogF->GetRect(0).x + FrogF->GetRect(0).w;

		leftB = (*vehicle_it_1)->GetRect().x;
		rightB = (*vehicle_it_1)->GetRect().x + (*vehicle_it_1)->GetRect().w;

		topA = FrogF->GetRect(0).y;
		bottomA = FrogF->GetRect(0).y + FrogF->GetRect(0).h;

		topB = (*vehicle_it_1)->GetRect().y;
		bottomB = (*vehicle_it_1)->GetRect().y + (*vehicle_it_1)->GetRect().h;

		if (leftA < rightB && rightA > leftB && topA < bottomB
				&& bottomA > topB)
			FrogF->Kill();
	}
}

void SDLFact::IsVehicleInTerrain()
{
	vehicle_it_1 = vehicle_list.begin();
	while (vehicle_it_1 != vehicle_list.end())
	{
		if ((*vehicle_it_1)->IsInTerrain() != -1)
		{
			//4 = number of cars for the default game. It's adjusted depending on
			//window width scale factor
			//IsInTerrain() returns the car that hit the edge its lane number, so the newly
			//created car is put on that same lane.
			//static_cast<double>(4*m_widthScaleFactor) results in the highest
			//possible ordinal number, which makes new vehicles spawn at the 'start region' of a lane
			SpawnVehicle((*vehicle_it_1)->GetLane());
			delete ((*(vehicle_it_1)));
			vehicle_list.erase(vehicle_it_1++); //remove pointer to vehicle from list
			//check for colliding cars, because we just created a new vehicle.
			RemoveCollidingVehicle(false);
		}
		else
			vehicle_it_1++;
	}
}

void SDLFact::IsBulletInTerrain()
{
	bullet_it = bullet_list.begin();
	while (bullet_it != bullet_list.end())
	{
		if ((*bullet_it)->IsInTerrain() != 1)
		{
			delete ((*(bullet_it)));
			bullet_list.erase(bullet_it++);
		}
		else
			bullet_it++;
	}
}

void SDLFact::RemoveCollidingVehicle(bool initial_spawns)
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

void SDLFact::BulletVehicleCollision()
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
				}
			}
		}
	}

}

bool SDLFact::IsSpawnAvailable(int lane)
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

void SDLFact::SpawnVehicle(int lane)
{
	if (IsSpawnAvailable(lane) == true)
	{
		vehicle_list.push_back(
				new SDLVehicle(m_pRenderer, m_pTexture, false, lane,
						static_cast<double>(4 * m_widthScaleFactor),
						(rand() % 5), WIDTH, HEIGHT, m_widthScaleFactor,
						m_heightScaleFactor));
		RemoveCollidingVehicle(false);
	}
}

void SDLFact::ManageVehicleNumber()
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
		//cout <<"lane " << i << ", number of cars:" << v << ", compare: " << 2*m_widthScaleFactor<< endl;
		if (v < 2 * m_widthScaleFactor)
			SpawnVehicle(i);
	}
}

Game::Frog * SDLFact::CreateFrog()
{
	return new SDL::SDLFrog(m_pRenderer, m_pTexture, m_windowRect, WIDTH,
			HEIGHT, m_heightScaleFactor, bullet_list);
}

Terrain * SDLFact::CreateBorder()
{
	return new SDLTerrain(m_pRenderer, m_pTexture, WIDTH, HEIGHT,
			m_heightScaleFactor);
}

Game::Frog * SDLFact::GetFrog()
{
	return FrogF;
}

bool SDLFact::IsRunning()
{
	return m_bRunning;
}

int SDLFact::GetTicks()
{
	return SDL_GetTicks();
}

void SDLFact::Delay(int delay_time)
{
	SDL_Delay(delay_time);
}

void SDLFact::Vis()
{

	// Create FrogF [[AFTER]] the creation of the renderer
	// FrogF = CreateFrog();
	// BorderF = CreateBorder(sdl::g_pRenderer);
	// Regulating Frame Rate
	// -- Reference : [2] in main.cpp

	// Events will be caught within (1000/FPS)ms https://wiki.libsdl.org/SDL_Scancode
	BulletVehicleCollision();
	DetectCollision();
	HandleEvents();
	IsVehicleInTerrain();
	IsBulletInTerrain();
	ManageVehicleNumber();
	Render();

	// The time needed to execute the 3 previous functions is taken into consideration
	// when calculating the appropriate delay in order to reach the aimed FPS
}

void SDLFact::Render()
{
	// clear the window to the RenderDrawColor set in the Init function ^
	SDL_RenderClear(m_pRenderer);
	TerrainF->Vis();
	FrogF->Vis(m_direction, m_leaping, FPS);

	for (vehicle_it_1 = vehicle_list.begin();
			vehicle_it_1 != vehicle_list.end(); ++vehicle_it_1)
	{
		(*vehicle_it_1)->Vis(FPS);
	}

	// show the window
	SDL_RenderPresent(m_pRenderer);
}

void SDLFact::HandleEvents()
{
	if (SDL_PollEvent(&m_event))
	{
		switch (m_event.type)
		{
		// If user presses the X button, the render loop breaks
		case SDL_QUIT:
			m_bRunning = false;
			break;
		case SDL_KEYDOWN:
			switch ((int) m_event.key.keysym.sym)
			{
			case 122:    // z
				m_direction = 0;
				m_leaping = 1;
				break;
			case 100:    // d
				m_direction = 1;
				m_leaping = 1;
				break;
			case 115:    // s
				m_direction = 2;
				m_leaping = 1;
				break;
			case 113:    // q
				m_direction = 3;
				m_leaping = 1;
				break;
			case 32: //space
				FrogF->CreateBullet();
				break;
			case 101: //e
				m_theta = 0;
				for (m_theta = 0; m_theta < 360; m_theta = m_theta + 10) //electric bullet every 10°
				{
					FrogF->CreateBullet(4, m_theta);
				}
				break;
			case 114: //r
				m_theta = 0;
				for (m_theta = 0; m_theta < 360; m_theta = m_theta + 36) //forceshield bullet every 36°
				{
					FrogF->CreateBullet(5, m_theta);
				}
				break;
			default:
				break;
			}
			break;
		case SDL_WINDOWEVENT:
			switch (m_event.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				WIDTH = m_event.window.data1;
				HEIGHT = m_event.window.data2;
				Close();
				break;
			default:
				break;
			}
			break;
		default:
			//cout << (int) m_event.key.keysym.sym << endl; // to discover the integer value of an event
			m_direction = -1;
			break;
		}
	}
	if (m_event.type != SDL_KEYDOWN)
	{
		m_leaping = 0;
	}
}

void SDLFact::Close()
{
	SDL_SetWindowSize(g_pWindow, WIDTH, HEIGHT);
	for (auto* bullet : bullet_list)
	{
		delete (bullet);
		bullet_list.remove(bullet);
	}
	for (auto* vehicle : vehicle_list)
	{
		delete (vehicle);
		vehicle_list.remove(vehicle);
	}
	delete (FrogF);
	delete (TerrainF);
	SDL_SetWindowPosition(g_pWindow, SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED);
	m_widthScaleFactor = static_cast<double>(WIDTH) / 640;
	m_heightScaleFactor = static_cast<double>(HEIGHT) / 640;
	InitEntities();
	cout << "Game.Stop():\tGame stopped, Called destructors in opposite order."
			<< endl;
	//SDL_DestroyRenderer(m_pRenderer);
	//SDL_DestroyWindow(g_pWindow);
	//SDL_Quit();
}

SDLFact::~SDLFact()
{
	cout << "SDLFact.~SDLFact():\n\t\tDestroyed an SDLFact object. [INDIRECT]"
			<< endl;
}
}

//~ Formatted by Jindent --- http://www.jindent.com
