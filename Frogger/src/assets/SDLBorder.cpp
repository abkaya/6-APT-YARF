/*
 * SDLBorder.cpp
 *
 *  Created on: 7 Mar 2016
 *      Author: abdil
 */
/*
#include "SDLBorder.h"

using namespace std;

SDLBorder::SDLBorder(SDL_Renderer* Renderer)
{
	// TODO Auto-generated constructor stub
	m_pRenderer = Renderer;

	cout << "SDLFrog():\tCreate FROG IN SDL" << endl;
	m_pTempSurface = IMG_Load(".\\Debug\\frogger.png");

	m_pStaticBorder = SDL_CreateTextureFromSurface(m_pRenderer,
			m_pTempSurface);
	SDL_FreeSurface(m_pTempSurface);

	m_sourceRectangle.x = 0;
	m_sourceRectangle.y = 120;

	m_destinationRectangle.x = 0;
	m_destinationRectangle.y = 0;

	m_destinationRectangle.w = m_sourceRectangle.w = 399;
	m_destinationRectangle.h = m_sourceRectangle.h = 24;

}

void SDLBorder::Vis()
{
	SDL_RenderCopy(m_pRenderer, m_pStaticBorder, &m_sourceRectangle,
			&m_destinationRectangle);
}

SDLBorder::~SDLBorder()
{
	// TODO Auto-generated destructor stub
}
*/

