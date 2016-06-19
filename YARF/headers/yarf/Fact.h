/*
 * Fact.h
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 *
 *  []Straustrup 4th, p.65
 *  Container class - Abstract types
 */

#ifndef SRC_FACT_H_
#define SRC_FACT_H_

#include <string>
#include <list>
#include "Bullet.h"
#include "Frog.h"
#include "Terrain.h"
#include "Vehicle.h"
#include "Rect.h"
#include "Entity.h"

namespace yarf{
class Frog;
class Fact
{
    public:
        Fact();
        virtual Terrain * CreateTerrain() = 0;
        virtual yarf::Frog * CreateFrog(list<yarf::Bullet *> &bullet_list) = 0;
        virtual yarf::Vehicle * CreateVehicle(bool init_spawn, int lane, int ordinalNumber)=0;
        virtual Rect GetFrogStates()=0;
        virtual bool Init(const char * title, int xPos, int yPos, int height,
			int width, int flags) = 0;
        virtual void InitTextures()=0;
        virtual void HandleVisEvents() = 0;
        virtual void RenderClear() = 0;
        virtual void RenderPresent()=0;
        virtual void HandleEvents() = 0;
        virtual void Resize() = 0;
        virtual bool IsRunning()=0;					//Visualisation running?
        virtual int GetTicks()=0;					//SDL ticks
        virtual void Delay(int delay_time)=0;		//Used for Ticks Per Second (TPS), which is in our case equal to FPS
        virtual void Stop()=0;
        virtual ~Fact();
};
}
#endif /* SRC_FACT_H_ */
