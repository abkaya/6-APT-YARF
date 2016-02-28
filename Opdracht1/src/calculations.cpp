/*
 * calculations.cpp
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

//functions definitions

#include "calculations.h"
#include <iostream>
using namespace std;

//sum
int sum(int rij[], int aantal)
{
	int array_sum = 0;
	for (int i = 0; i <= aantal; i++)
	{
		array_sum += rij[i];
	}
	return array_sum;
}

//minimum
int minimum(int rij[], int aantal)
{
	int min = rij[0];
	for (int i = 0; i <= aantal; i++)
	{
		if (rij[i] < min)
			min = rij[i];
	}
	return min;
}


//maximum
int maximum(int rij[], int aantal)
{
	int max = rij[0];
	for (int i = 0; i <= aantal; i++)
	{
		if (rij[i] > max)
			max = rij[i];
	}
	return max;
}


//average
double average(int rij[], int aantal)
{
	float avg = 0;
	int array_sum = sum(rij, aantal);
	avg = static_cast<float>(array_sum) / (aantal + 1);
	return avg;
}


//drukrij
void drukrij(int rij[], int aantal)
{
	for (int i = 0; i <= aantal; i++)
		cout << rij[i] << " ";
	cout << endl;
}



