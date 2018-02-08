#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;


#define MIN_NODE_NUMBER 0
#define MAX_NODE_NUMBER 5000

void invalid_command();
void invalid_Argument();
void negative_resistance();
void out_of_Range(int value);
void resistor_name();
void terminals(int value);
void toomany();
void toofew();
void insertR(string line);
void modifyR(string line);
void printR(string line);
void printNode(string line);
void deleteR(string line);


int main() {
	string line, command;
	cout<< ">";
	getline (cin, line); // Get a line from standard input
	while ( !cin.eof () ) {
	// Put the line in a stringstream for parsing;
		stringstream lineStream (line);
		lineStream >> command;
		if (command == "insertR") {
			insertR(line);
		}else if ( command == "modifyR" ) {
			modifyR(line);
		}else if ( command == "printR" ) {
			printR(line);
		}else if ( command == "printNode" ) {
			printNode(line);
		}else if ( command == "deleteR" ) {
			deleteR(line);
		}else {
			invalid_command();
		}
		cout<< ">";
		getline (cin, line);
	} // End input loop until EOF.
return 0;
}

void invalid_command(){
	cout<< "Error: invalid command"<<endl;
}

void invalid_Argument(){
	cout<< "Error: invalid argument"<<endl;
}

void negative_resistance(){
	cout<< "Error: negative resistance"<<endl;
}

void out_of_Range(int value){
	cout<<"Error: node "<< value << " is out of permitted range "<< MIN_NODE_NUMBER <<" - "<< MAX_NODE_NUMBER <<endl;
}

void resistor_name(){
	cout<<"Error: resistor name cannot be the keyword “all”"<<endl;
}

void terminals(int value){
	cout<<"Error: both terminals of resistor connect to node "<< value <<endl;
}

void toomany(){
	cout<< "Error: too many arguments"<<endl;
}

void toofew(){
	cout<< "Error: too few arguments"<<endl;
}

void insertR(string line){
	string command,name;
	stringstream lineStream (line);
	lineStream >> command;
	int node1,node2;
	double ohm;

	if (lineStream.eof()){	//end of file
		toofew();
		return;
	}

	lineStream >> name;
	if (lineStream.eof()){	//end of file
		toofew();
		return;
	}
	if (name == "all"){
		resistor_name();
		return;
	}

	lineStream >> ohm;
	
	if (lineStream.fail()){	//check if it is an integer
		if (lineStream.eof()){	//end of file
			toofew();
			return;
		}
		invalid_Argument();
		lineStream.ignore(1000,' ');
		lineStream.clear();
	    return;
	}
		if(ohm < 0.0){
			if(lineStream.peek()!= ' '){
				invalid_Argument();
				lineStream.ignore(1000,' ');
				return;
			}
			negative_resistance();
			return;
		}
		
	lineStream >> node1;
	if (lineStream.fail()){	//check if it is an integer
		lineStream >> ws;
		if (lineStream.eof()){	//end of file
			toofew();
			return;
		}
		invalid_Argument();
		lineStream.clear();
	    return;
	}
	lineStream >> ws;
	if(lineStream.peek() == '.' || lineStream.peek()!= ' '){
		invalid_Argument();
		lineStream.ignore(1000,' ');
		return;
		}
	
	lineStream >> node2;
	if (lineStream.fail()){	//check if it is an integer
		lineStream >> ws;
		if (!lineStream.eof()){	//end of file
			toomany();
			return;
		}
		invalid_Argument();
		lineStream.clear();
	    return;
	}
	if(lineStream.peek() == '.' || lineStream.peek()!= ' '){
		invalid_Argument();
		lineStream.ignore(1000,' ');
		return;
		}
	
	if(!lineStream.eof()){
			toomany();
			return;
	}
	if(!lineStream.eof()){
			toomany();
			return;
	}
	if(node2 < MIN_NODE_NUMBER || node2 > MAX_NODE_NUMBER){
		out_of_Range(node2);
		return;
	}
	if(node1 == node2){
		terminals(node1);
		return;
	}
	cout << "Inserted: resistor " << name << " ";
    cout << setprecision(2) << fixed << ohm << " Ohms ";
    cout << node1 << " -> " << node2 << endl;
}


void modifyR(string line){
	string command,name;
	stringstream lineStream (line);
	lineStream >> command;
	lineStream >> name;
	lineStream >> ws;

	if(name == "all"){
		resistor_name();
		return;
	}

	double ohm;
	lineStream >> ohm;
	if (lineStream.fail()){
		if (lineStream.eof()){	//end of file
			toofew();
			return;
		}
		invalid_Argument();
		lineStream.ignore(1000,' ');
		lineStream.clear();
	    return;
	}
	if(ohm < 0){
		negative_resistance();
		return;
	}
	if(lineStream.eof()){
		toofew();
		return;
	}
	if (!lineStream.eof()) {
		toomany();
		return;
	}
	cout << "Modified: resistor " << name << " to " << setprecision(2) << fixed << ohm << " Ohms" << endl;
}

void printR(string line){
	string command,name;
	stringstream lineStream (line);
	lineStream >> command;
	lineStream >> name;
	lineStream >> ws;

	if(lineStream.eof()){
		toofew();
		return;
	}
	if (!lineStream.eof()) {
		toomany();
		return;
	}
	if(name == "all"){
		cout << "Print: all resistors" << endl;
	}
	else {
		cout << "Print: resistor "<< name << endl;
	}
}

void printNode(string line){
	string command,name;
	stringstream lineStream (line);
	lineStream >> command;
	int node;
	lineStream >> node;

	if (lineStream.fail()){  
		if (lineStream.eof()){
            toofew();
            return;
		}

		lineStream >> ws;
		lineStream.clear();
		lineStream >> name;
		if (name == "all"){
			cout << "Print: all nodes" << endl;
			return;
		}
		invalid_Argument();
		lineStream.ignore(1000,' ');
		lineStream.clear();
		return;
	}

	lineStream >> ws;
	if(lineStream.peek() == '.'){
		invalid_Argument();
		return;
		}
	if (node > MAX_NODE_NUMBER){
		out_of_Range(node);
		return;
		}
	if (node < MIN_NODE_NUMBER){
		out_of_Range(node);
		return;
		}

	if(!lineStream.eof()){
		toomany();
		return;
		}
	cout << "Print: node "<< node << endl;
}

void deleteR(string line){
	string command,name;
	stringstream lineStream (line);
	lineStream >> command;
	lineStream >> name;
	lineStream >> ws;

	if(lineStream.eof()){
		toofew();
		return;
	}
	if (!lineStream.eof()) {
		toomany();
		return;
	}
	if(name == "all"){
		cout << "Deleted: all resistors" << endl;
	}
	else {
		cout << "Deleted: resistor "<< name << endl;
	}
}
