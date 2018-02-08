#include <iostream>
#include <sstream>

using namespace std;

#include "DayOfYear.h"

DayOfYear::DayOfYear() {
        cout << "Default constructor invoked on: " << this << endl;
        day = 1;
        month = 1;
}

DayOfYear::DayOfYear(int d, int m) {
        cout << "Second constructor invoked on:" << this << endl;
        // Do error checking here
        day = d;
        month = m;
}

DayOfYear::DayOfYear(string s) {
        cout << "String constructor invoked on:" << this << endl;
        // Extract two integers out of the string argument
        stringstream strm(s);
        strm >> day >> month;
        if (strm.fail()) {
           cerr << "Cannot initialize object with given string; setting day and month to 1" <<endl;
           day = 1;
           month = 1;
        }
}


DayOfYear::~DayOfYear() {
        cout << "Destructor invoked on: " << this << endl;
}

int DayOfYear::getDay() {
        cout << "getDay invoked on: " << this << endl;
	return(day);
}


int DayOfYear::getMonth() {
        cout << "getMonth invoked on: " << this << endl;
	return(month);
}


void DayOfYear::setDay(int d) {
        // Do error checking here
        cout << "setDay invoked on: " << this << ", arg is: " << d << endl;
	day = d;
}


void DayOfYear::setMonth(int m) {
        // Do error checking here
        cout << "setMonth invoked on: " << this << ", arg is: " << m << endl;
	month = m;
}

void DayOfYear::print() {
	cout << "print invoked on: " << this <<": " << day << "/"  << month << endl;
}
