/*
 * SDLProjectile.cpp
 *
 *  Created on: 21 Mar 2016
 *      Author: abdil
 */

#include "SDLProjectile.h"

SDLProjectile::SDLProjectile(SDL_Renderer * Renderer,
                             SDL_Texture *  Texture)
{
    m_pRenderer     = Renderer;
    m_pTexture      = Texture;

    m_sRect.x = 0;
    m_sRect.y = 64;

    m_dRect.x = 270;
    m_dRect.y = 595;
    m_dRect.w = m_sRect.w = 43;
    m_dRect.h = m_sRect.h = 25;
}
void SDLProjectile::Vis(const int & FPS)
{
	SDL_RenderCopyEx(m_pRenderer, m_pTexture, &m_sRect, &m_dRect, m_angle, NULL, SDL_FLIP_NONE);
}

void SDLProjectile::TargetAngle(){

}

void SDLProjectile::Move(const int & FPS)
{
}

SDLProjectile::~SDLProjectile()
{
    // TODO Auto-generated destructor stub
}


//~ Formatted by Jindent --- http://www.jindent.com
