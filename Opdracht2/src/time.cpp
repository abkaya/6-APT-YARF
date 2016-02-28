/*
 * time.cpp
 *
 *  Created on: 28 Feb 2016
 *      Author: abdil
 */


#include "time.h"
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
using namespace std;

time::time()
{
	day = 1;
	month = 1;
	year = 1970;
}

time::time(int fn_day, int fn_month, int fn_year)
{
	string error_code = check(fn_day, fn_month, fn_year);
	if (error_code == "none")
	{
		day = fn_day;
		month = fn_month;
		year = fn_year;
	}
	else
	{
		cout << "time error: " << error_code << endl;
		cout << "Default time set: " << endl;
		day = 1;
		month = 1;
		year = 1970;
	}
}

void time::set(int fn_day, int fn_month, int fn_year)
{
	string error_code = check(fn_day, fn_month, fn_year);
	if (error_code == "none")
	{
		day = fn_day;
		month = fn_month;
		year = fn_year;
	}
	else
		cout << "time error: " << error_code << endl;
}

void time::get_day()
{
	cout << "Day: " << day;
}

void time::get_month()
{
	cout << "Month: " << month;
}

void time::get_year()
{
	cout << "Year: " << year;
}

void time::print()
{
	cout << day << '/' << month << '/' << year << endl;
}

void time::advance()
{
	if (day < 28)
		day++;
	else
	{
		switch (month)
		{
		case 1:
			if (day < 31)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 2:
			if (check_leapy(year) == false)
			{
				if (day < 28)
					day++;
				else
				{
					day = 1;
					month++;
				}
			}
			else
			{
				if (day < 29)
					day++;
				else
				{
					day = 1;
					month++;
				}
			}
			break;
		case 3:
			if (day < 31)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 4:
			if (day < 30)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 5:
			if (day < 31)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 6:
			if (day < 31)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 7:
			if (day < 30)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 8:
			if (day < 31)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 9:
			if (day < 30)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 10:
			if (day < 31)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 11:
			if (day < 30)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 12:
			if (day < 31)
				day++;
			else
			{
				day = 1;
				month = 1;
				year++;
			}
			break;
		default:
			cout << "invalid time" << endl;
			break;
		}
	}
}

string time::check(int fn_day, int fn_month, int fn_year)
{
	if (fn_day < 1 || fn_month < 1 || fn_year < 0)
		return "day/month negative/zero or year negative";
	switch (fn_month)
	{
	case 1:
		if (fn_day > 31)
			return "January";
		break;
	case 2:
		if (check_leapy(fn_year) == false)
		{
			if (fn_day > 28)
				return "February : non leap-year";
		}
		else
		{
			if (fn_day > 29)
				return "February : leap-year";
		}
		break;
	case 3:
		if (fn_day > 31)
			return "March";
		break;
	case 4:
		if (fn_day > 30)
			return "April";
		break;
	case 5:
		if (fn_day > 31)
			return "May";
		break;
	case 6:
		if (fn_day > 31)
			return "June";
		break;
	case 7:
		if (fn_day > 30)
			return "July";
		break;
	case 8:
		if (fn_day > 31)
			return "August";
		break;
	case 9:
		if (fn_day > 30)
			return "September";
		break;
	case 10:
		if (fn_day > 31)
			return "October";
		break;
	case 11:
		if (fn_day > 30)
			return "November";
		break;
	case 12:
		if (fn_day > 31)
			return "December";
		break;
	default:
		break;
	}
	return "none";
}

int time::diff(time t)
{
	int ord = order(t);
	int i = 0;
	if (ord == 0)
	{
		while (ord != 2)
		{
			t.advance();
			ord = order(t);
			i++;
		}
	}
	else if (ord == 1)
	{
		while (ord != 2)
		{
			advance();
			ord = order(t);
			i++;
		}
	}
	else
		i = 0;
	return i;

}

void time::compare(time t)
{
	int td = diff(t);
	int ord = order(t);
	if (ord == 1)
	{
		cout << "Comparing " << now() << " to " << t.now() << endl;
		cout << "This date is " << td << " days behind the compared time."
				<< endl;
	}
	else if (ord == 0)
	{
		cout << "Comparing " << now() << " to " << t.now() << endl;
		cout << "This date is " << td << " days ahead of the compared time."
				<< endl;
	}
	else
	{
		cout << "Comparing " << now() << "to " << t.now() << endl;
		cout << "The dates are equal to each other." << endl;
	}
}

string time::now()
{
	ostringstream d, m, y;
	d << day;
	m << month;
	y << year;
	string sd = d.str();
	string sm = m.str();
	string sy = y.str();

	string t = sd + '/' + sm + '/' + sy;
	return t;
}

//custom operators
ostream& operator<<(ostream& os, const time& c)
{
	os << c.day << "/" << c.month << "/" << c.year;
	return os;
}
//prefix ++ operator
time& time::operator++()
{
	if (day < 28)
		day++;
	else
	{
		switch (month)
		{
		case 1:
			if (day < 31)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 2:
			if (check_leapy(year) == false)
			{
				if (day < 28)
					day++;
				else
				{
					day = 1;
					month++;
				}
			}
			else
			{
				if (day < 29)
					day++;
				else
				{
					day = 1;
					month++;
				}
			}
			break;
		case 3:
			if (day < 31)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 4:
			if (day < 30)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 5:
			if (day < 31)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 6:
			if (day < 31)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 7:
			if (day < 30)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 8:
			if (day < 31)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 9:
			if (day < 30)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 10:
			if (day < 31)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 11:
			if (day < 30)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 12:
			if (day < 31)
				day++;
			else
			{
				day = 1;
				month = 1;
				year++;
			}
			break;
		default:
			cout << "invalid time" << endl;
			break;
		}
	}
	return *this;
}
//postfix ++ operator
time time::operator++(int)
{
	time original = *this;
	if (day < 28)
		day++;
	else
	{
		switch (month)
		{
		case 1:
			if (day < 31)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 2:
			if (check_leapy(year) == false)
			{
				if (day < 28)
					day++;
				else
				{
					day = 1;
					month++;
				}
			}
			else
			{
				if (day < 29)
					day++;
				else
				{
					day = 1;
					month++;
				}
			}
			break;
		case 3:
			if (day < 31)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 4:
			if (day < 30)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 5:
			if (day < 31)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 6:
			if (day < 31)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 7:
			if (day < 30)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 8:
			if (day < 31)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 9:
			if (day < 30)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 10:
			if (day < 31)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 11:
			if (day < 30)
				day++;
			else
			{
				day = 1;
				month++;
			}
			break;
		case 12:
			if (day < 31)
				day++;
			else
			{
				day = 1;
				month = 1;
				year++;
			}
			break;
		default:
			cout << "invalid time" << endl;
			break;
		}
	}
	return original;

}

//help functions
bool time::check_leapy(int fn_year)
{
	if (fn_year % 4 == 0 && fn_year % 100 != 0)
		return true;
	else if (fn_year % 400 == 0)
		return true;
	else
		return false;
}

int time::order(time t) //t later in time than this. : 1, t earlier in time: 0. equal : 2
{
	int later;

	later = (t.year - year) * 365;
	later = later + (t.month - month) * 30;
	later = later + (t.day - day);

	if (later > 0)
	{
		//cout << "it's bigger" << endl;
		return 1;
	}
	else if (later < 0)
	{
		//cout << "it's not bigger" << endl;
		return 0;
	}
	else
	{
		//cout << "it's equal" << endl;
		return 2;
	}
}

time::~time()
{
}
