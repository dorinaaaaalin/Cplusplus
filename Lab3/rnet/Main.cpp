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

#include "Resistor.h"
#include "Node.h"
#include "Rparser.h"



using namespace std;

/*THis program works as a circuit database program. The parser should take a 
 * sequence of commands as input. It takes input from the terminal or a file,
 * parse it, verify that it is correct then print a response or an error msg
 */


int main() {
    //call parser()
    parser();
    return 0;
}