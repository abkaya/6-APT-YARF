//============================================================================
// Name        : complex.cpp
// Author      : Abdil Kaya
// Version     : 1
// Copyright   : N/A
// Description : opdracht 2 - complex definitions
//============================================================================

#include "student.h"
#include "complex.h"
#include<iostream>
#include<string>
using namespace std;

complex::complex()
{
	re = 0;
	im = 0;
}

complex::complex(double fn_re, double fn_im)
{
	re = fn_re;
	im = fn_im;
}

void complex::set(double fn_re, double fn_im)
{
	re = fn_re;
	im = fn_im;
}

double complex::get_re()
{
	return re;
}

double complex::get_im()
{
	return im;
}

complex complex::add(complex fn_cplx)
{
	complex cplx;
	cplx.re = re + fn_cplx.re;
	cplx.im = im + fn_cplx.im;
	return cplx;
}

complex complex::subtract(complex fn_cplx)
{
	complex cplx;
	cplx.re = re - fn_cplx.re;
	cplx.im = im - fn_cplx.im;
	return cplx;
}

void complex::print()
{
	cout << '(' << re << ',' << im << "j)" << endl;
}

complex::~complex()
{
}
