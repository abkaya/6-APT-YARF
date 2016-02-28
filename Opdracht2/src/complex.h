/*
 * complex.h
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */

#ifndef SRC_COMPLEX_H_
#define SRC_COMPLEX_H_


using namespace std;

class complex
{
public:
	complex();
	complex(double, double);
	void set(double, double);
	double get_re();
	double get_im();
	complex add(complex);
	complex subtract(complex);
	void print();

	virtual ~complex();
private:
	double re;
	double im;
};




#endif /* SRC_COMPLEX_H_ */
