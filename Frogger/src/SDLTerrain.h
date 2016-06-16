/*
 * SDLBorder.h
 *
 *  Created on: 8 Mar 2016
 *      Author: abdil
 */

#ifndef SRC_SDLTERRAIN_
#define SRC_SDLTERRAIN_

#include <iostream>
#include <string>
#include "SDLFact.h"
#include "Terrain.h"

namespace SDL{
class SDLTerrain : public Terrain
{
    public:
        SDLTerrain(SDL_Renderer * Renderer,
                  SDL_Texture *  Texture, int window_width, int window_height, double height_scale_factor);
        void Vis();
        virtual ~SDLTerrain();
    private:

        SDL_Texture * m_pTexture=0;

        // the first rectangle
         SDL_Rect m_terrainSrcRect;

        // another rectangle to copy to
         SDL_Rect m_borderDestRect;

        SDL_Renderer * m_pRenderer = 0;

        //Terrain blocks original source width and height
        double m_terrainWidth=64;
        double m_terrainHeight=64;

        //window width & height
        double m_windowWidth;
        double m_windowHeight;
        double m_heightScaleFactor;
};
#endif /* SRC_SDLTERRAIN_ */

}
//~ Formatted by Jindent --- http://www.jindent.com
