#ifndef RESISTOR_H
#define RESISTOR_H

#include <string>
#include <iostream>

using namespace std;

class Resistor
{
private:
   double resistance=0.0; // resistance (in Ohms)
   string name; // C++ string holding the label
   int endpointNodeIDs[2]; // IDs of nodes it attaches to 
   Resistor* next;
   
public:
   Resistor(string name_,double resistance_,int endpoints_[2]);
   // rIndex_ is the index of this resistor in the resistor array
   // endpoints_ holds the node indices to which this resistor connects

   ~Resistor();

   Resistor* getNext() const;
   void setNext(Resistor* n);
   
   string getName() const; // returns the name
   double getResistance() const; // returns the resistance

   void setResistance (double resistance_);
   void setEndPoints (int endpointNodeIDs[2]);
   int nodeId2(int id1);
   // you *may* create either of the below to print your resistor
   void print ();
   //friend ostream& operator<<(ostream&,const Resistor* head);
};

//ostream& operator<<(ostream&,const Resistor&);

#endif	/* RESISTOR_H */

