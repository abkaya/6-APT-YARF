//============================================================================
// Name        : student.h
// Author      : Abdil Kaya
// Version     : 1
// Copyright   : N/A
// Description : opdracht 2 - student header including declarations
//============================================================================

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
