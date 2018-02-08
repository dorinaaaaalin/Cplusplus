#include <cstdlib>
#include "TreeDB.h"
#include <iostream>
#include <string>
using namespace std;

//constructor
TreeDB::TreeDB() {
    root = NULL;
    probesCount = 0;
}

//delete the entire tree using recursion
void TreeDB::deleteTree(TreeNode* myroot) {
    if (myroot == NULL) return;
    deleteTree(myroot->getLeft());
    deleteTree(myroot->getRight());
    //cout << "remove all removing .... " << myroot->getEntry()->getName() << endl;
    delete myroot;
}

//destructor
TreeDB::~TreeDB() {
    deleteTree(root);
}

// inserts the entry pointed to by newEntry into the database. 
// If an entry with the same key as newEntry's exists 
// in the database, it returns false. Otherwise, it returns true.

bool TreeDB::insert(DBentry* newEntry) {
    //if(newEntry == NULL) return false;
    if (root == NULL) {
        TreeNode* temp = new TreeNode(newEntry);
        root = temp;
        return true;
    }
    return insertHelper(newEntry, root);
}

//insert helper that goes throu the whole tree recursively till you find an empty space to insert the new Entry
bool TreeDB::insertHelper(DBentry* newEntry, TreeNode* root) {
    if (newEntry->getName() == root->getEntry()->getName())
        return false;

    if (newEntry->getName() < root->getEntry()->getName()) {
        if (root->getLeft() == NULL) {
            //cout << "insert on the lefffttt!!" << endl;
            TreeNode* temp = new TreeNode(newEntry);
            root->setLeft(temp);
            return true;
        } else
            return insertHelper(newEntry, root->getLeft());
    }

    if (newEntry->getName() > root->getEntry()->getName()) {
        if (root->getRight() == NULL) {
            TreeNode* temp = new TreeNode(newEntry);
           // cout << "insert on the righttt!!" << endl;
            root->setRight(temp);
            return true;
        } else
            return insertHelper(newEntry, root->getRight());
    }
}

int TreeDB::getProbes() const {
    return probesCount;
}

// searches the database for an entry with a key equal to name.
// If the entry is found, a pointer to it is returned.
// If the entry is not found, the NULL pointer is returned.
// Also sets probesCount

DBentry* TreeDB::find(string name) {
    probesCount = 0;
    if (root == NULL) {
        cout << "Error: entry does not exist " << endl;
        return NULL;
    }
    return findHelper(name, root);
}


//find helper using recursion to find the data entry that has the same name,
//also adds probesCount everytime u enter this function
DBentry* TreeDB::findHelper(string name, TreeNode* r) {
    probesCount++;
    if (name == r->getEntry()->getName()) {
        //cout << "find this " << r->getEntry()->getName() << "  its " << r->getEntry()->getActive() << endl;
        return r->getEntry();
    }
    else if (name < r->getEntry()->getName()) {
        if (r->getLeft() == NULL) {
            return NULL;
        } else
            return findHelper(name, r->getLeft());
    }
    else if (name > r->getEntry()->getName()) {
        if (r->getRight() == NULL) {
            return NULL;
        } else
            return findHelper(name, r->getRight());
    }
}

// deletes all the entries in the database.
void TreeDB::clear() {
    if (root != NULL) {
        deleteTree(root);
        root = NULL;
        //cout << "Success" << endl;
    }

}

// deletes the entry with the specified name (key) from the database.
// If the entry was indeed in the database, it returns true.
// Returns false otherwise.
bool TreeDB::remove(string name) {

    if (find(name) == NULL) {
        cout << "TREEDB REMOVE: DOES NOT EXIST" << endl;
        return false;
    }
    removeHelper(name, NULL, root);
    cout << "Success" << endl;
    return true;
}

//remove helper using recursion to remove the data entry that has the same name,
//checks three cases after u find the right data entry

void TreeDB::removeHelper(string name, TreeNode* prev, TreeNode* cur) {
    DBentry* entryPtr = cur->getEntry();
    if (name < entryPtr->getName()) {
        if (cur->getLeft() != NULL) {
            prev = cur;
            cur = cur->getLeft();
            removeHelper(name, prev, cur);
        }
        return;
    } else if (name > entryPtr->getName()) {
        if (cur->getRight() != NULL) {
            prev = cur;
            cur = cur->getRight();
            removeHelper(name, prev, cur);
        }
        return;
    } else {
        //leaf
        if ((cur->getLeft() == NULL) && (cur->getRight() == NULL)) {
          //  cout << "case one leaf" << endl;
            if(prev != NULL){
                if (prev->getLeft() == cur)
                    prev->setLeft(NULL);
                else
                    prev->setRight(NULL);
            }
            else
                root = NULL;
            delete cur;
        }            //delete a node w/ right child but no left child
        else if ((cur->getLeft() == NULL) && (cur->getRight() != NULL)) {
          //  cout << "case 2 has a right child" << endl;
            if(prev!=NULL){
                 if (prev->getLeft() == cur)
                    prev->setLeft(cur->getRight());
                 else
                    prev->setRight(cur->getRight());
            //prev->setLeft(cur->getRight());
                 cur->setRight(NULL);
            }
            else{
                if(cur->getRight()!=NULL)
                root = cur->getRight();
                else
                    root = cur->getLeft();
            }
            delete cur;
        }            //delete a node w/ left child but no right child
        else if ((cur->getLeft() != NULL) && (cur->getRight() == NULL)) {
          //  cout << "case 3 has a left child" << endl;
            if(prev != NULL){
                  if (prev->getLeft() == cur)
                    prev->setLeft(cur->getLeft());
                 else
                    prev->setRight(cur->getLeft());
            //prev->setLeft(cur->getLeft());
            cur->setLeft(NULL);
            }
            else{
                if(cur->getRight()!=NULL)
                root = cur->getRight();
                else
                    root = cur->getLeft();
            }
            delete cur;
        } else if((cur->getLeft() != NULL) && (cur->getRight() != NULL)){
         //   cout << "two subtrees" << endl;
            DBentry* temp = maximum(cur->getLeft());
            cur->getEntry()->setName(temp->getName());
            cur->getEntry()->setIPaddress(temp->getIPaddress());
            cur->getEntry()->setActive(temp->getActive());
            removeHelper(temp->getName(), cur, cur->getLeft());
        }
    }
}

//only used in remove helper 
//this function searches the maximum treenode name on the left side of TreeNode* r
DBentry* TreeDB::maximum(TreeNode* r) {
    if (r->getRight() == NULL)
        return r->getEntry();
    return maximum(r->getRight());
}

// prints the number of probes stored in probesCount
void TreeDB::printProbes() const {
    cout << probesCount << endl;
    // cout << "I have these many probsCount" << probesCount << endl;
}

// computes and prints out the total number of active entries
// in the database (i.e. entries with active==true).
void TreeDB::countActive() const {
    int count = 0;
    if (root == NULL)
        cout << count << endl;
        //cout << "HOW MANY ACTIVE WEBSTIES????" << count << endl;
    else {
        int c = countActiveHelper(root, count);
        cout << c << endl;
        //cout << "HOW MANY ACTIVE WEBSTIES????" << c << endl;
    }
}

//countACtive helper using recursion to traverse the tree and count active websites
int TreeDB::countActiveHelper(TreeNode* root, int& count) const {
    //int count = 0;
    if (root == NULL)
        return count;

    if (root->getEntry()->getActive() == true)
        count++;

    countActiveHelper(root->getLeft(), count);
    countActiveHelper(root->getRight(), count);

}

// Prints the entire tree, in ascending order of key/name
// The entries are printed one per line, using the
// operator<< for DBentry.
ostream& operator<<(ostream& out, const TreeDB& rhs) {
    ///cout << "IM IN OPERATOR <<" << endl;
    if (rhs.root == NULL) {
        //cout << "IM IN OPERATOR << rooot is nulll" << endl;
        return out;
    }
    rhs.printHelper(out, rhs.root);
    return out;
}


//print helper using recursion to traverse the whole tree and print the data inOrder
void TreeDB::printHelper(ostream& out, TreeNode* r)const {
    if (r->getLeft() != NULL)
        printHelper(out, r->getLeft());
    operator<<(out, *r->getEntry());
    if (r->getRight() != NULL)
        printHelper(out, r->getRight());
}


