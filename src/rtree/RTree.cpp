#include "a2/rtree/RTree.hpp"

#include <iostream>
#include <algorithm>
#include<iterator>
#include <cmath>


int DataNode::find_min_x() {

	int min_index = 0;
	for (int i = 0; i < array_size; i++) {

		if (dpoints[min_index].first > dpoints[i].first) {
				min_index = i;
		}
	}

	return dpoints[min_index].first;
	
}


int DataNode::find_max_x() {

	int max_index = 0;
	for (int i = 0; i < array_size; i++) {

		if (dpoints[max_index].first < dpoints[i].first) {
			max_index = i;
		}
	}

	return dpoints[max_index].first;
}


int DataNode::find_min_y() {

	int min_index = 0;
	for (int i = 0; i < array_size; i++) {

		if (dpoints[min_index].second > dpoints[i].second) {
			min_index = i;
		}
	}

	return dpoints[min_index].second;
}

int DataNode::find_max_y() {

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