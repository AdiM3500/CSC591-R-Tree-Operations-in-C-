#include "a1/btree/BTree.hpp"

#include <iostream>
#include <algorithm>
#include<iterator>
#include <cmath>
#include <bits/stdc++.h>


//if node has no children, then node is a leaf
bool Node::check_leaf() {

	if (children[0] == NULL && children[1] == NULL && children[2] == NULL)
		return true;

	else return false;
}


bool BTree::operator == ( BTree  other ) const {

//if current object's root is empty, return true if other's root is empty as well
	if(root == NULL){

		if(other.root == NULL) return true;

		
	} 

	else {

		bool res = other.inOrderComparisonTraversal(other.root,root);   //returns true if every key in 'other' is present in current object

		return res;
	}

	return false;
}

void BTree::insertInNonFullNode(Node* focusNode, int key){

					int	index = focusNode->n;
					focusNode->keys[index] = key;
					focusNode->n += 1;  //increase number of keys counter after adding the new key
					std::sort(focusNode->keys, focusNode->keys + focusNode->n);   //sort the keys inside the node

}


//THIS DOES NOT WORK. VirtualNode[] doesn't work with std::sort when passed as an argument to a function
/*
int BTree::findMid(Node* focusNode, int virtualNode[], int key){

						int virtualNode[focusNode->num_keys];
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


						return mid;

}
*/


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

					
				insertInNonFullNode(focusNode, key);
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

						//---------------------------------------------------------------------------------------------------------------------------------
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

						//set focusNode as root
						focusNode = root;


						return;
					}






				}

			}
			
					//if node is not is not a leaf
			else {
								//loop ensures that we traverse through all keys in the node to find the appropriate location to go down to
								for(int i = 0; i < focusNode->n; i++){
									
									if (key < focusNode->keys[i]){							//if the key is less than the current key's value, then take the route to it's left Child (which has the same index as the current key)

										focusNode = focusNode->children[i];						

										if(focusNode->check_leaf()){

										std::cout <<"the key we are trying to insert: " <<key <<std::endl;
										std::cout <<"we are at leaf with starting key: " <<focusNode->keys[0]<<std::endl;

										if(focusNode->n < focusNode->num_keys)
										insertInNonFullNode(focusNode,key);

										else {
											std::cout <<"node full!";
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

								//--------------------------------------------------------------------------------------------------------------------	
										//splitleft
										
										if(parent->n < parent->num_keys) insertInNonFullNode(parent, virtualNode[mid-1]); //propogate the key up to the non-full parent
										
										//for displaying purposes
										 for (int j = 0; j <parent->n; j++){
											 std::cout <<parent->keys[j]<<std::endl;
										 }
										
										//we need to split the children and place them in their appropriate places with respect to the parent.
											Node* temp = parent->children[1];

										
										//place the 1st element in virtual node as the left child, the 3rd (last) element of the virtual node as the middle child and the previous middle child as right child.
											parent->children[0] = new Node(virtualNode[0]);
											parent->children[1] = new Node(virtualNode[mid]);
											parent->children[2] = temp;							//the previous middle element will always be the last element because it was already known that it is greater than the current parent's key.
											
											focusNode = parent;

											//for displaying purposes
											std::cout <<"parent children[2] key size: "<<parent->children[2]->n<<std::endl;
											std::cout <<"parent children[2] has key: "<<parent->children[2]->keys[0]<<std:: endl;
											std::cout <<"parent children[2] has key: "<<parent->children[2]->keys[1]<<std::endl;
											
										}

										return;
									}
								}
										//if we are at the last key in focusNode and the key we need to add is greater than this last key
									if ((i == (focusNode->n -1)) && (key > focusNode->keys[i])) {
										
										
										focusNode = focusNode->children[i+1];  //take the route to the rightChild this time 

										if(focusNode->check_leaf()){

										std::cout <<"[bigger] the key we are trying to insert: " <<key<<std::endl;
										std::cout <<"[bigger] we are at leaf with starting key: " <<focusNode->keys[0]<<std::endl;

										if(focusNode->n < focusNode->num_keys)
										{insertInNonFullNode(focusNode,key);

										//for displaying purposes only
										std::cout <<"parent children[2] key size: "<<parent->children[2]->n<<std::endl;
										std::cout <<"parent children[2] has key: "<<parent->children[2]->keys[0]<<std:: endl;
										std::cout <<"parent children[2] has key: "<<parent->children[2]->keys[1]<<std::endl;

										}

											


										else {
											std::cout <<"node full!";
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

								//--------------------------------------------------------------------------------------------------------------------	
										//splitRight
										
										if(parent->n < parent->num_keys) insertInNonFullNode(parent, virtualNode[mid-1]);
										
										//for displaying purposes only
										 for (int j = 0; j <parent->n; j++){
											 std::cout <<parent->keys[j]<<std::endl;
										 }
										
											Node* temp = parent->children[1];

											//make the 1st element of virtualnode as middle child and last element of virtualNode as right child.
											parent->children[1] = new Node(virtualNode[0]);
											parent->children[2] = new Node(virtualNode[mid]);
											
											
											focusNode = parent;

											
											std::cout <<"parent children[1] key size: "<<parent->children[1]->n<<std::endl;
											std::cout <<"parent children[1] has key: "<<parent->children[1]->keys[0]<<std:: endl;
										}

										return;
									}
										
									}
									
								}
									
							

							return;
						
			}

		}
	}
}


//InorderTraversal has been modified to accomodate 3 children now. Have taken inspiration for just this code from: https://www.geeksforgeeks.org/insert-operation-in-b-tree/
void BTree::inOrderTraversal(Node* focusNode) {

	if (focusNode != NULL) {
		
		int i;
		for ( i = 0; i < focusNode->n; i++) {
				inOrderTraversal(focusNode->children[i]);
			    std::cout << focusNode->keys[i] << "->";   //visit the currently focused on node because we know that will be the next value of the lowest value


		}
	

		inOrderTraversal(focusNode->children[i]);
	}

} 

/*
void BTree::inOrderTraversal(Node* focusNode){
			int i;
	for (i = 0; i < focusNode->n; i++){

		if (focusNode->check_leaf() == false)
				inOrderTraversal(focusNode->children[i]);
				std::cout << " "<<focusNode->keys[i];
					
	}

	if (focusNode->check_leaf() == false){
				
				inOrderTraversal(focusNode->children[i]);
	}
}
*/

//similar to inOrderTraversal but we compare each element of 2 b trees
bool BTree::inOrderComparisonTraversal(Node* focusNode1, Node* focusNode2) {

	if(focusNode1 != NULL){

		inOrderComparisonTraversal(focusNode1->children[0], focusNode2->children[0]);

		for (int i = 0; i < focusNode1->n; i++){

			if(focusNode1->keys[i] != focusNode2->keys[i])
			return false;
		}

	   inOrderComparisonTraversal(focusNode1->children[1], focusNode2->children[1]);

	}

	return true;
}
