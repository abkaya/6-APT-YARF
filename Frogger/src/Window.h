/*
 * Window.h
 *
 *  Created on: 29 Feb 2016
 *      Author: abdil
 */

#ifndef SRC_WINDOW_H_
#define SRC_WINDOW_H_

#include <string>
#include <iostream>
using namespace std;

class Window
{
public:
	Window();
	virtual void Vis()=0;
	virtual void Close()=0;
	virtual bool Init(const char* title, int xpos, int ypos, int height, int width, int flags)=0;
	virtual void Update()=0;
	virtual void Render()=0;
	virtual void HandleEvents()=0;
	virtual ~Window();
};

#endif /* SRC_WINDOW_H_ */
