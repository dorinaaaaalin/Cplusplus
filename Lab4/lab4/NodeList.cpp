#include <cstdlib>
#include <iostream>
#include <cmath>
#include <iomanip>
#include "ResistorList.h"
#include "Node.h"
#include "Resistor.h"
#include "NodeList.h"
using namespace std;

#define MIN_ITERATION_CHANGE 0.0001

NodeList::NodeList() {
   // cout << "default constructor NODELIST " << endl; //delete
    head = NULL;
}

NodeList::~NodeList() {
  //  cout << "default destructor NODELIST " << endl; //delete
    Node* ptr;
    while (head != NULL) {
        ptr = head;
        head = ptr -> getNext();
        delete ptr;
    }
}

Node* NodeList::findNode(int id) {
    Node* tptr = head;
    while (tptr != NULL) {
        if (tptr -> getNodeID() == id)
            break;
        tptr = tptr -> getNext();
    }
    return tptr;
}

Node* NodeList::getHead()const{
    return head;
}

Node* NodeList::findOrInsert(int id) {
    Node* findN = findNode(id);
    if (findN == NULL) {
        Node* tptr = head;
        Node* follow = NULL;

        while (tptr != NULL && id > tptr->getNodeID()) {
            follow = tptr;
            tptr = tptr->getNext();
        }

        Node* newNode = new Node(id, tptr);

        if (follow == NULL)
            head = newNode;
        else
            follow->setNext(newNode);
        return newNode;
    }//can not find one
    else
        return findN;
}

bool NodeList::ResistorExists(string name) {
    Node* tptr = head;
    bool found = false;
    while (tptr != NULL) {
        Resistor* rtptr = tptr -> getResistorList().getHead();
        while (rtptr != NULL) {
            if (name == rtptr -> getName()) {
                found = true;
                break;
            }
            rtptr = rtptr -> getNext();
        }
        tptr = tptr -> getNext();
    }
    return found;
}

bool NodeList::changeResistance(double resistance, string name) {
    Node* tptr = head;
    int count = 0;
    double r = 0;
    while (tptr != NULL) {
        Resistor* rtptr = tptr->getResistorList().getHead();
        while (rtptr != NULL) {
            if (name == rtptr->getName()) {
                r = rtptr->getResistance();
                rtptr->setResistance(resistance);
                count++;
                if (count == 2)
                    break;
            }
            rtptr = rtptr -> getNext();
        }
        tptr = tptr -> getNext();
    }
    if (count != 2)
        return false;
    else
        cout << "Modified: resistor " << name << " from " << r << " Ohms to " << setprecision(2) << fixed << resistance << " Ohms " << endl;
}

/*
int NodeList::delete_resistor(string name)
 {
    Node *ptr = NULL;//head for NodeList(node type)
    int checking = 0;
    if(head == NULL)
    {
        return checking;
    }
    else
    {
        for(ptr = head; ptr != NULL ; ptr = ptr->get_next_node())
        {
            Resistor* prev = NULL;
            Resistor* ptr1 = NULL;//pointer for ResistorList(resistor type)
                for(ptr1 =  ptr -> get_resistorList().get_head_ResistorList(); ptr1 != NULL; ptr1 = ptr1 -> get_resistor_next())
                {    
                    Resistor* copy_for_ptr1 = NULL;
                    copy_for_ptr1 = ptr1;
                  if(name == copy_for_ptr1->getName())
                  {
                      checking++;
                      if(prev != NULL)
                      {
                          prev -> set_next_resistor(copy_for_ptr1 -> get_resistor_next()); //not at the start of link list
                      }
                      else
                      {
                          ptr->get_resistorList().set_head_ResistorList(copy_for_ptr1 -> get_resistor_next());//start of link list
                      }
                      delete copy_for_ptr1;
                      break;
                   }
                  prev = ptr1;//update the prev pointer          
                }
        }       
        return checking;
    }
 } */

bool NodeList::deleteResistor(string name) {
    int count = 0;
    if (head == NULL) return false;
    else {
        Node* tptr = head;
        while (tptr != NULL) {
           
            Resistor* pptr = NULL;
            /*Resistor* rtptr = tptr -> getResistorList().getHead();
            while(rtptr!=NULL){
                if (name == rtptr->getName()) break;
                pptr = rtptr;
                rtptr = rtptr -> getNext();
            }
            if(rtptr == NULL) return false;
            
            if (rtptr == tptr -> getResistorList().getHead()) {//delete Resistor* head
                        tptr->getResistorList().setHead(rtptr->getNext());
                       // cout << "Deleted: resistor1 " << name << endl;
                        tptr->minusNumRes();
                         count ++;
                        delete rtptr;
                        break;                    
            }
            pptr -> setNext(rtptr -> getNext());
                      //  cout << "Deleted: resistor2 " << name << endl;
                        tptr->minusNumRes();
                        count++;
                        delete rtptr;
                        break;
            */
            // if (rtptr == NULL) cout << "do nothing" << endl;
           for ( Resistor* rtptr = tptr -> getResistorList().getHead(); rtptr != NULL; rtptr = rtptr -> getNext()) {
                if (name == rtptr->getName()) {
                    //Resistor* tt = rtptr;
                    if (pptr == NULL) {//delete Resistor* head
                        tptr->getResistorList().setHead(rtptr->getNext());
                       // cout << "Deleted: resistor1 " << name << endl;
                        tptr->minusNumRes();
                         count ++;
                        delete rtptr;
                        break;                    
                    } else {
                        pptr -> setNext(rtptr -> getNext());
                      //  cout << "Deleted: resistor2 " << name << endl;
                        tptr->minusNumRes();
                        count++;
                        delete rtptr;
                        break;
                    }
                    //delete rtptr;
                    //rtptr =  pptr;;
                    //break;
                }
                pptr = rtptr;
            }
            tptr = tptr -> getNext();
        }
    }
    if(count == 2){
        cout << "Deleted: resistor " << name << endl;
        return true;
    }
}

void NodeList::deleteAllResistor() {
    if (head == NULL) return;
    else{
        Node* tptr = head;
        while (tptr != NULL) {
            tptr->unsetV();
            Resistor* rtptr = tptr -> getResistorList().getHead();
           
            while (rtptr != NULL) {
                Resistor* ptr = rtptr;
                //rtptr = ptr -> getNext();
                tptr->getResistorList().setHead(ptr->getNext());
                delete ptr;
                ptr = NULL;
                tptr->minusNumRes();
                rtptr = tptr -> getResistorList().getHead();
                
            }
            tptr = tptr -> getNext();
        }
        cout << "Deleted: all resistors" << endl;
    }
    return;
}
//how to go from nHead to printR in resistor

Node* NodeList::getNodeFromName(string name) {
    Node* tptr = head;
    bool found = false;
    while (tptr != NULL) {
        Resistor* rtptr = tptr -> getResistorList().getHead();
        while (rtptr != NULL) {
            if (name == rtptr -> getName()) {
                found = true;
                break;
            }
            rtptr = rtptr -> getNext();
        }
        if (found == false)
            tptr = tptr -> getNext();
        else
            break;
    }
    return tptr;
}

void NodeList::printAllNodes() const {
    if (head == NULL) return;
    Node* temp = head;
    while (temp != NULL) {
        temp ->printNode();
        temp = temp ->getNext();
    }
}

void NodeList::solve(){
    double sumR = 0.0;
    double sumC = 0.0;
    double vol = 0.0;
    //Initialize the voltage of all nodes without setV to 0.0
    if (head == NULL) return;
    Node* temp = head;
    double zero = 0.0;
    bool checkSet = false;
    while (temp != NULL) {
        if(temp->getVoltageState()==false){
            temp ->setVoltageNoStateChange(zero);
        }
        else
            checkSet = true;
        temp = temp ->getNext();
    }
    
    double vChange = 0;
    bool start = true;
    double diff = 0.0;
    
    if(checkSet == true){
    while(vChange > MIN_ITERATION_CHANGE || start){
        start = false;    
        double max = 0;
        for(Node* startNode = head;startNode!=NULL;startNode=startNode->getNext()){
            
            if(startNode->getVoltageState()==false){
            int id1 = startNode->getNodeID();
            
            for(Resistor* temp = startNode->getResistorList().getHead();temp!=NULL;temp = temp->getNext()){
                sumR = sumR + 1/(temp->getResistance());
                
                int id2 = temp->nodeId2(id1);
                //get voltage for id2
                Node* tt = head;
                double current;
                while(tt!=NULL){
                    if(id2 == tt->getNodeID()){
                        current = (tt->getVoltage())/(temp->getResistance());
                        break;
                    }tt=tt->getNext();
                }
                sumC = sumC + current;               
            }
            vol = (1/sumR)*(sumC);
            diff = abs(vol - startNode->getVoltage());
            
            if(max < diff)
                max = diff;
            
            startNode ->setVoltageNoStateChange(vol);
            sumR=0.0;
            sumC=0.0;   
            }
        }
        vChange = max;        
    }
    printAllVoltages();
    }
    
    else
        cout << "Error: no nodes have their voltage set" << endl;
}

void NodeList::printAllVoltages(){
    if (head == NULL) return;
    Node* temp = head;
    cout << "Solve:" << endl;
    while (temp != NULL) {
        int nodeID = temp->getNodeID();
        double v = temp->getVoltage();
        cout << "  Node " << nodeID << ": " << v << " V" << endl;
        temp = temp ->getNext();
    }
}


