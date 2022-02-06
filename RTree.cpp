#include <iostream>
#include <utility>
using namespace std;


/*The current program creates an empty R-Tree with a user-specified root node */


//Class rectangle holds the upper right and lower left coordinates of a rectangle
class Rectangle {

public:
	
	pair <int, int> upperCoordinates;
	pair<int, int> lowerCoordinates;

	friend class Node;
	friend class RTree;

   //Default constructor (*rectangles array from class Node below doesn't initialize otherwise. Will look into why)
	Rectangle() {

		lowerCoordinates.first = 0;
		lowerCoordinates.second = 0;
		upperCoordinates.first = 0;
		upperCoordinates.second = 0;
	}


	//Display the rectangle's coordinates
	void display_rect() {

		cout << "(" <<lowerCoordinates.first << ","
			<< lowerCoordinates.second << "),("
			<< upperCoordinates.first << ","
			<< upperCoordinates.second << ")\n";
		
	}
	
}; 

//Class Node. Objects of class Node will have rectangles and pointers corresponding to those rectangles. 
//Node capacity is specified by the user. A single node cannot have more rectangles than the limit specified.
//
class Node {

public:
	int maxPtrs, maxRectangles;
	Rectangle *rectangles;
	Rectangle **rectPtr;
	int n;  //number of current rectangles in the node 
	int node_cap;
	bool leaf;  

	//Constructor for a new node with specified capacity
	Node(int node_capacity) {
		node_cap = node_capacity;
		rectangles = new Rectangle[node_cap];     //this allocates node_cap amount of rectangles of the node
		rectPtr = new Rectangle*[node_cap];       //this allocates node_cap amount of pointers of the rectangles
		n = 0;									// a new node will have 0 rectangles

	}

	void AddRectangetoNode(int x1, int y1, int x2, int y2);			//add a rectangle to the node. 

	friend class RTree;
	
};

//need to add to this function/re-write once I start filling up the tree with rectangles and nodes.
void Node::AddRectangetoNode(int x1, int y1, int x2, int y2) {


	//if the number of rectangles in the node hasn't reached capacity yet, add a new rectangle to the node with the current index n
	if (n < node_cap) {

		rectangles[n].lowerCoordinates.first = x1;
		rectangles[n].lowerCoordinates.second = y1;
		rectangles[n].upperCoordinates.first = x2;
		rectangles[n].upperCoordinates.second = y2; 

		n += 1;

	}
	
}


//Class RTree currently had the root object and can add a root node to the RTree. Going to be updating this further to work with internal nodes,
//leaf nodes & node_splits
class RTree {

public:

		Node *root;
		void addRootNode(int node_cap, int x1, int y1, int x2, int y2);

		RTree() {

			root = NULL;
		}
	
};

//add a root node to a newly created RTree. This will succesfully create an empty R-Tree with a root node. 
//Will either write down more code to this function to make it work with both internal nodes, internal rectangles, leaf nodes, and leaf rectangles.
//or will create seperate functions for all of them.
void RTree::addRootNode(int node_cap, int x1, int y1, int x2, int y2) {


	//if the root node is empty, assign a new node to the root with the user-specified coordinates as it's first rectangle.
	if (root == NULL) {
		Node* newNode = new Node(node_cap);
		root = newNode;
		
		root->AddRectangetoNode(x1, y1, x2, y2);		 //add the rectangle to the root node
		cout <<"Number of nodes currently in the root : "<< root->n << endl;   //show the current number of nodes in the root
		cout << "Node capacity of the root : " << root->node_cap << endl;   //show the user-specified capacity of the root.
	}

	else {
		cout << "root node already present!";				//small else condition to show that you cannot add another root node to a tree that already has one. 
	}
}


int main() {


	int node_capacity;

	cout << "Enter a node capacity: ";
	cin >> node_capacity;

	//Create new R Tree object
	RTree* theTree = new RTree();

	//Add a root node to the empty R tree
	theTree->addRootNode(node_capacity, 2, 4, 5, 6);
	theTree->root->rectangles[0].display_rect();

	cout << "\n----------------------Trying to Add another root node-------------\n";

	theTree->addRootNode(node_capacity, 5, 6, 7, 8);
	cin.get();
}