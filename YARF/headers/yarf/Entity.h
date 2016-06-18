/*
 * Entity.h
 *
 *  Created on: 17 Jun 2016
 *      Author: abdil
 *  Abstract class Entity to
 */

#ifndef SRC_ENTITY_H_
#define SRC_ENTITY_H_
#include "Rect.h"

namespace yarf
{

class Entity
{
public:
	Entity();
	//non-pure virtual function | optional implementation inheritance
	virtual Rect GetRect();
	virtual bool IsInTerrain(Rect testPosition);

	//pure virtual function | forced interface inheritance
	virtual void ConvertGameToVis()=0;
	virtual ~Entity()=0;
	Rect position;
	float gameAxisWidth=4;
	float gameAxisHeight=3;
};

} /* namespace Game */

#endif /* SRC_ENTITY_H_ */


/*
// Example program to check how passing by reference can be done using
// a pointer to a struct's member-- or in this case a class' member
// author: abdil
#include <iostream>
#include <string>

using namespace std;

class rect{
    public:
        int x=0;
        int y=5;
        virtual void setr(int& xp, int& yp){x=xp; y=yp; xp=xp+1; yp=yp+1;}
        //takes pointer to integers and uses it to set own x and y value
        //also edits incoming pointer to int values, to test the pass by reference
    };

int main()
{
    rect r1;
    rect* pr1=&r1;

   std::cout << pr1->x << pr1->y << endl;
   //expect 0 and 5
   pr1->setr(pr1->x,pr1->y);
   std::cout << pr1->x << pr1->y << endl;
   //expect 1 and 6
}
*/
