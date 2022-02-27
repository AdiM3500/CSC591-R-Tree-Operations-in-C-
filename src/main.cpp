#include "a1/btree/BTree.hpp"

#include <iostream>  // std::cout

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
