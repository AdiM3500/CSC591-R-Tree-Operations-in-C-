#include "a2/rtree/RTree.hpp"

#include <iostream>
#include <algorithm>
#include<iterator>
#include <cmath>


std::optional<Node*> RTree::find(coordinate_t datapoint) {


	if (root == NULL)
		return std::nullopt;

	Node* focusNode = root;


	/* 
	* if tree contains only one node(one MBR node that points to a datanode)
	*/

	std::cout << "focusnode size: " << focusNode->n <<std::endl;

	if (focusNode->check_leaf()) {

		std::cout << "we are at a leaf"<<std::endl ;

		//displaying purposes
		//------------------------------------------------------------------------------------- 
		
	//	std::cout << "its a leaf node with coords: " << std::get<pair_of_coordinates_t>(focusNode->contents[0]).first.first<<std::endl;
		//std::cout <<"its a leaf node with coords: " << std::get<pair_of_coordinates_t>(focusNode->contents[0]).first.second << std::endl;

	//	std::cout << "leaf node's child contains: " << std::get<coordinate_t>(focusNode->children[0]->contents[0]).first << std::endl;
	//	std::cout << "leaf node's child contains: " << std::get<coordinate_t>(focusNode->children[0]->contents[1]).first << std::endl;

		//------------------------------------------------------------------------------------
		
		for (auto i = 0; i < focusNode->n; i++) {

			for (auto j = 0; j < focusNode->children[i]->n; j++) {


				std::cout << "comparing datapoint: " << datapoint.first << ", " << datapoint.second << " to : " 
					<< std::get<coordinate_t>(focusNode->children[i]->contents[j]).first << ", " << std::get<coordinate_t>(focusNode->children[i]->contents[j]).second<<std::endl;


				if (datapoint == std::get<coordinate_t>(focusNode->children[i]->contents[j]))
				{	
					std::cout << "FOUND" << std::endl;
					return focusNode;   //returns the root node
				}

			}
			


	}
		
	}

	 return std::nullopt;
}


//If an MBR node's children is pointing to a datanode, then that node is a leaf node.
bool Node::check_leaf() {

	if ((children[0]->contents[0].index() == 0) || (children[1]->contents[0].index() == 0) || (children[2]->contents[0].index() == NULL) )
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




/*
int Node::find_max_x() {

	int max_index = 0;
	for (int i = 0; i < array_size; i++) {

		if (dpoints[max_index].first < dpoints[i].first) {
			max_index = i;
		}
	}

	return dpoints[max_index].first;
}


int Node::find_min_y() {

	int min_index = 0;
	for (int i = 0; i < array_size; i++) {

		if (dpoints[min_index].second > dpoints[i].second) {
			min_index = i;
		}
	}

	return dpoints[min_index].second;
}

int Node::find_max_y() {

	int max_index = 0;
	for (int i = 0; i < array_size; i++) {

		if (dpoints[max_index].second < dpoints[i].second) {
			max_index = i;
		}
	}

	return dpoints[max_index].second;
}


bool Node::check_leaf() {

	if (children[0] == NULL && children[1] == NULL && children[2] == NULL)
		return true;

	else return false;
}

 */



