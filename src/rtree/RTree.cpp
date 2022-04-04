#include "a2/rtree/RTree.hpp"

#include <iostream>
#include <algorithm>
#include<iterator>
#include <cmath>


std::optional<Node*> RTree::find(coordinate_t datapoint) {

	Node* exists = NULL;

	if (root == NULL)
		return std::nullopt;

	Node* focusNode = root;
	/*
	* if tree contains only one node i.e. the root is just a data node
	*/


	
	if (focusNode->check_leaf()) {

		


		for (const auto& x : focusNode->contents) {

			if (datapoint == std::get<coordinate_t>(x))
				return focusNode;
		}

	}



	else while (true) {


			for (int i = 0; i < focusNode->n; i++) {

				if (isContained(datapoint, std::get<pair_of_coordinates_t>(focusNode->contents[i]))) {

					exists = focusNode;
					focusNode = focusNode->children[i];

					i = int(-1);

				}

				//if the iscontained check fails throughout the root node, we know the datapoint is not present in the r-tree

				if(i == (focusNode->n - 1)){
					if (exists == NULL) return std::nullopt;
				}
			

				//we are at a datanode
				if (focusNode->check_leaf()) {


					for (const auto& x : focusNode->contents) {

						if (datapoint == std::get<coordinate_t>(x))
							return focusNode;
					}

					if (exists != NULL) return exists;
				}
			}
		
			//if the datapoint is not even indexed by the area covered by the R-tree then return null opt;
			return std::nullopt;
	}

}


//If the current node's contents are datapoints, then it is a leaf node
bool Node::check_leaf() const {

	if ((contents[0].index() == 0) )
		return true;

	else return false;
}


pair_of_coordinates_t Node::find_minmax_coordinates(variety_content data) {

	int min_index_x = 0;
	int min_index_y = 0;
	int max_index_x = 0;
	int max_index_y = 0;

	//coordinate_t dpoints = std::get<coordinate_t>(data[0]);

	for (int i = 0; i < data.size(); i++) {

		if (std::get<coordinate_t>(data[min_index_x]).first > std::get<coordinate_t>(data[i]).first) {

			min_index_x = i;

		}

		if (std::get<coordinate_t>(data[min_index_y]).second > std::get<coordinate_t>(data[i]).second) {

			min_index_y = i;

		}

		if (std::get<coordinate_t>(data[max_index_x]).first < std::get<coordinate_t>(data[i]).first) {

			max_index_x = i;

		}


		if (std::get<coordinate_t>(data[max_index_y]).second < std::get<coordinate_t>(data[i]).second) {

			max_index_y = i;

		}

	}


	pair_of_coordinates_t minmax_coords = { { std::get<coordinate_t>(data[min_index_x]).first, std::get<coordinate_t>(data[min_index_y]).second }
											, { std::get<coordinate_t>(data[max_index_x]).first, std::get<coordinate_t>(data[max_index_y]).second} };

	return minmax_coords;
}



pair_of_coordinates_t Node::mbr_generator(Node* datanode) {

	pair_of_coordinates_t mbr;
	//make sure its type-safe
	
	if (datanode->contents[0].index() == 0)
	{
		mbr = datanode->find_minmax_coordinates(datanode->contents);
	}

	return mbr;
}


bool RTree::isContained(coordinate_t d, pair_of_coordinates_t mbrs) {

				//mbrs.first contain the lower-left coordinates (xmin, ymin) while mbrs.second contain the upper-right coordinates (xmax, ymax)
	if ( (d.first >= mbrs.first.first) && (d.second >= mbrs.first.second) && (d.first <= mbrs.second.first)  && (d.second <= mbrs.second.second) ) {

		return true;
	}

	else return false;
}



void RTree::depthFirstTraversal(Node* focusNode) {


	if (focusNode != NULL) {

		int i;
		for (i = 0; i < focusNode->n; i++) {
			depthFirstTraversal(focusNode->children[i]);
	//	std::cout << focusNode->keys[i] << "->";   //visit the currently focused on node because we know that will be the next value of the lowest value
			if (focusNode->contents[i].index() == 0)
			{
				
				std::cout << "(" << std::get<coordinate_t>(focusNode->contents[i]).first << ", " << std::get<coordinate_t>(focusNode->contents[i]).second << ") -> ";

			}
			


			if (focusNode->contents[i].index() == 1)
				std::cout << "[(" << std::get<pair_of_coordinates_t>(focusNode->contents[i]).first.first << ", " <<
				std::get<pair_of_coordinates_t>(focusNode->contents[i]).first.second << "), (" <<
				std::get<pair_of_coordinates_t>(focusNode->contents[i]).second.first << "," <<
		    	std::get<pair_of_coordinates_t>(focusNode->contents[i]).second.second <<")] -> ";
		}


	}


}


datapoint_list_t RTree:: find(pair_of_coordinates_t search_rectangle) {

	Node* focusNode = root;

	
	Node* parent;								//parent variable to keep track of the focusnode's parent
	datapoint_list_t listOfDataPoints{};		//vector of datapoints that are contained within the search rectangle; to be returned by the find function


	Node* exists = NULL;

	//a counter to keep track of which MBRs we have read/or are currently reading in the root
	int root_counter = 0; 

	//a counter to keep track of the focusnode's parent MBRs that we have read or are currently reading. Specifically beneficial when we are at a leaf datanode and want to read the next MBR node in its parent.
	int parent_counter = 0;

	for (int i = 0; i < focusNode->n; i++) {


		parent = focusNode;
		
		//always retain the parent's last known index of the MBR being read before going into the child
		if (focusNode == parent) parent_counter = i;

		//if the focusNode is the root retain the last known index of the MBR in the root that overlaps the search rectangle
		if (focusNode == root) root_counter = i;

		//if node is an MBR node
		if (focusNode->contents[i].index() == 1) {


			//condition to see if the search rectaangle overlaps the current MBR:
			/*
			*	Comparing two rectangles: { (X1min, Y1min), (X1max, Y1max) }  and { (X2min, Y2min), (X2max, Y2max) }
			* 
				FOR COORDINATE X:
				(X2min <= X1max) AND (X1min <= X2max)

				FOR COORDINATE Y:
				(Y2min <= Y1max) AND (Y1min <= Y2max)
			*/
			if ((search_rectangle.first.first <= std::get<pair_of_coordinates_t>(focusNode->contents[i]).second.first)
				&& (std::get<pair_of_coordinates_t>(focusNode->contents[i]).first.first <= search_rectangle.second.first)
				&& (search_rectangle.first.second <= std::get<pair_of_coordinates_t>(focusNode->contents[i]).second.second)
				&& (std::get<pair_of_coordinates_t>(focusNode->contents[i]).first.second <= search_rectangle.second.second)
				) {

				//the search rectangle does overlap with at least one of the MBRs.
				exists = focusNode;

				focusNode = focusNode->children[i];

				//set i = -1 to reset the loop to start reading from the beginning of the child node
				i = int(-1);


				//if we are at a datanode, loop through the datapoints inside it to understand which ones are contained within the search rectangle
				if (focusNode->check_leaf()) {

					
					for (const auto& d : focusNode->contents) {


						//check which datapoints are within the search rectangle
						if ((std::get<coordinate_t>(d).first >= search_rectangle.first.first)
							&& (std::get<coordinate_t>(d).second >= search_rectangle.first.second)
							&& (std::get<coordinate_t>(d).first <= search_rectangle.second.first)
							&& (std::get<coordinate_t>(d).second <= search_rectangle.second.second)
							) {


							//if the search rectangle is degenerate:
							if (search_rectangle.first == search_rectangle.second) {

								listOfDataPoints.push_back(std::get<coordinate_t>(d));
								return listOfDataPoints;
							}


							//if the search rectangle is not degenerate:

							listOfDataPoints.push_back(std::get<coordinate_t>(d));


							//FOR DISPLAYING PURPOSES:
							std::cout << "datapoint inside the search rectangle: " << std::get<coordinate_t>(d).first << ", " << std::get<coordinate_t>(d).second << std::endl;

							
					
							
							
						}


					}

					//after finishing looping through the datanode, go back to its parent to see if there's another MBR that might overlap with the search rectangle
					focusNode = parent;

					
					//start from the last read MBR in the parent node
					i = parent_counter;

					//if we have read through all MBRs in the parent node, go back to the last read MBR in the root
					if (i == (focusNode->n - 1)) {		
						
						i = root_counter; 
						focusNode = root;
					}
					

				}

				

				
			}

			//if the search rectangle does not overlap any of the MBRs in the root node, then return the empty list of datapoints
			if (i == (focusNode->n - 1)) {

				if (exists == NULL) { 
					return listOfDataPoints; 
				}
			}
			
		}


	}
	return listOfDataPoints;

} 


bool RTree::operator == (RTree other) const {


	if (root == NULL){

		if (other.root == NULL) return true;

		if (other.root != NULL) return false;

	}

	if (other.root == NULL) {

		if (root != NULL) return false;

		if (root == NULL) return true;

	}


	else {

		bool res = other.comparisonTraversal(root, other.root);

		return res;
	}


	return false;
}


bool RTree::comparisonTraversal(Node* focusNode1, Node* focusNode2) {

	


	if (focusNode1 != NULL) {

		int i;

		if (focusNode2 == NULL) { equality_confirmed = false; return equality_confirmed; }

		for (i = 0; i < focusNode1->n; i++) {

			//std::cout << "fnode1 size : " << focusNode1->n << "fnode2 size: " << focusNode2->n << std::endl;

			if (focusNode1->n != focusNode2->n) { 
				
				equality_confirmed = false;
				break;
			
			}
			comparisonTraversal(focusNode1->children[i], focusNode2->children[i]);



			//std::cout << "\n focusnode1 size: " << focusNode1->n << "  and focusNode2 size: " << focusNode2->n<<std::endl;
			if (focusNode1->contents[i].index() == 0) {

				std::cout << "fnode1 size : " << focusNode1->n << " fnode2 size: " << focusNode2->n << std::endl;

				//if (focusNode1->n != focusNode2->n) return false;
				std::cout <<"\ncomparing datapoints of fnode1 " << "(" << std::get<coordinate_t>(focusNode1->contents[i]).first << ", " << std::get<coordinate_t>(focusNode1->contents[i]).second << ") ";
				std::cout <<"to datapoints of fnode2 " << "(" << std::get<coordinate_t>(focusNode2->contents[i]).first << ", " << std::get<coordinate_t>(focusNode2->contents[i]).second << ")\n ";


				if (std::get<coordinate_t>(focusNode1->contents[i]) != std::get<coordinate_t>(focusNode2->contents[i])) {
					equality_confirmed = false;
					
				

				}
					
			}

			if (focusNode1->contents[i].index() == 1) {


				//if (focusNode1->n != focusNode2->n) return false;
				if (std::get<pair_of_coordinates_t>(focusNode1->contents[i]) != std::get<pair_of_coordinates_t>(focusNode2->contents[i]))
				equality_confirmed = false;
				
			}
		}
	}

	

	


	 return equality_confirmed;
}

