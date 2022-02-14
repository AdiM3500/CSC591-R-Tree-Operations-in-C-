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
	void inOrderTraversal(Node* focusNode);
};
