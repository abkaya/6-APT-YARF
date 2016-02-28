/*
 * student.h
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#ifndef SRC_STUDENT_H_
#define SRC_STUDENT_H_


#include <string>
using namespace std;

class student
{
public:
	student();
	student(string, string, int, int, int);
	void Print();
	void SetNaam(string);
	void SetKlas(string);
	void SetPunten(int,int); //first integer is the index, the value is stored in the second one
	float Gemiddelde();

	virtual ~student();
private:
	string naam;
	string klas;
	int punten[3];
};




#endif /* SRC_STUDENT_H_ */
