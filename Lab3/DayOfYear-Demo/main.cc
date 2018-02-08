#include <iostream>
#include "DayOfYear.h"
#include <string>

using namespace std;

int main () {


    DayOfYear FirstOfJuly;
    FirstOfJuly.setDay(1);
    FirstOfJuly.setMonth(7);
    FirstOfJuly.print();

    DayOfYear Christmas(25,12);
    Christmas.print();

    string s = "7 8";
    DayOfYear Birthday(s);
    Birthday.print();

    DayOfYear MyBirthday(20,7);
    DayOfYear* MySecondBirthday = new DayOfYear;
    DayOfYear* MyThirdBirthday = new DayOfYear(18,5);
    
    delete MySecondBirthday;

    DayOfYear Birthdays[10];
    cout << endl << endl;
    DayOfYear* OtherBirthdays = new DayOfYear[10];
    cout << endl << endl;

    return (0);
}
