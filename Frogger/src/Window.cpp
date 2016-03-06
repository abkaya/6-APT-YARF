/*
 * Window.cpp
 *
 *  Created on: 29 Feb 2016
 *      Author: abdil
 */

#include "Window.h"
#include <iostream>
using namespace std;

Window::Window()
{
}

Window::~Window()
{
	cout << "Window.~Window():\n\t\tDestroyed a Window object. [DIRECT]" << endl;
}
