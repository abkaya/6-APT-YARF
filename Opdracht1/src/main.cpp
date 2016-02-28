/*
 * main.cpp
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */



#include <iostream>
#include <algorithm>
#include "calculations.h"

using namespace std;

int main()
{
	int getal = 1, aantal = -1, i, rij[20];
	do {
		cout << "\nGeef getal " << (aantal + 2) << " (0 om te stoppen) : ";
		cin >> getal;
		if (getal != 0)
		{
			aantal++;
			for (i = aantal; i > 0 && rij[i - 1] > getal; i--)
				rij[i] = rij[i - 1];
			rij[i] = getal;
			drukrij(rij, aantal);
		}

	} while (getal != 0);

	int array_sum = sum(rij,aantal);
	int min = minimum(rij, aantal);
	int max = maximum(rij, aantal);
	double avg = average(rij, aantal);
	drukrij(rij, aantal);

	cout << "Sum:\t" << array_sum << endl;
	cout << "Minimum:\t" << min << endl;
	cout << "Maximum:\t" << max << endl;
	cout << "Average:\t" << avg << endl;

	return 0;
}



