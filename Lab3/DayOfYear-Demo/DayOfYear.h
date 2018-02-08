#ifndef DAY_OF_YEAR_H
#define DAY_OF_YEAR_H

#include <string>

using namespace std;

class DayOfYear {
   private:
	int day;
	int month;

   public:
        // The constructors
        DayOfYear();
        DayOfYear(int d, int m);
        DayOfYear(string s);
    
        // The Destructor
        ~DayOfYear();

        // Accessor methods
        int getDay();
        int getMonth();
    
        // Mutator methods
        void setDay(int d);
        void setMonth(int m);
        
        // A utility method
        void print();
};
#endif

