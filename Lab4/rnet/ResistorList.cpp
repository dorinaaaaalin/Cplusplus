#include <cstdlib>
#include <iostream>
#include "NodeList.h"
#include "Node.h"
#include "Resistor.h"
using namespace std;

ResistorList::ResistorList() {
   // cout << "default constructor NODELIST " << endl; //delete
    head = NULL;
}

ResistorList::~ResistorList() {
   // cout << "default destructor ResistorLIST " << endl; //delete
    Resistor* ptr;
    while (head != NULL) {
        ptr = head;
        head = ptr -> getNext();
        delete ptr;
    }
}

Resistor* ResistorList ::getHead() const{
    return head;
}

void ResistorList::setHead(Resistor* r){
    head=r;
}

//Resistor::Resistor(string name_,double resistance_,int endpoints_[2]){

void ResistorList::insertAtTail(string name,double resistance, int endpoints[2]) {
    Resistor* temp = new Resistor(name,resistance,endpoints);
    if (head == NULL) {
        head = temp;
        temp -> setNext(NULL);
    } else {
        Resistor* tptr = head;
        while (tptr -> getNext() != NULL)
            tptr = tptr -> getNext();
        tptr -> setNext(temp);
        temp -> setNext(NULL);
    }
}

Resistor* ResistorList::locateResistor(string name) {
    Resistor* tptr = head;
    while (tptr != NULL) {
        if (name == tptr -> getName()) {
            return tptr;
            break;
        }
        tptr = tptr -> getNext();
    }
    return tptr;
}

void ResistorList::deleteResistor(Resistor* ptr) {
    if (head == NULL) return;
    Resistor* rtptr = head;
    Resistor* pptr = NULL;
    while (rtptr != NULL) {
        if (ptr->getName() == rtptr->getName()) break;
        pptr = rtptr;
        rtptr = rtptr -> getNext();
    }
    if (rtptr == NULL) return;
    if (rtptr == head) {//if rtptr = Resistor* head
        Resistor* newHead = head;
        newHead = newHead -> getNext();
        delete rtptr; //**** DELETE
    }
    pptr -> setNext(rtptr -> getNext());
    delete rtptr; //****** DELETE 
}

void ResistorList::printAllResistors(int numRes) const{
    if(head == NULL) return;
    Resistor* temp = head;
    for(int i=0;i<numRes;i++){
        temp->print();
        temp = temp ->getNext();
    }
}
