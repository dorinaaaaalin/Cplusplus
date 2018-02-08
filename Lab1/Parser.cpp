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
	cout<<"Error: resistor name cannot be the keyword \"all\""<<endl;
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
	int node1,node2, c;
	double ohm;

	if (lineStream.eof()){	//check for end of file
		toofew();
		return;
	}

	lineStream >> name;
	lineStream >> ws;
	if (lineStream.eof()){	//check for end of file
		toofew();
		return;
	}
	if (name == "all"){	//if name is all
		resistor_name();
		return;
	}

	lineStream >> ohm;
	if (lineStream.fail()){	//check if it is a real number
		invalid_Argument();
		lineStream.ignore(1000,' ');	//ignores the first 1000 characters or until it sees a space
		lineStream.clear();
	    return;
	}

	if(ohm < 0) {	
		//invalid if next character is not a new line, tab or space
		if(lineStream.peek()!= '\n' && lineStream.peek() != '\t' && lineStream.peek() != ' '){	
			invalid_Argument();																
			lineStream.ignore(1000,' ');
			return;
		}//else return resistance is negative
		negative_resistance();	
		return;
}
	lineStream >> ws;
	if (lineStream.eof()){	//check for end of file
		toofew();
		return;
	}

	lineStream >> node1;
	if (lineStream.fail()) {//check if it is a real number
		invalid_Argument();
	    return;
	} else if(lineStream.peek()!= -1 && lineStream.peek() != '\t' && lineStream.peek() != ' '){
		invalid_Argument();
		return;
	} else if (node1 < MIN_NODE_NUMBER || node1 > MAX_NODE_NUMBER) {	//check if node is in range
		out_of_Range(node1);
		return;
	}
	lineStream >> ws;
	if (lineStream.eof()){	//check for end of file
		toofew();
		return;
	}
	
	lineStream >> node2;
	cout<<node2<<endl;
	if (lineStream.fail() && lineStream.eof()){	//check if it is a real number and the end of file
		cout<<"failed"<<endl;
		invalid_Argument();
	    return;
	} 
	if(!lineStream.eof()){
		if(lineStream.peek()!= -1 || lineStream.peek() != '\t' || lineStream.peek() != ' '){
			invalid_Argument();
			return;
		} else {
			if(node1 == node2){	//if the two nodes are equal, return same terminals
				terminals(node1);
				return;
			}else {
				//checks if there is anything after the node, if yes, return toomany
				string temp;
				if(lineStream >> temp){
					toomany();
					return;
				}
			}
		}
	} else if (node2 < MIN_NODE_NUMBER || node2 > MAX_NODE_NUMBER) {	//checks if node is in the boundary
			out_of_Range(node2);
			return;
	} else if(node1 == node2){
			terminals(node1);
			return;
	}

	//eats up the whitespaces 
	lineStream >> ws;
	if(!lineStream.eof()){
		toomany();
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

	if (lineStream.eof()){	//check for end of file
			toofew();
			return;
	}
	
	double ohm;
	lineStream >> ohm;
	if (lineStream.fail()){
		invalid_Argument();
		lineStream.ignore(1000,' ');
	    return;
	}
	if(ohm < 0.0){
		
		negative_resistance();
		return;
	}
	if(!lineStream.eof()){
		if(lineStream.peek()!= ' ' && lineStream.peek()!= '\t'){
			invalid_Argument();
			lineStream.ignore(1000,' ');
			return;
		}else {
			string temp;
			if(lineStream >> temp){
				toomany();
				return;
			}
		}
	}
	cout << "Modified: resistor " << name << " to " << setprecision(2) << fixed << ohm << " Ohms" << endl;
}

void printR(string line){
		string command,name;
	stringstream lineStream (line);
	lineStream >> command;
	lineStream >> ws;

	if(lineStream.eof()){
		toofew();
		return;
	} 
	lineStream >> name;
	lineStream >> ws;
	if(name == "all"){
		if (!lineStream.eof()){
			toomany();
			return;
		}
		if(lineStream.peek()== ' '){
			invalid_Argument();
			return;
		}
		cout << "Print: all resistors" << endl;
		return;
	}
	string temp;	//temporary string to check if there is anything after the name
	lineStream >> ws;
	if (!lineStream.eof()){ 
		toomany();
		return;
	}
	else {
		cout << "Print: resistor "<< name << endl;
		return;
	}
}

void printNode(string line){
	string command,name;
	stringstream lineStream (line);
	lineStream >> command;
	lineStream >> ws;

	if (lineStream.eof()){
            toofew();
            return;
	}
	int node;
	lineStream >> node;
	if (lineStream.fail()){  
		lineStream.clear();
		lineStream >> name;
		lineStream >> ws;
		if (name == "all"){
			if (!lineStream.eof()){
				toomany();
				return;
			}
			cout << "Print: all nodes" << endl;
			return;
		}
		invalid_Argument();
		lineStream.ignore(1000,' ');
		lineStream.clear();
		return;
	}

	lineStream >> ws;
	if(lineStream.peek()!= -1 && lineStream.peek() != '\t' && lineStream.peek() != ' '){
		if (node > MAX_NODE_NUMBER || node < MIN_NODE_NUMBER){
		out_of_Range(node);
		return;
		}
		invalid_Argument();
		return;
		}
	if (node > MAX_NODE_NUMBER || node < MIN_NODE_NUMBER){
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
	lineStream >> ws;

	if(lineStream.eof()){
		toofew();
		return;
	} 
	lineStream >> name;
	lineStream >> ws;
	if(name == "all"){
		if (!lineStream.eof()){
			toomany();
			return;
		}
		if(lineStream.peek()== ' '){
			invalid_Argument();
			return;
		}
		cout << "Deleted: all resistors" << endl;
		return;
	}
	string temp;	//temporary string to check if there is anything after the name
	lineStream >> ws;
	if (!lineStream.eof()){ 
		toomany();
		return;
	}
	else {
		cout << "Deleted: resistor "<< name << endl;
		return;
	}
}
