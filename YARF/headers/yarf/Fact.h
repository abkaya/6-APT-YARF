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
        virtual ~Fact();
        virtual void InitTextures()=0;
        virtual void InitEntities()=0;
        virtual Terrain * CreateTerrain() = 0;

        virtual yarf::Frog * CreateFrog() = 0;
        virtual yarf::Frog * GetFrog() = 0;
        virtual void DetectCollision()=0;
        virtual void IsVehicleInTerrain()=0;
        virtual void IsBulletInTerrain()=0;
        virtual bool IsSpawnAvailable(int lane)=0;
        virtual void SpawnVehicle(int lane)=0;
        virtual void ManageVehicleNumber()=0;
        virtual void RemoveCollidingVehicle(bool initial_spawns)=0;
        virtual void BulletVehicleCollision()=0;

        // Methods used to allow for the game loop & logic to happen in game.cpp
        virtual bool IsRunning()=0;
        virtual int GetTicks()=0;
        virtual void Delay(int delay_time)=0;

        virtual void Vis() = 0;
        virtual bool Init(const char * title,
                          int          xPos,
                          int          yPos,
                          int          height,
                          int          width,
                          int          flags) = 0;
        virtual void Render() = 0;
        virtual void HandleEvents() = 0;
        virtual void Resize() = 0;
};
}
#endif /* SRC_FACT_H_ */
