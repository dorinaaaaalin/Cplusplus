/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Resistor.cpp
 * Author: linxinzh
 *
 * Created on October 10, 2017, 2:30 PM
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include "Resistor.h"

using namespace std;

//implementation of the constructor prototype
Resistor::Resistor(string name_,double resistance_,int endpoints_[2]){
    //cout << "------constructor invoked on: " << this << endl; //delete later
    name = name_;
    resistance = resistance_;
    endpointNodeIDs[0] = endpoints_[0];
    endpointNodeIDs[1] = endpoints_[1];
    //cout << "----" << name << resistance << endpointNodeIDs[0] << endpointNodeIDs[1] << "----" << endl;
}

Resistor::~Resistor(){
    //cout << "Destructor invoked on: " << this << endl; //delete
}

Resistor* Resistor::getNext() const{
    return (next);
}

void Resistor::setNext(Resistor* n){
    next = n;
}

string Resistor::getName() const{
    if(!name.empty())
        return name;
    //cout << "getName invoked on" << this << name << endl;
    
}

double Resistor::getResistance() const{
    //cout << "getResistance invoked on" << this << resistance << endl;
    return resistance;
}

void Resistor::setResistance (double resistance_){
    resistance = resistance_;
   // cout << endl << "setResistance error check" << this << "arg is " << resistance_ << endl;
}

void Resistor::setEndPoints (int endpoints[2]){
    endpointNodeIDs[0] = endpoints [0];
    endpointNodeIDs[1] = endpoints [1];
   // cout << "setEndpoints...";
    
}

/*ostream& operator<<(ostream& os,const Resistor& r){
    return os << left << setw(20) << setfill(' ') << r.name << " " << setprecision(2) << fixed << right << setw(8) << setfill(' ') << r.resistance << " Ohms " << r.endpointNodeIDs[0] << " -> " << r.endpointNodeIDs[1] << endl;
}*/

void Resistor::print(){
    cout << "  ";
    cout << fixed;
    cout << left << setw(20) << setfill(' ') << name << " " ;
    cout << setprecision(2) << fixed << right << setw(8) << setfill(' ') << resistance;
    cout << " Ohms " << endpointNodeIDs[0] << " -> " << endpointNodeIDs[1] << endl;
}

int Resistor::nodeId2(int id1){
    if(id1 == endpointNodeIDs[0])
        return endpointNodeIDs[1];
    else 
        return endpointNodeIDs[0];
}
