#include "a1/btree/BTree.hpp"

#include <iostream>  // std::cout

int main() {

	BTree theTree;

	theTree.AddKey(7);
	theTree.AddKey(5);
	theTree.AddKey(9);
	theTree.AddKey(3);
	theTree.AddKey(1);
	theTree.AddKey(11);
	// theTree.AddKey(13);
	

	std::cout << "B-Tree Traversal: ";
	theTree.inOrderTraversal(theTree.root);

	std::cin.get();
}
