#ifndef _TREENODE_H
#define _TREENODE_H

#include "DBentry.h"
#include <cstdlib>
#include <iostream>
#include <cstdlib>
#include <string>
//stores individual nodes of the tree // a pointer to a DBentry that stores the key and data associated with a node

class TreeNode {
private:
    DBentry* entryPtr;
    TreeNode* left;
    TreeNode* right;
public:
    // A useful constructor
    TreeNode(DBentry* _entryPtr);

    // the destructor
    ~TreeNode();

    // sets the left child of the TreeNode.
    void setLeft(TreeNode* newLeft);

    // sets the right child of the TreeNode
    void setRight(TreeNode* newRight);

    // gets the left child of the TreeNode.
    TreeNode* getLeft() const;

    // gets the right child of the TreeNode
    TreeNode* getRight() const;

    // returns a pointer to the DBentry the TreeNode contains. 
    DBentry* getEntry() const;
};

#endif 

