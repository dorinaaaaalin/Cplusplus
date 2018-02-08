#ifndef _TREEDB_H
#define _TREEDB_H

#include "TreeNode.h"
#include "DBentry.h"

class TreeDB {

private:
   TreeNode* root;
   int probesCount;
   
   //insert helper that goes throu the whole tree recursively till you find an empty space to insert the new Entry
   bool insertHelper(DBentry* newEntry,TreeNode* root);
   
   //find helper using recursion to find the data entry that has the same name,
    //also adds probesCount everytime u enter this function
   DBentry* findHelper(string name,TreeNode* r);
   
  //remove helper using recursion to remove the data entry that has the same name,
    //checks three cases after u find the right data entry
   void removeHelper(string name,TreeNode* prev,TreeNode* cur);
   
   //delete the entire tree using recursion
   void deleteTree(TreeNode* _root);
   
   //funtion that returns probesCOunt
   int getProbes() const;
   
    //countACtive helper using recursion to traverse the tree and count active websites
   int countActiveHelper(TreeNode* root,int& count)const;
   
   //only used in remove helper 
   //this function searches the maximum treenode name on the left side of TreeNode* r
   DBentry* maximum(TreeNode* r);
   
   //print helper using recursion to traverse the whole tree and print the data inOrder
   void printHelper(ostream& out,TreeNode* r) const;

public:
   // the default constructor, creates an empty database.
   TreeDB();

   // the destructor, deletes all the entries in the database.
   ~TreeDB();

   // inserts the entry pointed to by newEntry into the database. 
   // If an entry with the same key as newEntry's exists 
   // in the database, it returns false. Otherwise, it returns true.
   bool insert(DBentry* newEntry); 

   // searches the database for an entry with a key equal to name.
   // If the entry is found, a pointer to it is returned.
   // If the entry is not found, the NULL pointer is returned.
   // Also sets probesCount
   DBentry* find(string name);

   // deletes the entry with the specified name (key)  from the database.
   // If the entry was indeed in the database, it returns true.
   // Returns false otherwise.
   // See section 6 of the lab handout for the *required* removal method.
   // If you do not use that removal method (replace deleted node by
   // maximum node in the left subtree when the deleted node has two children)
   // you will not match exercise's output.
   bool remove(string name);
	
   // deletes all the entries in the database.
   void clear();
    
   // prints the number of probes stored in probesCount
   void printProbes() const;
   
   // computes and prints out the total number of active entries
   // in the database (i.e. entries with active==true).
   void countActive () const;
   
 
   
   // Prints the entire tree, in ascending order of key/name
   friend ostream& operator<< (ostream& out, const TreeDB& rhs);
}; 

// You *may* choose to implement the function below to help print the 
// tree.  You do not have to implement this function if you do not wish to.
ostream& operator<< (ostream& out, TreeNode* rhs);   
   
#endif 

