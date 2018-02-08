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
#include "Rparser.h"


using namespace std;


/*THis program works as a circuit database program. The parser should take a 
 * sequence of commands as input. It takes input from the terminal or a file,
 * parse it, verify that it is correct then print a response or an error msg
 */


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


int parser(NodeList*& nHead) {

    string line, command;
    // May have some setup code here
    cout << "> ";
    getline(cin, line); // Get a line from standard input




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
        double voltage = 13.244; //random

        if (command == "setV") {
            double voltage = 0;
            int nodeID = 0;
            lineStream >> nodeID;
            lineStream >> voltage;
            if (invalidArg(lineStream)) //if one of them is true then check is false 
                check = false;
            if (check == true) {
                if (nHead->findNode(nodeID) != NULL){
                    cout << "Set: node " << nodeID << " to " << voltage << " Volts" << endl;
                    nHead->findNode(nodeID)->setVoltage(voltage);
                }
                else
                     cout << "Error: node " << nodeID << " not found" << endl;
            }
            
        } else if (command == "unsetV") {
            int nodeID = 0;
            lineStream >> nodeID;
            if (invalidArg(lineStream)) //if one of them is true then check is false 
                check = false;
            if (check == true) {
                if (nHead->findNode(nodeID) != NULL){
                    nHead ->findNode(nodeID)->unsetV();
                     cout << "Unset: the solver will determine the voltage of node " << nodeID << endl;
                }
                else
                    cout << "Error: node " << nodeID << " not found" << endl;
            }

        } else if (command == "solve") {
            
                nHead->solve();
          
            //solve function :(
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
                    if (invalidArg(lineStream) || tooFewArg(lineStream))
                        check = false;
                }
                //use a new stringstream to check if there're too many arguments
                copyStream >> command >> name >> resistance >> nodeID1 >> nodeID2;
                if (check == true && tooManyArg(copyStream))
                    check = false;

            }
            if (check == true) {
                if (!nHead->ResistorExists(name) && !bothNodes(nodeID1, nodeID2)) {
                    int endPoints[2] = {nodeID1, nodeID2};
                    Node* n1 = nHead ->findOrInsert(nodeID1);
                    Node* n2 = nHead->findOrInsert(nodeID2);
                    n1->addNumRes();
                    n2->addNumRes();
                    n1->getResistorList().insertAtTail(name, resistance, endPoints);
                    n2->getResistorList().insertAtTail(name, resistance, endPoints);

                    cout << "Inserted: resistor " << name << " " << setprecision(2) << fixed << resistance << " Ohms " << nodeID1 << " -> " << nodeID2 << endl;
                }
                else
                    cout << "Error: resistor " << name << " already exists" << endl;

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

            if (check == true && nHead->ResistorExists(name)) 
                check = nHead ->changeResistance(resistance, name);
            else
                cout << "Error: resistor " << name << " not found" << endl;
          
            
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
                
                if (nHead->ResistorExists(name)) {
                    cout << "Print:" << endl;
                    nHead->getNodeFromName(name)->getResistorList().locateResistor(name)->print();
                } else
                     cout << "Error: resistor " << name << " not found" << endl;
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
                            nHead -> printAllNodes();

                        }
                    }
                }
                } else {


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
                            nHead ->findNode(nodeID1)->printNode();
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
                    nHead->deleteAllResistor();
                }
                else{
                    if(nHead->ResistorExists(name))
                        nHead->deleteResistor(name);
                    else
                        cout <<"Error: " << "resistor " << name << " not found" << endl;
                                
                                
                }
            }
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
        //delete nHead;
    } // End input loop until EOF.
    return 0;
}
