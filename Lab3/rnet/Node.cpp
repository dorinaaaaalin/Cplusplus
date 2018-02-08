/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Node.cpp
 * Author: linxinzh
 *
 * Created on October 10, 2017, 2:29 PM
 */

#include <cstdlib>
#include <iostream>
#include "Node.h"
#include "Resistor.h"

using namespace std;

#define MAX_RESISTORS_PER_NODE 5

Node::Node(){
   // cout << "default constructor" << numRes <<this << endl; //delete
    numRes = 0;
    resIDArray[MAX_RESISTORS_PER_NODE];
}

Node::~Node(){}

bool Node::canAddResistor(int rIndex){ 
    if(numRes < MAX_RESISTORS_PER_NODE)
        return true;
    else
        return false;
}

int Node::getRID(int index) const{
    //cout << "getRID invoked on" << this << endl;
    return resIDArray[index];
}

int Node::getNumRes() const{
    //cout << "getNumRes invoked on" << this << numRes << endl;
    return numRes;
}

void Node::addResistor (int rIndex){
    resIDArray[numRes] = rIndex;
    numRes++;
    
   // cout << "resistor added with index :" << rIndex << endl;
}

void Node::print(int nodeIndex){
    cout << "Connections at node " << nodeIndex << ": " << numRes << " resistor(s)"<< endl;
}
