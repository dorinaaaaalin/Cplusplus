#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include "DBentry.h"
#include "TreeNode.h"
#include "TreeDB.h"

using namespace std;

/*  g++ -g -Wall testDBEntry.cpp DBentry.cpp -o testDBentry ./testDBentry (-g debugger info -Wall warning falgs -o link and compile)
 * implement a simple database to store and retrieve data. 
 * “domain name server” - names, Internet Protocol (IP), active/inactive state
 */
int main() {
    
     /* //TESTING DBEntry.cpp TreeNode.cpp
    string name = "www.hi.com";
    unsigned int ip = 123455;
    bool active = true;
    DBentry* hi = new DBentry(name,ip,active);
    DBentry* hello = new DBentry();
    DBentry* hey = new DBentry("hey",12434,false);
    
     operator<<(cout,*hi);
     operator<<(cout,*hello);
     operator<<(cout,*hey);
    
    TreeNode* root = new TreeNode(hi);
    TreeNode* tempL = new TreeNode(hello);
    TreeNode* tempR = new TreeNode(hey);
    root->setLeft(tempL);
    root->setRight(tempR);
    
    operator<<(cout,*root->getEntry());
    operator<<(cout,*root->getLeft()->getEntry());
    operator<<(cout,*root->getRight()->getEntry());
    */
    
    TreeDB dataBase;

    string line, command;
    // May have some setup code here
    cout << "> ";
    getline(cin, line); // Get a line from standard input

    while ( !cin.eof () ) {
             stringstream lineStream(line);
             lineStream >> command;
            //take three commands name IPaddress status 
             //This command creates a new entry with name
             //as the key and IPaddress (a non-negative integer) and status (active or
             //inactive) as specified.
            if (command == "insert") {
                string name;
                unsigned int ip;
                string status;
                bool s;
                lineStream >> name >> ip >> status;
                if(status == "active")
                    s = true;
                else
                    s = false;             
                
                DBentry* p = new DBentry(name,ip,s);
             
                if (dataBase.insert(p))
                    cout << "Success" <<endl;
                
                else if(!dataBase.insert(p)){
                    cout << "Error: entry already exists" << endl;
                    delete p;
                }

            }
            //This command finds the entry with the key name in the database, and prints name : IPaddress : status.
            else if ( command == "find" ) {
                string name;
                lineStream >> name;
                DBentry* temp = dataBase.find(name);
                if(temp == NULL)
                    cout << "Error: entry does not exist" << endl;
                else
                    cout << *temp;
            }
             //This command deletes the entry with the key name from the database
            else if ( command == "remove" ) {
                string name;
                lineStream >> name;
                dataBase.remove(name);
            }
             //This command prints all the entries in the database, sorted in ascending order
            //of keys, one entry per line
            else if ( command == "printall" ) { 
                operator<<(cout,dataBase);

            }
             //This command finds the entry with the key name in the database. Print number of probes if it exists
            else if ( command == "printprobes" ) {
                string name;
                lineStream >> name;
                DBentry* temp = dataBase.find(name);
                if(temp == NULL)
                    cout << "Error: entry does not exist" << endl;
                else
                    dataBase.printProbes();
            }
             //This command deletes all the entries in the database, returning it to the
                //empty state. When done, “Success” is printed.
            else if ( command == "removeall" ) {
                dataBase.clear();
                cout << "Success" << endl;
            }
             //This command counts the number of entries in the database that are active
            //and prints this count to cout.
            else if ( command == "countactive" ) {
                dataBase.countActive();
            }
             //name status. This command updates the status of the entry with
            //the given name; status must be either active or inactive.
            else if ( command == "updatestatus" ) {
                string name;
                string status;
                bool s;
                lineStream >> name >> status;
                DBentry* temp = dataBase.find(name);
                
                if ( temp == NULL)//not found
                    cout << "Error: entry does not exist"<<endl;
                else {
                  //  cout << "cehck upadte" << endl;
                    if(status == "active")
                        s = true;
                    else
                        s = false;
                    temp -> setActive(s);

                    cout << "Success" << endl;//<< temp->getActive() << endl;
                }
            }
            else{
                cout << "invalid command" << endl;
            }
             lineStream.clear();
             lineStream.ignore(1000, '\n');
              cout << "> ";
        //get the user input again
              getline(cin, line);
    } 
    
    dataBase.clear();
    return 0;
}

