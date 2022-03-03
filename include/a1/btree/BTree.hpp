#include <iostream>
#include <algorithm>
#include<iterator>
#include <cmath>


class Node {


public:

	static const uint32_t num_keys = 2;  //changing node capacity to 2. max children will be 3.
	int keys[num_keys];
	Node* children[num_keys + 1];
	int n = 0;          //var to keep track of the number of keys


	Node(int key) {
		keys[0] = key;
		children[0] = NULL;
		children[1] = NULL;
		children[2] = NULL;
		n += 1;							//every time you add a new node with a key, number of keys increases by one
	}

	bool check_leaf();     //function to check if node is a leaf node.


	friend class BTree;
};



class BTree {

public:

	Node* root = NULL; //ROOT IS A POINTER TO A NODE OBJECT


	void AddKey(int key);
	void insertInNonFullNode(Node* focusNode, int key);				//function to insert a key into a node when it is non-full.
	void inOrderTraversal(Node* focusNode);
	bool inOrderComparisonTraversal (Node* focusNode1, Node* focusNode2);		//function to traverse the elements of 2 b trees and compare each key
	bool operator == ( BTree other ) const;
	int  findMid(Node* focusNode, int virtualNode[], int key);    //THIS DOES NOT WORK. VirtualNode[] doesn't work with std::sort when passed as an argument to a function
};
