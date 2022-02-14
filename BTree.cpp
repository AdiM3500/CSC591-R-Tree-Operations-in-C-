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

//if node has no children, then node is a leaf
bool Node::check_leaf() {

	if (children[0] == NULL && children[1] == NULL && children[2] == NULL)
		return true;

	else return false;
}

void BTree::AddKey(int key) {

	Node* newNode = new Node(key);

	if (root == NULL) {

		root = newNode;
	
	}

	else {

		Node* focusNode = root;
		Node* parent;

		while (true) {

			parent = focusNode;

			//check if the node is a leaf
			if (focusNode->check_leaf()) {

				//if there is space in the node, add the new key to the node and sort it
				if (focusNode->n < focusNode->num_keys) {

					
					int	index = focusNode->n;
					focusNode->keys[index] = key;
					focusNode->n += 1;  //increase number of keys counter after adding the new key
					std::sort(focusNode->keys, focusNode->keys + focusNode->n);   //sort the keys inside the node
					return;
				}


				else {

					std::cout << " the node's already full!" << std::endl;


					//splitting the root
					if (focusNode == root) {



						/*this is not a Node object. It is an array of integers that stores the keys of the focusNode, along with the overflown key as well.
						Used for finding the middle element which needs to be pushed up to the new root. */
						int virtualNode[focusNode->num_keys + 1];

						//copy focusNode's keys to virtualNode
						std::copy(std::begin(focusNode->keys), std::end(focusNode->keys), std::begin(virtualNode));

						//add the overflown key
						virtualNode[focusNode->num_keys] = key;

						//sort virtualNode
						std::sort(virtualNode, (virtualNode + focusNode->num_keys + 1));

						//display the contents of the virtual node
						std::cout << "Node with overflown elements are:" << std::endl;
						for (auto e : virtualNode)
							std::cout << e << ' ';
						std::cout << std::endl;


						//pick the middle key
						int mid = ceil(float(focusNode->num_keys + 1) / 2);
						std::cout << "middle element is: ";
						std::cout << virtualNode[mid - 1] << std::endl;

						//Make a new node with the middle key as the first key. This is how it is being pushed up for the root.
						Node* x = new Node(virtualNode[mid - 1]);

						//make 2 new nodes to put all the keys that are left of the middle key into splitLeft node. Put all the keys right of the middle key into splitRight node.
						Node* splitLeft = new Node(virtualNode[0]);
						Node* splitRight = new Node(virtualNode[mid]);

						//set the first child of x to splitLeft node. set the 2nd child of x to splitRight node (this probably needs tweaking to work seamlessly with 3 children)
						x->children[0] = splitLeft;
						x->children[1] = splitRight;

						//set the new root as x
						root = x;


						return;
					}




				}

			}

		}
	}
}


void BTree::inOrderTraversal(Node* focusNode) {

	if (focusNode != NULL) {

		inOrderTraversal(focusNode->children[0]);   //keep traversing the left node to the left child till it hits null

		for (int i = 0; i < focusNode->n; i++)
			std::cout << focusNode->keys[i] << "->";   //visit the currently focused on node because we know that will be the next value of the lowest value

		inOrderTraversal(focusNode->children[1]); //traverse right child. INORDER fulfilled 
	}

}

int main() {

	BTree theTree;

	theTree.AddKey(2);
	theTree.AddKey(1);
	theTree.AddKey(0);
	//theTree.AddNode(3);
	//theTree.AddNode(6);
	//theTree.AddNode(5);
	//theTree->AddNode(85);

	std::cout << "B-Tree Traversal: ";
	theTree.inOrderTraversal(theTree.root);

	std::cin.get();
}