// ------------------------------------------------ bintree.h -------------------------------------------------------
// Sean O'Dell, CSS 502A
// Creation Date: 1/21/2019
// Date of Last Modification: 2/03/2019
// --------------------------------------------------------------------------------------------------------------------
// Purpose - Data structure declaration of a binary tree
// --------------------------------------------------------------------------------------------------------------------
// Allows for the creation, storage, and conversion to and from an array.  Functionality for equality operators 
// is included. Size checking for the array was not required. 
// --------------------------------------------------------------------------------------------------------------------
#ifndef BINTREE_H
#define BINTREE_H
#include "nodedata.h"
#include <vector>

class BinTree
{

	// ------------------------------------<<-----------------------------------------------
	// Description: Prints tree contents in-order from smallest to largest
	// ---------------------------------------------------------------------------------------------------
	friend std::ostream& operator<<(std::ostream &out, const BinTree& tree);

public:

	// ------------------------------------BinTree-----------------------------------------------
	// Description: constructor for binary tree
	// ---------------------------------------------------------------------------------------------------
	BinTree();								// constructor

	// ------------------------------------BinTree-----------------------------------------------
	// Description: copy constructor for binary tree
	// ---------------------------------------------------------------------------------------------------
	BinTree(const BinTree &);				// copy constructor

	// ------------------------------------~BinTree-----------------------------------------------
	// Description: destructor for binary tree.  Deletes both Data nodes and the data held within the Data node
	// ---------------------------------------------------------------------------------------------------
	~BinTree();								// destructor, calls makeEmpty	

	// ------------------------------------isEmpty-----------------------------------------------
	// Description: returns if tree is empty
	// ---------------------------------------------------------------------------------------------------
	bool isEmpty() const;					// true if tree is empty, otherwise false

	// ------------------------------------makeEmpty-----------------------------------------------
	// Description: empties tree. Deletes both Data nodes and the data held within the Data node
	// ---------------------------------------------------------------------------------------------------
	void makeEmpty();						// make the tree empty so isEmpty returns true

	// ------------------------------------=operator-----------------------------------------------
	// Description: assignment, copies the information from the given binary tree to the assigned binary tree
	// ---------------------------------------------------------------------------------------------------
	BinTree& operator=(const BinTree &);

	// ------------------------------------==operator-----------------------------------------------
	// Description: determines if two binary trees are equivalent
	// ---------------------------------------------------------------------------------------------------
	bool operator==(const BinTree &) const;

	// ------------------------------------!=operator-----------------------------------------------
	// Description: determines if two binary trees are not equivalent
	// ---------------------------------------------------------------------------------------------------
	bool operator!=(const BinTree &) const;

	// ------------------------------------insert-----------------------------------------------
	// Description: inserts data into the binary tree
	// ---------------------------------------------------------------------------------------------------
	bool insert(NodeData*);

	// ------------------------------------retrieve-----------------------------------------------
	// Description: retrieves data held within a node and reports if data is found
	// ---------------------------------------------------------------------------------------------------
	bool retrieve(const NodeData& data, NodeData* & actual) const;

	// ------------------------------------getHeight-----------------------------------------------
	// Description:finds height of a given value in the tree
	// ---------------------------------------------------------------------------------------------------
	int getHeight(const NodeData&) const;

	// ------------------------------------displaySideways-----------------------------------------------
	// Description: displays the tree sideways
	// ---------------------------------------------------------------------------------------------------
	void displaySideways() const;			// provided below, displays the tree sideways

	// ------------------------------------bstreeToArray-----------------------------------------------
	// Description: converts binary tree into the given array and resets the binary tree
	// ---------------------------------------------------------------------------------------------------
	void bstreeToArray(NodeData* []);

	// ------------------------------------arrayToBSTree-----------------------------------------------
	// Description: converts a given array into a balanced binary seatch tree and resets the array
	// ---------------------------------------------------------------------------------------------------
	void arrayToBSTree(NodeData*[]);


private:

	struct Node
	{
		NodeData* data;						// pointer to data object
		Node* left;							// left subtree pointer
		Node* right;						// right subtree pointer
	};

	Node* root;								// root of the tree
	int size;								// number of nodes in the tree

// utility functions

	// ------------------------------------inorderHelper-----------------------------------------------
	// Description: inorder helper for << overload
	// ---------------------------------------------------------------------------------------------------
	void inorderHelper(Node * root, std::ostream & out) const;

	// ------------------------------------sideways-----------------------------------------------
	// Description: helper for display sideways
	// ---------------------------------------------------------------------------------------------------
	void sideways(Node*, int) const;			// provided below, helper for displaySideways()

	// ------------------------------------deleteSubTree-----------------------------------------------
	// Description: deletes the given node and nodeData and all the information below it
	// ---------------------------------------------------------------------------------------------------
	void deleteSubTree(Node*);

	// ------------------------------------getNodeHeight-----------------------------------------------
	// Description: gets height of the given node
	// ---------------------------------------------------------------------------------------------------
	int getNodeHeight(const Node*) const;

	// ------------------------------------deepCopy-----------------------------------------------
	// Description: creates a deep copy of all the nodes below the given node
	// ---------------------------------------------------------------------------------------------------
	void deepCopy(const Node*, Node*);

	// ------------------------------------subTreeEqual-----------------------------------------------
	// Description: determines if given subtrees are equivalent
	// ---------------------------------------------------------------------------------------------------
	bool subTreeEqual(const Node*, const Node*) const;

	// ------------------------------------toArrayInorderHelper-----------------------------------------------
	// Description: helper to convert binary tree to an array
	// ---------------------------------------------------------------------------------------------------
	void toArrayInorderHelper(Node * root, vector<NodeData*>&);

	// ------------------------------------createBSTFromArray-----------------------------------------------
	// Description: creates balanced binary search tree from array
	// ---------------------------------------------------------------------------------------------------
	void createBSTFromArray(vector<NodeData*>, int, int);

};
#endif