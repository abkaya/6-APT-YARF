/*
 * SDLFact.h
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#ifndef SRC_SDLFACT_H_
#define SRC_SDLFACT_H_

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include "Fact.h"
#include "Rect.h"
#include <list>
#include "SDLBullet.h"

//for random function
#include <cstdlib>
#include <ctime>

namespace SDL
{

// Class Hierarchies Straustrup p.68
// "A class hierarchy is a set of classes ordererd in a lattice created by derivation (e.g., : public)
// Extend class Fact to the extent of its possibilities. Public will be public, but privates remain private and so on.
class SDLFact: public Game::Fact
{
public:
	SDLFact();
	virtual ~SDLFact();
	void InitTextures(); // Creates all Textures. We will only pass pointers to these textures.
	void InitEntities();
	Game::Frog * CreateFrog();
	Terrain * CreateBorder();
	Game::Frog * GetFrog();
	void IsVehicleInTerrain();
	void IsBulletInTerrain();
	void RemoveCollidingVehicle(bool initial_spawns);
	void BulletVehicleCollision();

	// Methods used to allow for the game loop & logic to happen in game.cpp
	bool IsRunning();
	int GetTicks();
	void Delay(int delay_time);

	void Vis();
	bool Init(const char * title, int xPos, int yPos, int height, int width,
			int flags);
	void Render();
	void HandleEvents();
	void DetectCollision();
	bool IsSpawnAvailable(int lane);
	void SpawnVehicle(int lane);
	void ManageVehicleNumber();
	void Close();
private:
	int FPS;

	Game::Frog * FrogF = 0;
	Terrain * TerrainF = 0;

	//using a list of vehicles rather than an array
	list<Vehicle *> vehicle_list;
	list<Vehicle *>::iterator vehicle_it_1;

	//second iterator used to check on colliding cars upon creation.
	list<Vehicle *>::iterator vehicle_it_2;
	int m_collided = 0;

	int WIDTH = 1300, HEIGHT = 900;
	//the scale factor will adjust along with the width and height
	double m_widthScaleFactor = static_cast<double>(WIDTH) / 640;
	double m_heightScaleFactor = static_cast<double>(HEIGHT) / 640;

	// Border for Frog in game = gamewindow
	SDL_Rect m_windowRect;
	SDL_Rect m_vehicleBorder;

	// For the Frog->Vis(int Direction) function
	int m_direction;
	int m_leaping;
	int m_key = 0;

	// Main render loop variable. A private boolean variable
	bool m_bRunning = false;

	// Event handler variable
	SDL_Event m_event;

	// Definition of private pointer to Renderer
	SDL_Renderer * m_pRenderer = 0;

	// Temporary surface from which we'll create the Texture
	SDL_Surface * m_pTempSurface = 0;

	// Definition of private pointer to Texture
	SDL_Texture * m_pTexture;

	// global pointer to Window declared
	SDL_Window * g_pWindow = 0;

	//collision detection left and right
	int leftA, rightA, leftB, rightB, bottomA, topA, bottomB, topB;

	bool m_spawnAvailable = false;
	list<Game::Bullet *> bullet_list;
	list<Game::Bullet *>::iterator bullet_it;
	int m_tempDir;
	int m_theta=0;
};
}
#endif /* SRC_SDLFACT_H_ */

//~ Formatted by Jindent --- http://www.jindent.com
