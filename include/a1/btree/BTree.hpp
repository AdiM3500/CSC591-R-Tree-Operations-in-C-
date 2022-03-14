#include <iostream>
#include <algorithm>
#include<iterator>
#include <cmath>
#include <optional>

#include <vector>


using key_t = int;
using key_list_t = std::vector< key_t >;

class Node {


public:

	static const uint32_t num_keys = 2;  //changing node capacity to 2. max children will be 3.
	int keys[num_keys];
	Node* children[num_keys + 1];
	int n = 0;          //var to keep track of the number of keys


	/**
	 * Create a new node with a single key and no children
	 */
	Node(int key) {
		keys[0] = key;
		children[0] = NULL;
		children[1] = NULL;
		children[2] = NULL;
		n += 1;							//every time you add a new node with a key, number of keys increases by one
	}

	/**
	 * Create a new node with no children from a list of keys
	 */
	Node( key_list_t keys_to_insert )
	{
		std::copy( keys_to_insert.cbegin(), keys_to_insert.cend(), keys );
		std::fill( children, children + num_keys + 1, static_cast< Node * >( NULL ) );
		n = keys_to_insert.size();
	}

	bool check_leaf();     //function to check if node is a leaf node.


	friend class BTree;
};



class BTree {

public:

	Node* root = NULL; //ROOT IS A POINTER TO A NODE OBJECT

	key_list_t listOfKeys{};
	/**
	 * Given a key, retrieves a pointer to the node containing that key if it exists.
	 * Otherwise, std::nullopt is returned.
	 */

	std::optional< Node * > find( key_t key );

	/**
	 * Returns a list of all keys in the tree within a given half-open interval, [lower_bound, upper_bound)
	 */
	key_list_t find( key_t lower_bound, key_t upper_bound );

	Node* lookup(Node* focusNode, key_t key);
	void inOrderRangeTraversal (Node* focusNode, key_t lower, key_t upper);
	void AddKey(int key);
	void insertInNonFullNode(Node* focusNode, int key);				//function to insert a key into a node when it is non-full.
	void inOrderTraversal(Node* focusNode);
	bool inOrderComparisonTraversal (Node* focusNode1, Node* focusNode2);		//function to traverse the elements of 2 b trees and compare each key
	bool operator == ( BTree other ) const;
	int  findMid(Node* focusNode, int virtualNode[], int key);    //THIS DOES NOT WORK. VirtualNode[] doesn't work with std::sort when passed as an argument to a function
	Node* insertInFullNode(Node* parentNode, int key);

};
