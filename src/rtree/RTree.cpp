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

		std::cout << "we are at root's leaf" << std::endl;


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

					std::cout << "we are at a leaf" << std::endl;


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



void RTree::inOrderTraversal(Node* focusNode) {


	if (focusNode != NULL) {

		int i;
		for (i = 0; i < focusNode->n; i++) {
			inOrderTraversal(focusNode->children[i]);
	//	std::cout << focusNode->keys[i] << "->";   //visit the currently focused on node because we know that will be the next value of the lowest value
			if(focusNode->contents[i].index()==0)
			std::cout << "(" << std::get<coordinate_t>(focusNode->contents[i]).first << ", " << std::get<coordinate_t>(focusNode->contents[i]).second << ") -> ";


			if (focusNode->contents[i].index() == 1)
				std::cout << "[(" << std::get<pair_of_coordinates_t>(focusNode->contents[i]).first.first << ", " <<
				std::get<pair_of_coordinates_t>(focusNode->contents[i]).first.second << "), (" <<
				std::get<pair_of_coordinates_t>(focusNode->contents[i]).second.first << "," <<
				std::get<pair_of_coordinates_t>(focusNode->contents[i]).second.second <<")] -> ";
		}


	}

//	inOrderTraversal(focusNode->children[i]);

}
