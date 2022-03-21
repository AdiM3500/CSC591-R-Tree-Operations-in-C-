#include <iostream>
#include <algorithm>
#include<iterator>
#include <cmath>
#include <optional>
#include <utility>
#include <vector>
#include <array>


using coordinate_t = std::pair< int, int >;
using pair_of_coordinates_t = std::pair < coordinate_t, coordinate_t >;
using datapoint_list_t = std::vector < coordinate_t >;			


class DataNode {

public:

	static const uint32_t data_cap = 3;
	std::array < coordinate_t, data_cap > dpoints;				//A list of datapoints (or a list of (x,y) coordinates)
	int array_size = 0;

	/*
		Add a new datapoint to the plane
	*/
	DataNode(int x1, int y1) {

		dpoints[array_size] = { x1,y1 };
		array_size += 1;

	}

	DataNode(datapoint_list_t datapoints_to_insert) {
																									//can't use a std::copy here to copy pairs from a vector of pairs to an array of pairs.
		for (auto i = 0; i < datapoints_to_insert.size(); i++) {

			dpoints[i] = datapoints_to_insert[i];
		}

		array_size = datapoints_to_insert.size();
	}

	int find_min_x();
	int find_min_y();
	int find_max_x();
	int find_max_y();

	friend class Node;
	friend class RTree;

};

class Node {


public:

	static const uint32_t node_cap = 3;  
	std::array<pair_of_coordinates_t, node_cap> mbr ;				//A list of MBRs

	Node* children[node_cap];										//children of MBRs
	DataNode* dataPtr[node_cap];									//an optional data member for leaf MBRs only. Points to an array of datapoints for a particular MBR 
	
	int n = 0;														//var to keep track of the number of rectangles


	/**
	 * Create a new node with a single MBR and no children. Argument is a pointer to a list of datapoints. Perhaps create another constructor that accepts MBRs as an argument?
	 */
	Node(DataNode *d) {

		//mbr[n] =  (find min x, find max x blah blah blah.......


		int min_x = d->find_min_x();
		int max_x = d->find_max_x();
	
		int min_y = d->find_min_y();
		int max_y = d->find_max_y();

		mbr[n] = { {min_x, min_y},{max_x, max_y} };       //pair of lower-left and upper-right coordinates to represent a minimum bounding rectangle


		
		children[0] = NULL;
		children[1] = NULL;
		children[2] = NULL;

		dataPtr[n] = d;
		n += 1;							
	}


	bool check_leaf();     //function to check if node is a leaf node. check to see if its the smallest MBR node??


	friend class RTree;
};



class RTree {

public:

	Node* root = NULL; //ROOT IS A POINTER TO A NODE OBJECT

	
	
	void AddDatapoint(coordinate_t d);

};
