//============================================================================
// Name        : complex.h
// Author      : Abdil Kaya
// Version     : 1
// Copyright   : N/A
// Description : opdracht 2 - complex header including declarations
//============================================================================

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
