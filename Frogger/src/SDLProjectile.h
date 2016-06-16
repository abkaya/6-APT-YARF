/*
 * SDLProjectile.h
 *
 *  Created on: 21 Mar 2016
 *      Author: abdil
 */

#ifndef SRC_SDLPROJECTILE_H_
#define SRC_SDLPROJECTILE_H_

#include "Projectile.h"
#include "SDLFact.h"
#include "SDLFrog.h"

class SDLProjectile : public Projectile
{
    public:
        SDLProjectile(SDL_Renderer * Renderer,
                      SDL_Texture *  Texture);
        void Vis(const int & FPS);

        void Move(const int & FPS);

        void TargetAngle();

        virtual ~SDLProjectile();

    private:
        SDL_Renderer * m_pRenderer = 0;
        SDL_Texture * m_pTexture     = 0;
        SDL_Rect      m_sRect;

         // Angle -- used for driving left or right;
        int m_angle = 0;

        // another rectangle to copy to
        SDL_Rect m_dRect;


};
#endif /* SRC_SDLPROJECTILE_H_ */


//~ Formatted by Jindent --- http://www.jindent.com
