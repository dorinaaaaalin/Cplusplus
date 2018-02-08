#ifndef RESISTORLIST_H
#define RESISTORLIST_H

#include<string>
#include<iostream>
#include "Resistor.h"
using namespace std;

class ResistorList {
    private:   
        Resistor *head;
       
    public:
        ResistorList();
        //ResistorList(Resistor* h);
        ~ResistorList();
        
       
        Resistor* getHead() const;
        void setHead(Resistor* r);
        void insertAtTail(string name,double resistance, int endpoints[2]);
        Resistor* locateResistor(string name);
        void deleteResistor(Resistor* rDelete);
        void printAllResistors(int numRes)const;
        //void print() const;        
    };

    

#endif /* RESISTORLIST_H */