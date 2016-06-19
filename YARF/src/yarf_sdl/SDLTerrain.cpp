/*
 * SDLBorder.cpp
 *
 *  Created on: 8 Mar 2016
 *      Author: abdil
 */

#include "SDLTerrain.h"

namespace yarf_sdl
{
SDLTerrain::SDLTerrain(SDL_Renderer * Renderer, SDL_Texture * Texture,
		int window_width, int window_height, double height_scale_factor, double width_scale_factor)
{
	m_pRenderer = Renderer;
	m_pTexture = Texture;

	// non-leap nlx,nly
	m_terrainSrcRect.x = 64;
	m_terrainSrcRect.y = 0;
	m_borderDestRect.x = 0;
	m_borderDestRect.y = 0;

	m_windowWidth = window_width;
	m_windowHeight = window_height;
	m_heightScaleFactor = height_scale_factor;
	m_widthScaleFactor= width_scale_factor;

	m_terrainSrcRect.w = m_terrainSrcWidth;
	m_terrainSrcRect.h = m_terrainSrcHeight;

	m_terrainDstWidth = m_terrainDstWidth * m_widthScaleFactor;
	m_terrainDstHeight = m_terrainDstHeight * m_heightScaleFactor;

	m_borderDestRect.w = m_terrainDstWidth;
	m_borderDestRect.h = m_terrainDstHeight;
}
void SDLTerrain::Vis()
{

	/* Flexible window resizing for when WIDTH & HEIGHT are edited in SDLFact.h
	 * Default values:
	 * m_width = 640
	 * for which m_scaleFactor = 1
	 */

	/*road*/
	// place road terrain on the x-axis
	for (int i = 0; i < m_windowWidth; i += m_terrainDstWidth)
	{
		m_borderDestRect.x = i;
		// place road terrain along the y-axis
		for (int j = m_terrainDstHeight; j < m_windowHeight - m_terrainDstHeight; j +=
				m_terrainDstHeight)
		{
			m_borderDestRect.y = j;
			SDL_RenderCopy(m_pRenderer, m_pTexture, &m_terrainSrcRect,
					&m_borderDestRect);
		}
	}

	/*grass borderwalks*/
	m_terrainSrcRect.x = 128;
	m_borderDestRect.y = 0;
	//the first borderwalk terrain starts on y=0, placed along x-axis
	for (int i = 0; i < m_windowWidth; i += m_terrainDstWidth)
	{
		m_borderDestRect.x = i;
		SDL_RenderCopyEx(m_pRenderer, m_pTexture, &m_terrainSrcRect,
				&m_borderDestRect, 180, NULL, SDL_FLIP_NONE);
	}
	//the second borderwalk terrain starts on a y-value which depends on
	//the windowHeight and scaled terrain block height
	m_borderDestRect.y = m_windowHeight - m_terrainDstHeight;
	for (int i = 0; i < m_windowWidth; i += m_terrainDstWidth)
	{
		m_borderDestRect.x = i;
		SDL_RenderCopy(m_pRenderer, m_pTexture, &m_terrainSrcRect,
				&m_borderDestRect);
	}
	m_terrainSrcRect.x = 64;
}

SDLTerrain::~SDLTerrain()
{
}
}
