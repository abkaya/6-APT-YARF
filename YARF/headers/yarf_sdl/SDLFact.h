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

namespace yarf_sdl
{

// Class Hierarchies Straustrup p.68
// "A class hierarchy is a set of classes ordererd in a lattice created by derivation (e.g., : public)"
// Extend class Fact to the extent of its possibilities. Public will be public, but privates remain private and so on.
class SDLFact: public yarf::Fact
{
public:
	SDLFact();
	virtual ~SDLFact();
	void InitTextures(); // Creates all Textures. We will only pass pointers to these textures.
	void InitEntities();
	yarf::Frog * CreateFrog();
	Terrain * CreateBorder();
	yarf::Frog * GetFrog();
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
	void Resize();
private:
	int FPS;

	yarf::Frog * FrogF = 0;
	Terrain * TerrainF = 0;

	//using a list of vehicles rather than an array
	list<Vehicle *> vehicle_list;
	list<Vehicle *>::iterator vehicle_it_1;

	//second iterator used to check on colliding cars upon creation.
	list<Vehicle *>::iterator vehicle_it_2;
	int collided = 0;

	int WIDTH = 640, HEIGHT = 480;
	//the scale factor will adjust along with the width and height
	double widthScaleFactor = static_cast<double>(WIDTH) / 640;
	double heightScaleFactor = static_cast<double>(HEIGHT) / 480;

	// Border for Frog in game = gamewindow
	SDL_Rect windowRect;
	SDL_Rect vehicleBorder;

	// For the Frog->Vis(int Direction) function
	int m_direction;
	int m_leaping;
	int m_key = 0;

	// Main render loop variable. A private boolean variable
	bool bRunning = false;

	// Event handler variable
	SDL_Event event;

	// Definition of private pointer to Renderer
	SDL_Renderer * pRenderer = 0;

	// Temporary surface from which we'll create the Texture
	SDL_Surface * pTempSurface = 0;

	// Definition of private pointer to Texture
	SDL_Texture * pTexture;

	// pointer to Window declared
	SDL_Window * pWindow = 0;

	//collision detection left and right
	int leftA, rightA, leftB, rightB, bottomA, topA, bottomB, topB;

	bool m_spawnAvailable = false;
	list<yarf::Bullet *> bullet_list;
	list<yarf::Bullet *>::iterator bullet_it;
	int m_tempDir;
	int m_theta = 0;
protected:
	int a;
};
}
#endif /* SRC_SDLFACT_H_ */

//~ Formatted by Jindent --- http://www.jindent.com
