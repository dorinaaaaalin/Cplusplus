/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Rparser.h
 * Author: linxinzh
 *
 * Created on October 17, 2017, 11:20 PM
 */

#ifndef RPARSER_H
#define RPARSER_H

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include "NodeList.h"
#include "Resistor.h"
#include "Node.h"
#include "NodeList.h"
#include "ResistorList.h"

using namespace std;


   bool checkArgumentName(string argument);
   //bool negativeResistance(double resistance);
   bool nodeValue(int node);
   bool bothNodes(int node1, int node2);
   bool tooFewArg(stringstream& line);
   bool invalidArg(stringstream& line);
   bool tooManyArg(stringstream& line);
   bool checkNOTEOF(stringstream& line);
   bool peekToCheck(stringstream& line);
   int findResistor(string name);
   bool checkDupResistor(string name);
   void printAllResistors();
   bool fullResistorArrayCheck();
   int parser(NodeList*& n);


#endif /* RPARSER_H */

