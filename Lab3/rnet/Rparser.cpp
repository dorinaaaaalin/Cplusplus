/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: linxinzh
 *
 * Created on October 10, 2017, 2:25 PM
 */

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "Rparser.h"
#include "Node.h"
#include "Resistor.h"

using namespace std;


#define MIN_NODE_NUMBER 0

/*THis program works as a circuit database program. The parser should take a 
 * sequence of commands as input. It takes input from the terminal or a file,
 * parse it, verify that it is correct then print a response or an error msg
 */

//global variables
int maxNodeNumber = 0;
int maxResistors = 0;
Resistor **resistorArray;
Node *nodeArray;
int rIndex = 0;

//return true if argument name is all

bool checkArgumentName(string argument) {
    if (argument == "all") {
        cout << "Error: resistor name cannot be the keyword \"all\"" << endl;
        return true;
    } else
        return false;
}
//return true if resistance is negative

bool negativeResistance(double resistance) {
    if (resistance < 0.0) {
        cout << "Error: negative resistance" << endl;
        return true;
    } else
        return false;
}
//return true if the node value is out of bound

bool nodeValue(int node) {
    if (node > maxNodeNumber || node < MIN_NODE_NUMBER) {
        cout << "Error: node " << node << " is out of permitted range 0-" << maxNodeNumber << endl;
        return true;
    } else
        return false;
}
//return true if both nodes are the same

bool bothNodes(int node1, int node2) {
    if (node1 == node2) {
        cout << "Error: both terminals of resistor connect to node " << node1 << endl;
        return true;
    } else
        return false;
}
//return ture if there're too few arguments in the stringstream, pass the reference of stringstream

bool tooFewArg(stringstream& line) {
    if (line.fail()) {
        if (line.eof()) {
            cout << "Error: too few arguments" << endl;
            return true;
        }
    } else
        return false;

}
//there should only be two fail cases 1) incorrect types detected 2) end of file
//return ture if there's a invalid argument in the stringstream, pass the reference of stringstream

bool invalidArg(stringstream& line) {
    if (line.fail()) {
        if (!line.eof()) {
            cout << "Error: invalid argument" << endl;
            return true;
        }
    } else
        return false;
}
//return true if there're more arguments as expected

bool tooManyArg(stringstream& line) {
    string next;
    line >> next;
    if (!next.empty()) {
        cout << "Error: too many arguments" << endl;
        return true;
    } else
        return false;
}
//return true if its not the end of file

bool checkNOTEOF(stringstream& line) {
    string next;
    line >> next;
    if (!next.empty())
        return true;
    else
        return false;
}
//return true if there's still argument after calling

bool peekToCheck(stringstream& line) {
    char c = line.peek();

    if (c == ' ' || c == '\t' || c == '\n') {
        return false;
    } else {
        cout << "Error: invalid argument" << endl;
        return true;
    }

}

//findResistor that has the same name

int findResistor(string name) {
    bool find = false;
    for (int i = 0; i < rIndex; i++) {
        if (name == resistorArray[i] -> getName()) {
            find = true;
            return i;
        }
    }
    if (find == false) cout << "Error: resistor " << name << " not found" << endl;
    return -1;
}

bool checkDupResistor(string name) {
    bool find = false;
    for (int i = 0; i < rIndex; i++) {
        if (name == resistorArray[i] -> getName()) {
            find = true;
        }
    }
    if (find == true) cout << "Error: resistor " << name << " already exists" << endl;
    return find;
}

void printAllResistors() {
    cout << "Print:" << endl;
    for (int i = 0; i < rIndex; i++) {
        operator<<(cout, *resistorArray[i]);
    }
}

bool fullResistorArrayCheck() {
    if (rIndex >= maxResistors) {
        cout << "Error: resistor array is full" << endl;
        return true;
    } else
        return false;
}

int parser() {

    string line, command;

    // May have some setup code here
    cout << "> ";
    getline(cin, line); // Get a line from standard input
    maxNodeNumber = 0;
    maxResistors = 0;
    //tempMaxNode and tempMaxResistors to avoid delete the old pointers in maxVal
    int tempMaxNode = 0;
    int tempMaxResistors = 0;
    while (!cin.eof()) {
        // Put the line in a stringstream for parsing
        // Making a new stringstream for each line so flags etc. are in a known state

        command = "first";
        stringstream lineStream(line);
        lineStream >> command;

        //to test checkEOF function
        stringstream testStream(line);
        testStream >> command;

        //to test too many arguments functions
        stringstream copyStream(line);

        string name;
        int nodeID1 = 1567; //random
        int nodeID2 = 1345; //random
        double resistance = 1537.5; //random
        bool check = true;


        if (command == "maxVal") {
            //delete old pointers
            if (tempMaxNode > 0) {
                delete [] nodeArray;
                nodeArray = NULL;
                tempMaxNode = 0;
                maxNodeNumber = 0;

            }
            if (tempMaxResistors > 0) {
                for (int i = 0; i < rIndex; i++) {
                    delete resistorArray[i];
                    resistorArray[i] = NULL;
                }
                delete []resistorArray;
                resistorArray = NULL;
                tempMaxResistors = 0;
                maxResistors = 0;
                rIndex = 0;
            }
            lineStream >> maxNodeNumber >> maxResistors;

            if (maxNodeNumber <= 0 || maxResistors <= 0) {
                cout << "Error: maxVal arguments must be greater than 0" << endl;
                maxNodeNumber = 0;
                maxResistors = 0;
            } else {
                cout << "New network: max node number is " << maxNodeNumber << "; max resistors is " << maxResistors << endl;

                nodeArray = new Node[maxNodeNumber + 1]; //calls node constructor n times

                resistorArray = new Resistor*[maxResistors];

                tempMaxNode = maxNodeNumber;
                tempMaxResistors = maxResistors;
            }

        } else if (command == "insertR") {
            // parse an insertR command
            lineStream >> name;
            stringstream test2Stream(line);
            //check if name is all/invalid name
            if (invalidArg(lineStream) || checkArgumentName(name)) //if one of them is true then check is false 
                check = false;
            //check if resistance is double
            if (check == true) {
                lineStream >> resistance;
                //make the new test2Stream the same as linestream to check if its eof
                test2Stream >> command >> name >> resistance;
                if (checkNOTEOF(test2Stream)) {
                    if (peekToCheck(lineStream))
                        check = false;
                }

                if (check == true) {
                    if (invalidArg(lineStream) || negativeResistance(resistance)) //|| checkDouble(resistance) || 
                        check = false;
                }
                stringstream testStream(line);
                testStream >> command;

                //to test too many arguments functions
                stringstream copyStream(line);

                string name;
                int nodeID1 = 1567; //random
                int nodeID2 = 1345; //random
            }
            if (check == true) {
                lineStream >> nodeID1 >> nodeID2;
                testStream >> name >> resistance >> nodeID1 >> nodeID2;


                if (check == true && checkNOTEOF(testStream)) { //checkEOF is false then it is empty
                    if (peekToCheck(lineStream)) // if its true then theres stuff after the last node     
                        check = false;
                }

                if (check == true) {
                    if (invalidArg(lineStream) || nodeValue(nodeID1) || nodeValue(nodeID2) || tooFewArg(lineStream))
                        check = false;
                }
                //use a new stringstream to check if there're too many arguments
                copyStream >> command >> name >> resistance >> nodeID1 >> nodeID2;
                if (check == true && tooManyArg(copyStream))
                    check = false;

            }
            if (check == true) {
                if (!fullResistorArrayCheck()){
                    if (!nodeArray[nodeID1].canAddResistor(rIndex) || !nodeArray[nodeID2].canAddResistor(rIndex))
                        cout << "Error: node is full" << endl;
                    else if(nodeArray[nodeID1].canAddResistor(rIndex) && nodeArray[nodeID2].canAddResistor(rIndex) && !checkDupResistor(name) && !bothNodes(nodeID1, nodeID2)) {
                        nodeArray[nodeID1].addResistor(rIndex);
                        nodeArray[nodeID2].addResistor(rIndex);
                        int endPoints[2] = {nodeID1, nodeID2};
                        resistorArray[rIndex] = new Resistor(rIndex, name, resistance, endPoints);
                        rIndex++;
                        cout << "Inserted: resistor " << name << " " << setprecision(2) << fixed << resistance << " Ohms " << nodeID1 << " -> " << nodeID2 << endl;
                    } 
                }
            }
        } else if (command == "modifyR") {
            lineStream >> name; //>> resistance;
            //check if name is all/invalid name
            if (invalidArg(lineStream) || checkArgumentName(name)) //if one of them is true then check is false
                check = false;
            if (check == true) {
                lineStream >> resistance;
                testStream >> name >> resistance;
                //check for negative resistance and too few arguments
                if (invalidArg(lineStream) || tooFewArg(lineStream))
                    check = false;
            }
            //check if its end of file if its not, peek to see if the last argument is space 
            if (check == true && checkNOTEOF(testStream)) {
                if (peekToCheck(lineStream))
                    check = false;
            }

            if (check == true)
                if (negativeResistance(resistance))
                    check = false;
            //use a new stringstream to check if there're too many arguments
            copyStream >> command >> name >> resistance;
            if (check == true && tooManyArg(copyStream))
                check = false;

            if (check == true) {
                int i = findResistor(name);
                if (i != -1) {
                    double res = 0;
                    res = resistorArray[i]->getResistance();
                    resistorArray[i]->setResistance(resistance);
                    cout << "Modified: resistor " << name << " from " << res << " Ohms to " << setprecision(2) << fixed << resistance << " Ohms " << endl;
                }
            }
        } else if (command == "printR") {
            lineStream >> name;
            testStream >> name;

            //lineStream >> resistance;
            //testStream >> resistance;
            //check for negative resistance and too few arguments
            if (invalidArg(lineStream) || tooManyArg(testStream) || tooFewArg(lineStream)) //if one of them is true then check is false
                check = false;
            //check if the resistor name is all 
            if (check == true) {
                if (name == "all") {
                    if (rIndex == 0)
                        cout << "Print:" << endl;
                    else if (rIndex != 0)
                        printAllResistors();
                } else {
                    int i = findResistor(name);
                    if (i != -1) {
                        cout << "Print:" << endl;
                        operator<<(cout, *resistorArray[i]);
                    }
                }

            }

        } else if (command == "printNode") {
            lineStream >> nodeID1;
            copyStream >> nodeID1; //to check if there're too many arguments
            //if linestream fails two cases 1. too few arguments 2. incorrect type of inputs
            if (lineStream.fail()) {
                if (lineStream.eof()) {
                    cout << "Error: too few arguments" << endl;
                    check = false;
                } else {
                    testStream >> name;
                    check = false;
                    //the only valid case is all
                    if (name != "all")
                        cout << "Error: invalid argument" << endl;
                        //check for too many arguments
                    else if (tooManyArg(testStream) == false) {
                        if (name == "all") {
                            cout << "Print:" << endl;
                            for (int i = 0; i < (maxNodeNumber + 1); i++) {
                                nodeArray[i].print(i);
                                int numRes = nodeArray[i].getNumRes();
                                if (numRes != 0) {
                                    for (int j = 0; j < numRes; j++) {
                                        int rID = nodeArray[i].getRID(j);
                                        cout << "  ";
                                        operator<<(cout, *resistorArray[rID]);
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                //check the node vale and see if its invalid first
                if (nodeValue(nodeID1))
                    check = false;

                testStream >> nodeID1;
                if (check == true) {
                    if (checkNOTEOF(testStream)) { //checkEOF is false then it is empty
                        if (peekToCheck(lineStream)) // if its true then theres stuff for 2nd node      || tooManyArg(testStream) 
                            check = false;
                    }
                    if (check == true) {
                        if (tooManyArg(lineStream))
                            check = false;
                    }
                    if (check == true) {
                        cout << "Print:" << endl;
                        nodeArray[nodeID1].print(nodeID1);
                        int numRes = nodeArray[nodeID1].getNumRes();
                        for (int i = 0; i < numRes; i++) {
                            int rID = nodeArray[nodeID1].getRID(i);
                            cout << "  ";
                            operator<<(cout, *resistorArray[rID]);
                        }
                    }
                }
            }
        } else if (command == "deleteR") {
            lineStream >> name;
            testStream >> name;

            if (invalidArg(lineStream) || tooManyArg(testStream) || tooFewArg(lineStream)) //if one of them is true then check is false
                check = false;

            if (check == true) {
                if (name == "all") {
                    if (rIndex > 0) {
                        delete [] nodeArray;
                        nodeArray = NULL;

                        for (int i = 0; i < rIndex; i++) {
                            delete resistorArray[i];
                            resistorArray[i] = NULL;
                        }

                        delete []resistorArray;
                        resistorArray = NULL;
                        rIndex = 0;
                        
                        nodeArray = new Node[maxNodeNumber + 1]; //calls node constructor n times

                        resistorArray = new Resistor*[maxResistors];
                    }
                    cout << "Deleted: all resistors" << endl;

                    //tempMaxNode and tempMaxResistors to avoid delete the old pointers in maxVal
                    tempMaxNode = maxNodeNumber;
                    tempMaxResistors = maxResistors;
                }
            }
        } else {
            cout << "Error: invalid command" << endl;
        }
        //reset all the stringstream's flags to default
        lineStream.clear();
        testStream.clear();
        copyStream.clear();
        //ignore the first 1000 characters or ignore until it sees a new line 
        copyStream.ignore(1000, '\n');
        testStream.ignore(1000, '\n');
        lineStream.ignore(1000, '\n');
        cout << "> ";
        //get the user input again
        getline(cin, line);
    } // End input loop until EOF.

    if (rIndex > 0 || tempMaxNode > 0 || tempMaxResistors > 0) {
        delete [] nodeArray;
        nodeArray = NULL;

        for (int i = 0; i < rIndex; i++) {
            delete resistorArray[i];
            resistorArray[i] = NULL;
        }

        delete []resistorArray;
        resistorArray = NULL;
        rIndex = 0;
    }

    return 0;
}
