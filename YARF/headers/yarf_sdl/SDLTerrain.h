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

namespace yarf_sdl{
class SDLTerrain : public Terrain
{
    public:
        SDLTerrain(SDL_Renderer * Renderer,
                  SDL_Texture *  Texture, int window_width, int window_height, double height_scale_factor, double width_scale_factor);
        void Vis();
        virtual ~SDLTerrain();
    private:

        SDL_Texture * m_pTexture=0;

        // the first rectangle
         SDL_Rect m_terrainSrcRect;

        // another rectangle to copy to
         SDL_Rect m_borderDestRect;

        SDL_Renderer * m_pRenderer = 0;

        //Terrain blocks don't keep the original source width and height
        double m_terrainSrcWidth=64;
        double m_terrainSrcHeight=64;
        //The destination however needs to abide by the 4x3 window setup (requirement)
        double m_terrainDstWidth=64;
        double m_terrainDstHeight=48;

        //window width & height
        double m_windowWidth;
        double m_windowHeight;
        double m_heightScaleFactor;
        double m_widthScaleFactor;
};
#endif /* SRC_SDLTERRAIN_ */

}
//~ Formatted by Jindent --- http://www.jindent.com
