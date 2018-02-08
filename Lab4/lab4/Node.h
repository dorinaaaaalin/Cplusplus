#ifndef NODE_H
#define NODE_H

#include "ResistorList.h"
#define MIN_ITERATION_CHANGE 0.0001
class Node {
private:
    int nodeID;
    ResistorList rl;
    Node* next;
    double voltage;
    bool setV;
    int numRes;

public:
    Node();
    Node(int id,Node* next);
    ~Node();

    Node* getNext() const;
    void setNext(Node* n);
    ResistorList& getResistorList();
    void setVoltage(double v);
    void unsetV();
    int getNodeID() const;
    void addNumRes();
    void minusNumRes();
    int getNumRes() const;
    void printNode() const;
    bool getVoltageState() const;
    double solveVoltage(int id1);
    double getVoltage()const;
    void setVoltageNoStateChange(double v);
    


};

#endif /* NODE_H */

