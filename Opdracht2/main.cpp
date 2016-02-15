//============================================================================
// Name        : main.cpp
// Author      : Abdil Kaya
// Version     : 1
// Copyright   : N/A
// Description : opdracht 2 - main
//============================================================================

#include <iostream>
#include "student.h"
#include "complex.h"
#include "time.h"
#include <cmath>
using namespace std;

int main()
{
	cout << "*************Part 1 of the program.*************" << endl;
	student st;
	student st2("Jan", "3EA", 15, 12, 13);

	st.SetPunten(0, 15);
	st.Print();
	st2.Print();

	cout << "Het gemiddelde is " << st2.Gemiddelde() << endl;

	cout << "*************Part 2 of the program.*************" << endl;
	complex c1;
	complex c2(1.0, 3.0);
	cout << c1.get_re() << " + " << c1.get_im() << " j" << endl;
	cout << c2.get_re() << " + " << c2.get_im() << " j" << endl;
	c1.set(5.0, 4.0);
	cout << c1.get_re() << " + " << c1.get_im() << " j" << endl;
	c1.add(c2);
	cout << c1.get_re() << " + " << c1.get_im() << " j" << endl;
	c1.print();

	c1.~complex();
	c2.~complex();

	cout << "*************Part 3 of the program.*************" << endl;
	time t1;
	t1.print();
	time t2(202, 3, 2016);
	t2.print();
	t2.set(29, 2, 2015);
	t2.print();
	t2.set(22, 2, 2016);
	t2.print();
	time t3(26, 2, 2002);
	t3.advance();
	t3.print();
	t3.compare(t1);
	t2.compare(t3);
	t1.compare(t2);

	cout << endl << "Compare Abdil's birthday to Kevin's:" << endl;
	time t4(25, 3, 1992);
	time t5(27, 5, 1993);
	t5.compare(t4);

	time t6(22, 2, 2016);

	t6++;
	cout << t6 << endl;
	t6++;
	cout << t6 << endl;

	return 0;
}
