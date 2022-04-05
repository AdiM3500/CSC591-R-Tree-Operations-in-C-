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



pair_of_coordinates_t Node::find_minmax_coordinates(variety_content_list_t data) {

	pair_of_coordinates_t minmax_coords;

	//if only one datapoint is given as the argument, return the same datapoint ad both the min and the max coordinate
	if (data.size() == 1) {

		minmax_coords = { {std::get<coordinate_t>(data[0]).first, std::get<coordinate_t>(data[0]).second },
							{ std::get<coordinate_t>(data[0]).first, std::get<coordinate_t>(data[0]).second  }  };

		return minmax_coords;
	}


	int min_index_x = 0;
	int min_index_y = 0;
	int max_index_x = 0;
	int max_index_y = 0;


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


	 minmax_coords = { { std::get<coordinate_t>(data[min_index_x]).first, std::get<coordinate_t>(data[min_index_y]).second }
											, { std::get<coordinate_t>(data[max_index_x]).first, std::get<coordinate_t>(data[max_index_y]).second} };

	return minmax_coords;
}

//	pair_of_coordinates_t minmax_coords = { { std::get<coordinate_t>(data[min_index_x]).first, std::get<coordinate_t>(data[min_index_y]).second }
	//										, { std::get<coordinate_t>(data[max_index_x]).first, std::get<coordinate_t>(data[max_index_y]).second} };

	//return minmax_coords;




pair_of_coordinates_t Node::mbr_generator(variety_content_list_t list) {

	pair_of_coordinates_t mbr;
	//make sure its type-safe
	
	if (list[0].index() == 0)
	{
		mbr = find_minmax_coordinates(list);
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

	//Node* focusNode = root;
	//datapoint_list_t listOfDataPoints{};		//vector of datapoints that are contained within the search rectangle; to be returned by the find function


	rangeTraversal(root, search_rectangle);

	return listOfDataPoints;

	
		

} 

void RTree::rangeTraversal(Node* focusNode, pair_of_coordinates_t search_rectangle) {


	int i = 0;

	if (focusNode!= NULL) {

		int i;
		for (i = 0; i < focusNode->n; i++) {

			//if the focusNode is a leaf node, check to see which datapoints does the MBR overlap
			if (focusNode->contents[i].index() == 0)
			{
				if ((std::get<coordinate_t>(focusNode->contents[i]).first >= search_rectangle.first.first)
					&& (std::get<coordinate_t>(focusNode->contents[i]).second >= search_rectangle.first.second)
					&& (std::get<coordinate_t>(focusNode->contents[i]).first <= search_rectangle.second.first)
					&& (std::get<coordinate_t>(focusNode->contents[i]).second <= search_rectangle.second.second)
					) {

					//(remove comment below to display exactly which datanodes are being returned)
				//	std::cout << "(" << std::get<coordinate_t>(focusNode->contents[i]).first << ", " << std::get<coordinate_t>(focusNode->contents[i]).second << ") -> ";
					listOfDataPoints.push_back(std::get<coordinate_t>(focusNode->contents[i]));

				}

			}


			// if the focusnode is an MBR node
			if (focusNode->contents[i].index() == 1) {

				// condition to check if the search rectangle is overlapping the current MBR
				if ((search_rectangle.first.first <= std::get<pair_of_coordinates_t>(focusNode->contents[i]).second.first)
					&& (std::get<pair_of_coordinates_t>(focusNode->contents[i]).first.first <= search_rectangle.second.first)
					&& (search_rectangle.first.second <= std::get<pair_of_coordinates_t>(focusNode->contents[i]).second.second)
					&& (std::get<pair_of_coordinates_t>(focusNode->contents[i]).first.second <= search_rectangle.second.second)
					) {

					// (remove comment below to display exactly which MBR nodes we are entering. Can be used to confirm that we are only traversing those nodes that actually overlap the search rectangle)
				/*	std::cout << "[(" << std::get<pair_of_coordinates_t>(focusNode->contents[i]).first.first << ", " <<
						std::get<pair_of_coordinates_t>(focusNode->contents[i]).first.second << "), (" <<
						std::get<pair_of_coordinates_t>(focusNode->contents[i]).second.first << "," <<
						std::get<pair_of_coordinates_t>(focusNode->contents[i]).second.second << ")] -> "; */

					//selectively dfs recurse through the tree
					rangeTraversal(focusNode->children[i], search_rectangle);

					
				}


			}
			//	std::cout << "[(" << std::get<pair_of_coordinates_t>(focusNode->contents[i]).first.first << ", " <<
				//std::get<pair_of_coordinates_t>(focusNode->contents[i]).first.second << "), (" <<
				//std::get<pair_of_coordinates_t>(focusNode->contents[i]).second.first << "," <<
				//std::get<pair_of_coordinates_t>(focusNode->contents[i]).second.second << ")] -> ";
		}



	}
	

	//std::cout << "\n\n";
		
	
		
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


//insertion function
void RTree::AddDatapoint(coordinate_t d) {

	Node* newNode = new Node{ variety_content_list_t{d} };

	//if root is null, create a brand new mbr node with mbr in the root that indexes the datapoint given
	if (root == NULL) {

		//create an MBR to accomodate for the incoming datanode
		
		root = new Node{ variety_content_list_t{ pair_of_coordinates_t{ root->mbr_generator(variety_content_list_t{d}) }   } };			//this creates a degenrate mbr where the min and max coordinates are the same, since we are inserting just one datapoint to an empty tree.


		root->children[0] = new Node{ variety_content_list_t{d} };

		
	}


	else {

		Node* focusNode = root;
		Node* parent;

		while (true) {

			parent = focusNode;

			for (int i = 0; i < focusNode->n; i++) {

				if (isContained(d, std::get<pair_of_coordinates_t>(focusNode->contents[i]))) {

					//check if we're at a leaf, else go down to the respective child
					//if we're at a leaf, check if there's space
					//if there's space, put the datapoint in the datanode
					
					return;
				}

				//if the datapoint to be inserted is outside of all of the indexable area of the r-tree
				if (i == (focusNode->n - 1)) {

					//pick the rectangle that shall invoke the least amount of increase of its area to accomodate the datapoint
					//put the point inside the datanode of this rectangle

					return;
				}
			}
		}
	}
}
