// ------------------------------------------------ bintree.cpp -------------------------------------------------------
// Sean O'Dell, CSS 502A
// Creation Date: 1/21/2019
// Date of Last Modification: 2/03/2019
// --------------------------------------------------------------------------------------------------------------------
// Purpose - Data structure implementation of a binary tree
// --------------------------------------------------------------------------------------------------------------------
// Allows for the creation, storage, and conversion to and from an array.  Functionality for equality operators 
// is included. Size checking for the array was not required. 
// --------------------------------------------------------------------------------------------------------------------

#include "bintree.h"
#include <queue>

// ------------------------------------<<-----------------------------------------------
// Description: Prints tree contents in-order from smallest to largest
// ---------------------------------------------------------------------------------------------------
std::ostream & operator<<(std::ostream & out, const BinTree & tree)
{
	tree.inorderHelper(tree.root, out);
	out << std::endl;
	return out;
}

// ------------------------------------BinTree-----------------------------------------------
// Description: constructor for binary tree
// ---------------------------------------------------------------------------------------------------
BinTree::BinTree()
{
	this->root = nullptr;
	this->size = 0;
}

// ------------------------------------BinTree-----------------------------------------------
// Description: copy constructor for binary tree
// ---------------------------------------------------------------------------------------------------
BinTree::BinTree(const BinTree& other)
{
	this->root = new Node;
	NodeData* otherRootNodeData = new NodeData(*other.root->data);
	this->root->data = otherRootNodeData;
	this->root->left = nullptr;
	this->root->right = nullptr;
	deepCopy(other.root, this->root);
	this->size = other.size;
}

// ------------------------------------~BinTree-----------------------------------------------
// Description: destructor for binary tree.  Deletes both Data nodes and the data held within the Data node
// ---------------------------------------------------------------------------------------------------
BinTree::~BinTree()
{
	makeEmpty();
	//deleteSubTree(this->root);
}

// ------------------------------------isEmpty-----------------------------------------------
// Description: returns if tree is empty
// ---------------------------------------------------------------------------------------------------
bool BinTree::isEmpty() const
{
	if (this->root == nullptr)
	{
		return true;
	}
	return false;
}

// ------------------------------------makeEmpty-----------------------------------------------
// Description: empties tree. Deletes both Data nodes and the data held within the Data node
// ---------------------------------------------------------------------------------------------------
void BinTree::makeEmpty()
{
	deleteSubTree(this->root);
	this->root = nullptr;
	this->size = 0;
}

// ------------------------------------=operator-----------------------------------------------
// Description: assignment, copies the information from the given binary tree to the assigned binary tree
// ---------------------------------------------------------------------------------------------------
BinTree & BinTree::operator=(const BinTree & other)
{
	if (this != &other)
	{
		deleteSubTree(this->root);
		this->root = new Node;
		this->root->data = new NodeData(*other.root->data);
		this->root->left = nullptr;
		this->root->right = nullptr;
		deepCopy(other.root, this->root);
	}
	return (*this);
}

// ------------------------------------==operator-----------------------------------------------
// Description: determines if two binary trees are equivalent
// ---------------------------------------------------------------------------------------------------
bool BinTree::operator==(const BinTree & other) const
{
	if (this == &other) return true;
	return subTreeEqual(this->root, other.root);
}

// ------------------------------------!=operator-----------------------------------------------
// Description: determines if two binary trees are not equivalent
// ---------------------------------------------------------------------------------------------------
bool BinTree::operator!=(const BinTree & other) const
{
	return !(*this == other);
}

// ------------------------------------insert-----------------------------------------------
// Description: inserts data into the binary tree
// ---------------------------------------------------------------------------------------------------
bool BinTree::insert(NodeData * data)
{
	if (data == nullptr) return false;
	Node* newDataNodePtr = new Node;
	newDataNodePtr->data = data;
	newDataNodePtr->left = nullptr;
	newDataNodePtr->right = nullptr;
		if (this->root == nullptr)
	{
		this->root = newDataNodePtr;
		this->size = 1;
		return true;
	} else
	{
		Node* currentNode = this->root;
		while (true)
		{
			if (*data < *currentNode->data)
			{
				if (currentNode->left == nullptr)
				{
					currentNode->left = newDataNodePtr;
					this->size++;
					return true;
				} else
				{
					currentNode = currentNode->left;
				}
			} else if (*data > *currentNode->data)
			{
				if (currentNode->right == nullptr)
				{
					currentNode->right = newDataNodePtr;
					this->size++;
					return true;
				} else
				{
					currentNode = currentNode->right;
				}
			} else
			{
				delete newDataNodePtr;
				return false;
			}
		}
	}
	return false;
}

// ------------------------------------retrieve-----------------------------------------------
// Description: retrieves data held within a node and reports if data is found
// ---------------------------------------------------------------------------------------------------
bool BinTree::retrieve(const NodeData& data, NodeData* & actual) const
{
	Node* currentNode = this->root;
	while (currentNode != nullptr)
	{
		if (data < *currentNode->data)
		{
			currentNode = currentNode->left;
		} else if (data > *currentNode->data)
		{
			currentNode = currentNode->right;
		} else if (data == *currentNode->data)
		{
			actual = currentNode->data;
			return true;
		}
	}
	actual = nullptr;
	return false;
}

// ------------------------------------getHeight-----------------------------------------------
// Description:finds height of a given value in the tree
// ---------------------------------------------------------------------------------------------------
int BinTree::getHeight(const NodeData & data) const
{
	bool nodeFound = false;
	Node* currentNode;
	currentNode = this->root;
	queue<Node*> nodeQueue;
	nodeQueue.push(currentNode);
	while (!nodeQueue.empty())
	{
		currentNode = nodeQueue.front();
		nodeQueue.pop();
		if (*currentNode->data == data)
		{
			nodeFound = true;
			break;
		}
		if (currentNode->left != nullptr)
		{
			nodeQueue.push(currentNode->left);
		}
		if (currentNode->right != nullptr)
		{
			nodeQueue.push(currentNode->right);
		}
	}
	if (nodeFound == false) return 0;
	return getNodeHeight(currentNode);
}

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const
{
	sideways(root, 0);
}

// ------------------------------------bstreeToArray-----------------------------------------------
// Description: converts binary tree into the given array and resets the binary tree
// ---------------------------------------------------------------------------------------------------
void BinTree::bstreeToArray(NodeData *resultArray[])
{
	vector<NodeData*> resultVector;
	toArrayInorderHelper(this->root, resultVector);
	int count = 0;
	for (NodeData* data : resultVector)
	{
		resultArray[count] = data;
		count++;
	}
	this->makeEmpty();
}

// ------------------------------------arrayToBSTree-----------------------------------------------
// Description: converts a given array into a balanced binary seatch tree and resets the array
// ---------------------------------------------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData *input[])
{
	vector<NodeData*> inputVector;
	int count = 0;
	while (input[count] != nullptr)
	{
		inputVector.push_back(input[count]);
		input[count] = nullptr; // does this need to be NULL?
		count++;
	}
	this->makeEmpty();
	createBSTFromArray(inputVector, 0, inputVector.size() - 1);
	vector<NodeData*>::iterator it;
	for (it = inputVector.begin(); it < inputVector.end(); it++)
	{
		delete *it;
	}
}


// utility functions

// ------------------------------------inorderHelper-----------------------------------------------
// Description: inorder helper for << overload
// ---------------------------------------------------------------------------------------------------
void BinTree::inorderHelper(Node * root, std::ostream & out) const
{
	if (root != nullptr)
	{
		inorderHelper(root->left, out);
		out << *root->data << " ";
		inorderHelper(root->right, out);
	}
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const
{
	if (current != NULL)
	{
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--)
		{
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}

// ------------------------------------deleteSubTree-----------------------------------------------
// Description: deletes the given node and nodeData and all the information below it
// ---------------------------------------------------------------------------------------------------
void BinTree::deleteSubTree(Node * subTreeTop)
{
	if (subTreeTop == nullptr) return;
	queue<Node*> deletionQueue;
	Node* currentNode = subTreeTop;
	deletionQueue.push(currentNode);
	while (!deletionQueue.empty())
	{
		if (currentNode->left != nullptr)
		{
			deletionQueue.push(currentNode->left);
		}
		if (currentNode->right != nullptr)
		{
			deletionQueue.push(currentNode->right);
		}
		deletionQueue.pop();
		delete currentNode->data;
		delete currentNode;
		this->size--;
		if (!deletionQueue.empty())
		{
			currentNode = deletionQueue.front();
		}
	}
}

// ------------------------------------getNodeHeight-----------------------------------------------
// Description: gets height of the given node
// ---------------------------------------------------------------------------------------------------
int BinTree::getNodeHeight(const Node* node) const
{
	if (node == nullptr) return 0;
	return max(getNodeHeight(node->left), getNodeHeight(node->right)) + 1;
}

// ------------------------------------deepCopy-----------------------------------------------
// Description: creates a deep copy of all the nodes below the given node
// ---------------------------------------------------------------------------------------------------
void BinTree::deepCopy(const Node * otherNode, Node * copiedNode)
{
	if (otherNode == nullptr || (otherNode->left == nullptr && otherNode->right == nullptr)) return;
	if (otherNode->left != nullptr)
	{
		Node* left = new Node;
		left->data = new NodeData(*otherNode->left->data);
		left->left = nullptr;
		left->right = nullptr;
		copiedNode->left = left;
		deepCopy(otherNode->left, copiedNode->left);
	}
	if (otherNode->right != nullptr)
	{
		Node* right = new Node;
		right->data = new NodeData(*otherNode->right->data);
		right->left = nullptr;
		right->right = nullptr;
		copiedNode->right = right;
		deepCopy(otherNode->right, copiedNode->right);
	}
}

// ------------------------------------subTreeEqual-----------------------------------------------
// Description: determines if given subtrees are equivalent
// ---------------------------------------------------------------------------------------------------
bool BinTree::subTreeEqual(const Node * first, const Node * second) const
{
	if (first == nullptr && second == nullptr)
	{
		return true;
	} else if (first != nullptr && second != nullptr)
	{
		if (first->data == second->data)
		{
			bool firstResult = subTreeEqual(first->left, second->left);
			bool secondResult = subTreeEqual(first->right, second->right);
			return (firstResult == false || secondResult == false) ? false : true;
		} else
		{
			return false;
		}
	} else
	{
		return false;
	}
}

// ------------------------------------toArrayInorderHelper-----------------------------------------------
// Description: helper to convert binary tree to an array
// ---------------------------------------------------------------------------------------------------
void BinTree::toArrayInorderHelper(Node * root, vector<NodeData*> &resultVector)
{
	if (root == nullptr) return;
	toArrayInorderHelper(root->left, resultVector);
	resultVector.push_back(new NodeData(*root->data));
	toArrayInorderHelper(root->right, resultVector);
}

// ------------------------------------createBSTFromArray-----------------------------------------------
// Description: creates balanced binary search tree from array
// ---------------------------------------------------------------------------------------------------
void BinTree::createBSTFromArray(vector<NodeData*> vec, int low, int high)
{
	if (low > high) return;
	this->insert(new NodeData(*vec[(low + high) / 2]));
	createBSTFromArray(vec, low, (low + high) / 2 - 1);
	createBSTFromArray(vec, (low + high) / 2 + 1, high);
}