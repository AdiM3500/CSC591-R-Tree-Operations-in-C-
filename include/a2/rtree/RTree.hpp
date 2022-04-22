#include <iostream>
#include <algorithm>
#include<iterator>
#include <cmath>
#include <optional>
#include <utility>
#include <vector>
#include <array>
#include <variant>
#include <queue>
#include <tuple>


using coordinate_t = std::pair< int, int >;
using pair_of_coordinates_t = std::pair < coordinate_t, coordinate_t >;
using variety_content = std::array < std::variant <coordinate_t, pair_of_coordinates_t>, 3 >;              //an array of either only coordinates or only a pair of coordinates
using variety_content_list_t = std::vector < std::variant <coordinate_t, pair_of_coordinates_t> >;	//a list of either datapoints or pair of coordinates (Datapoints list or MBR list)

using datapoint_list_t = std::vector<coordinate_t>;



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

	}

	bool check_leaf() const;     //function to check if node is a leaf node. A leaf node is an MBR node that points to a datanode

	pair_of_coordinates_t find_minmax_coordinates(variety_content_list_t data);  //find the minimum and maximum coordinates from the list of datapoints 

	pair_of_coordinates_t mbr_generator (variety_content_list_t list); 	//This function will take a datapoint list and return a MBR corresponding to its minimum and maximum coordinates.

	int findArea(pair_of_coordinates_t rect_coords);      //Used to find the area of a rectangle, given its minmax coordinates

	int updateMBRNode(Node* focusNode, coordinate_t datapoint); //returns an index of the MBR that has the most minimum amount of increase in its area to accomodate an unindexed datapoint

	friend class RTree;
};



class RTree {

public:

	Node* root = NULL; //ROOT IS A POINTER TO A NODE OBJECT

	bool equality_confirmed = true;									//used to check if two r-tree objects are equal or not. used in the comparisonTraversal function.

	datapoint_list_t listOfDataPoints{};							//set as empty initially. Used to contain datapoints that overlap a search-rectangle. Primarily used in the find function (for range search) and in the rangeTraversal function.
	


	//comperator for the priority queue
	template <typename T>
	struct new_min_dist {


		bool operator() (T a, T b) const {

			return std::get<2>(a) > std::get<2>(b);
		}
	};






	//1st element in the tuple is either an mbr or a datapoint, 2nd element is the node that the first element is present in, and 3rd element is the distance of the 1st element from the querypoint
	std::priority_queue< std::tuple < std::variant<coordinate_t, pair_of_coordinates_t>, Node*, double >, std::vector < std::tuple < std::variant<coordinate_t, pair_of_coordinates_t>, Node*, double > >, new_min_dist < std::tuple < std::variant<coordinate_t, pair_of_coordinates_t>, Node*, double > >   > new_knn;

   

	/**
	 * Returns a list of all datapoints that overlap a search rectangle
	 */
	datapoint_list_t find(pair_of_coordinates_t search_rectangle);


	//inserts a datapoint into the r-tree
	void AddDatapoint(coordinate_t d, Node* focusNode);

	//Used for the lookup query in the r-tree
	std::optional< Node* > find(coordinate_t datapoint);

	//returns true if a datapoint could be theoretically contained inside a rectangle
	bool isContained(coordinate_t d, pair_of_coordinates_t mbrs);

	//produces a depth-first traversal of the whole r-tree
	void depthFirstTraversal(Node* focusNode);

	//uses depth-first traversal of two r-tree objects simultaneously to check whether each and every node's contents of one object are exactly the same as the other.
	bool comparisonTraversal(Node* focusNode1, Node* focusNode2);

	//uses conditional statements to check whether mbr(s) overlap a given search rectangle. Then selectively recurses through the tree to locate the nodes which contain the datapoints that overlap the search rectangle.
	void rangeTraversal(Node* focusNode, pair_of_coordinates_t search_rectangle);

	bool operator == (RTree other) const;

	double calc_distance(coordinate_t querypoint, pair_of_coordinates_t rectangle); //calculate the distance between a querypoint and a rectangle 

	double calc_distance(coordinate_t querypoint, coordinate_t datapoint);		//calculate the distance between a querypoint and a datapoint

	std::vector<coordinate_t> IncNearest(coordinate_t querypoint, RTree tree, int k);  //function that returns the k nearest neighbors of a querypoint in the r-tree

	void push_elements_to_queue(Node* focusNode, coordinate_t querypoint );		//function to push the contents of a focusNode(whether it be an MBR or a querypoint), the distances of the contents to the querypoint, etc. into the priority queue.

};
