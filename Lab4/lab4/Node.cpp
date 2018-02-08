#include <cstdlib>
#include <iostream>
#include <math.h>
#include "Node.h"
#include "Resistor.h"

#define MIN_ITERATION_CHANGE 0.0001
using namespace std;


Node::Node(){
    nodeID = 0;
   // cout << "default constructor" << nodeID << endl; //delete
}

Node::Node(int id,Node* nextOne){
   // cout << "default constructor for inserting a node with id" << id <<this << endl; //delete
    nodeID = id;
    next = nextOne;
    numRes = 0;
    voltage = 0.0;
}

Node::~Node(){
    //delete rl;
}

Node* Node::getNext() const{
    return (next);
}

void Node::setNext(Node* n){
    next = n;
}

ResistorList& Node:: getResistorList(){
    return (rl);
}

int Node::getNodeID() const{
    return nodeID;
}

void Node::setVoltage(double v){
    voltage = v;
    setV = true;
    
}

double Node::getVoltage() const{
    return voltage;
}

void Node::unsetV(){
    voltage = 0;
    setV = false;
}

void Node::addNumRes(){
    numRes++;
}

void Node::minusNumRes(){
    numRes=numRes -1 ;
}

int Node::getNumRes() const{
    return numRes;
}

void Node::printNode() const{
    if(numRes!=0){
    cout << "Connections at node " << nodeID << ": " << numRes << " resistor(s)" << endl;
    rl.printAllResistors(numRes);
    }
}

bool Node::getVoltageState() const{
    return setV;
}

void Node::setVoltageNoStateChange(double v){
    voltage =v;
}

