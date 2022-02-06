#include <iostream>
using namespace std;

class Node {

public:
	int _key;
	Node* leftChild;
	Node* rightChild;

	Node(int key) {
		_key = key;
		leftChild = NULL;
		rightChild = NULL;
	}

	friend class BTree;
};



class BTree {

public:

	Node* root; //ROOT IS A POINTER TO A NODE OBJECT
	BTree() {
		root = NULL;
	}
	void AddNode(int key);
	void inOrderTraversal(Node* focusNode);
};



void BTree :: AddNode(int key) {

	Node* newNode = new Node(key);

	if (root == NULL) {

		root = newNode;
	}

	else {
		Node* focusNode = root;
		Node* parent;

		while (true) {
			
			parent = focusNode;
			if (key < focusNode->_key) {

				focusNode = focusNode->leftChild;

				if (focusNode == NULL) {
					parent->leftChild = newNode;
					return;
				}

			}
			else {
					focusNode = focusNode->rightChild;

					if (focusNode == NULL) {
						parent->rightChild = newNode;
						return;
					}
				}
			}
		}
	}


void BTree::inOrderTraversal(Node* focusNode) {

	if (focusNode != NULL) {
		inOrderTraversal(focusNode->leftChild);   //keep traversing the left node to the left child till it hits null

		cout <<focusNode->_key<<"->";   //visit the currently focused on node because we know that will be the next value of the lowest value

		inOrderTraversal(focusNode->rightChild); //traverse right child. INORDER fulfilled 
	}
	
}

int main() {

	BTree* theTree = new BTree();

	theTree->AddNode(1);
    theTree->AddNode(2);
	theTree->AddNode(3);
	theTree->AddNode(6);
	theTree->AddNode(5);
	//theTree->AddNode(85);
	theTree->inOrderTraversal(theTree->root);

	delete theTree;
	
	cin.get();
}
