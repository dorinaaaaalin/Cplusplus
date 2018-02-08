#ifndef NODELIST_H
#define NODELIST_H

#include<string>
#include<iostream>

#include "Node.h"
#include "Resistor.h"
using namespace std;

class NodeList {
    private:
        Node* head;
       
       
    public:
        NodeList();
        ~NodeList();
        
        Node* getHead()const;
        Node* findNode(int id); //Accept a node ID and return a pointer to Node
        Node* findOrInsert(int id); //same as above but if it does not exist, create a new node
        bool ResistorExists(string name); //Determine if a resistor with a given label exists in any of the Nodes
        bool changeResistance(double resistance,string name); //Two copies! Change the resistance of a resistor by name 
        bool deleteResistor(string name); //Delete a resistor by name
        void deleteAllResistor(); 
        Node* getNodeFromName(string name);
        void printAllNodes() const;
        void solve();
        void printAllVoltages();
        
      //  void print() const;        
};



#endif /* NODELIST_H */
