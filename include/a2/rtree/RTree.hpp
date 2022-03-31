#include <iostream>
#include <algorithm>
#include<iterator>
#include <cmath>
#include <optional>
#include <utility>
#include <vector>
#include <array>
#include <variant>


using coordinate_t = std::pair< int, int >;
using pair_of_coordinates_t = std::pair < coordinate_t, coordinate_t >;
using variety_content = std::array < std::variant <coordinate_t, pair_of_coordinates_t>, 3 >;              //an array of either only coordinates or only a pair of coordinates
using variety_content_list_t = std::vector < std::variant <coordinate_t, pair_of_coordinates_t> >;			//a list of either datapoints or pair of coordinates (Datapoints list or MBR list)



class Node {


public:

	static const uint32_t node_cap = 3;  

	variety_content contents;						//A node's content can be either an array of mbrs or an array of datapoints

	Node* children[node_cap] = { NULL };					
	int n = 0;										//size of the node
	

	Node(variety_content_list_t data_to_insert) {

		for (auto i = 0; i < data_to_insert.size(); i++) {

			contents[i] = data_to_insert[i];
		}

		n = data_to_insert.size();


		std::cout << "size: " << n << std::endl;
	}


	/* 
	* 
	* WRTIE 1 MORE CONSTRUCTOR: This constructor will take a list of datapoints or a list of MBRs (of the type variety_content)

	 */


	bool check_leaf() const;     //function to check if node is a leaf node. A leaf node is an MBR node that points to a datanode

	pair_of_coordinates_t find_minmax_coordinates(variety_content data);  //find the minimum and maximum coordinates from the list of datapoints 

	pair_of_coordinates_t mbr_generator (Node* datapoint_list); 	//(HASN'T BEEN USED YET) This function will take a datapoint list and return a MBR corresponding to it.

	

	friend class RTree;
};



class RTree {

public:

	Node* root = NULL; //ROOT IS A POINTER TO A NODE OBJECT

	
	//NOT WRITTEN: Will be used for inserting a datapoint into the Tree
	void AddDatapoint(coordinate_t d);

	//PARTIALLY WRITTEN: Will be used for finding a datapoint in the RTree
	std::optional< Node* > find(coordinate_t datapoint);

	//NOT WRITTEN: Will be used for finding a range of elements in the Rtree
	pair_of_coordinates_t find(coordinate_t lower_bound, coordinate_t upperbound);

	//returns true if a datapoint could be theoretically contained inside a rectangle
	bool isContained(coordinate_t d, pair_of_coordinates_t mbrs);

	//produces an in-order traversal of the whole r-tree
	void inOrderTraversal(Node* focusNode);

};
