/*
 * student.cpp
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#include "student.h"
#include<iostream>
using namespace std;

student::student()
{
	naam = "";
	klas = "";
	punten[0] = 0;
	punten[1] = 0;
	punten[2] = 0;
}
student::student(string init_naam, string init_klas, int p0, int p1, int p2)
{
	naam = init_naam;
	klas = init_klas;
	punten[0] = p0;
	punten[1] = p1;
	punten[2] = p2;
}

void student::Print()
{
	cout << "Naam: " << naam << endl;
	cout << "Klas: " << klas << endl;
	cout << "Punten: " << punten[0] << ", " << punten[1] << ", " << punten[2]
			<< endl;
}

void student::SetNaam(string fn_naam)
{
	naam = fn_naam;
}

void student::SetKlas(string fn_klas)
{
	klas = fn_klas;
}

void student::SetPunten(int index, int p1)
{
	punten[index] = p1;
}

float student::Gemiddelde()
{
	int sum = punten[0] + punten[1] + punten[2];
	float gemiddelde = static_cast<float>(sum) / 3;
	return gemiddelde;
}

student::~student(void)
{
}

