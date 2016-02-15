//============================================================================
// Name        : time.h
// Author      : Abdil Kaya
// Version     : 1
// Copyright   : N/A
// Description : opdracht 2 - time header including declarations
//============================================================================
#include<string>
using namespace std;

class time
{
public:
	time();
	time(int, int, int);
	void set(int, int, int);
	void get_day();
	void get_month();
	void get_year();
	void print();
	void advance();
	string check(int, int, int);
	int diff(time);
	void compare(time);
	string now();

	//custom operators
	friend ostream& operator<<(ostream& os, const time&);
	time& operator++(); //prefix
	time operator++(int); //postfix

	//help functions
	bool check_leapy(int);
	int order(time); //defines which of the two times is ahead; used to portray differences  and comapre properly

	virtual ~time();
private:
	int day;
	int month;
	int year;
};
