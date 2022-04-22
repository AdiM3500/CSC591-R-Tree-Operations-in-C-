#include "a2/rtree/RTree.hpp"

#include <iostream>
#include <algorithm>
#include<iterator>
#include <cmath>
#include <climits>




std::optional<Node*> RTree::find(coordinate_t datapoint) {

	Node* exists = NULL;

	if (root == NULL)
		return std::nullopt;

	Node* focusNode = root;
	
	 //if tree contains only one node i.e. the root is just a data node
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

	//if only one datapoint is given as the argument, return the same datapoint as both the min and the max coordinate
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


//insertion function. 
void RTree::AddDatapoint(coordinate_t d, Node* focusNode) {

	//if root is null, create a brand new mbr node with mbr in the root that indexes the datapoint given
	if (root == NULL) {

		//create an MBR to accomodate for the incoming datanode
		
		root = new Node{ variety_content_list_t{ pair_of_coordinates_t{ root->mbr_generator(variety_content_list_t{d}) }   } };			//this creates a degenrate mbr where the min and max coordinates are the same, since we are inserting just one datapoint to an empty tree.


		root->children[0] = new Node{ variety_content_list_t{d} };

		return; //terminate the function
	}

	//if we are at an internal node
	if (focusNode->contents[0].index() == 1) {

		int i;
		for (i = 0; i < focusNode->n; i++) {

			//check which MBR could the datapoint be stored in
			if (isContained(d, std::get<pair_of_coordinates_t>(focusNode->contents[i]))) {

				//go into the MBR's child in which the datapoint could be stored and recursively call AddDataPoint again. This process will keep repeating till we eventually hit a leaf/data node.
				AddDatapoint(d, focusNode->children[i]);

				return;
				//Once we keep going down into the children which might contain the datapoint, we'll eventually hit a leaf node. We will insert the datapoint into the node if its non-full 
				//The program will return to this point again and since there's nothing left to do, we will terminate the recursion ( this case is true only if we inserted into a non-full datanode.)

			}
			
		}

		//we reach an MBR node where the datapoint cannot be contained/is not in the indexable area of any of the MBRs in the current focusnode

		//find which MBR can be enlarged to hold the datapoint which will add the least amount of area to the datapoint.
		
		int updated_index;

		//find the index of the mbr in the focusNode that needs to be updated to accomodate the datapoint we're trying to insert. this mbr shall require the least amount of area increase to accomodate the datapoint
		updated_index = focusNode->updateMBRNode(focusNode, d);

		//expand the correct mbr that needs to be expanded to accomodate the point
		focusNode->contents[updated_index] = focusNode->mbr_generator({ std::get<pair_of_coordinates_t>(focusNode->contents[updated_index]).first, std::get<pair_of_coordinates_t>(focusNode->contents[updated_index]).second, d });

		AddDatapoint(d, focusNode->children[updated_index]);				//recurse through the the new MBR's child now


	}


	//if we are at a leaf node
	if (focusNode->check_leaf()) {

		int i = 0;

		if (focusNode->n < focusNode->node_cap) {

			//insert the datapoint into the non-full datanode and increase the size of the data node by 1

			focusNode->contents[focusNode->n] = d;
			focusNode->n += 1;
		}

	}
	
	
}


//returns the area of the rectangle
int Node::findArea(pair_of_coordinates_t rect_coords) {

	int length = rect_coords.second.first - rect_coords.first.first;
	int breadth = rect_coords.second.second - rect_coords.first.second;

	int area = length * breadth;

	return area;
}

//find the index of the mbr in the mbrNode that needs to be updated for the datapoint d. This mbr will require the least amount of area increase to accomodate the datapoint d.
int Node:: updateMBRNode(Node* focusNode, coordinate_t d) {
	
	int smallest_difference = INT_MAX; int updated_index = 0;

	for (int i = 0; i < focusNode->n; i++) {

		int difference; int old_area; int new_area;

		//first find the original area of an mbr
		old_area = findArea(std::get<pair_of_coordinates_t>(focusNode->contents[i]));
		
		//std::cout << "\nold area: " << old_area << std::endl;

		//generate hypothetical MBR that is expanded to accomodate the unindexable datapoint
		pair_of_coordinates_t new_mbr = mbr_generator({ std::get<pair_of_coordinates_t>(focusNode->contents[i]).first, std::get<pair_of_coordinates_t>(focusNode->contents[i]).second, d });

		//find the area of this hypothetical mbr
		new_area = findArea(new_mbr);

		//std::cout << "new area: " << new_area << std::endl;

		//find the difference of areas between the old mbr and the new mbr
		difference = new_area - old_area;

		//if the difference is smaller than the previously documented *smallest difference*, then set the index of the mbr that needs to be updated to this mbr
		if (difference < smallest_difference) {

			smallest_difference = difference;
			updated_index = i;

			//std::cout << "correct update index" << std::endl;     //displaying purposes
		}


	}

	//std::cout << "\nindex to be updated: " << updated_index << std::endl;

	return updated_index;
}




/*   
   *Functions below are specifically related to the kNN query
*/


double RTree::calc_distance(coordinate_t querypoint, coordinate_t datapoint) {

	double distance;

	//euclidian distance between the querypoint and the datapoint
	distance = sqrt(pow(querypoint.first - datapoint.first, 2) + pow(querypoint.second - datapoint.second, 2)) ;

	return distance;

}


double RTree::calc_distance(coordinate_t querypoint, pair_of_coordinates_t rectangle) {

	//consider querypoint (x1,y1)

	//calculating distance in the x-dimension
	double dx, dy;

	/*
			// querypoint.x < rectangle.min.x
	if (querypoint.first < rectangle.first.first) {

		dx = rectangle.first.first - querypoint.first;  //minx - x1

	}

			// rectangle.min.x <= querypoint.x <= rectangle.max.x
	if (querypoint.first >= rectangle.first.first && querypoint.first <= rectangle.second.first) {

		dx = 0;
	}

			//querypoint.x > rectangle.max.x
	if (querypoint.first > rectangle.second.first) {

		dx = querypoint.first - rectangle.second.first;   //x1 - max_x
	}


	//calculating distance in the y-axis;


	if (querypoint.second < rectangle.first.second) {

		dy = rectangle.first.second - querypoint.second;  //miny - y1

	}

	// rectangle.min.y <= querypoint.y <= rectangle.max.y
	if (querypoint.second >= rectangle.first.second && querypoint.second <= rectangle.second.second) {

		dy = 0;
	}

	//querypoint.y > rectangle.max.y
	if (querypoint.second > rectangle.second.second) {

		dy = querypoint.second - rectangle.second.second;
	}


	double distance = sqrt(pow(dx, 2) + pow(dy, 2));

	return distance;  

*/

		//OR A SHORTER ALGORITHM INSPIRED BY STACK OVERFLOW: https://stackoverflow.com/questions/5254838/calculating-distance-between-a-point-and-a-rectangular-box-nearest-point

	std::vector<int> x_list = { rectangle.first.first - querypoint.first , 0 , querypoint.first - rectangle.second.first };
	std::vector<int> y_list = { rectangle.first.second - querypoint.second , 0 , querypoint.second - rectangle.second.second };

	dx = *std::max_element(x_list.begin(), x_list.end());
	dy = *std::max_element(y_list.begin(), y_list.end());

	double distance = sqrt(pow(dx, 2) + pow(dy, 2));

	return distance;

}



std::vector<coordinate_t> RTree::IncNearest(coordinate_t querypoint, RTree tree, int k) {

	Node* focusNode = tree.root;

	double distance;

	std::vector<coordinate_t> nearest_neighbor_list;		//list that contains upto k nearest neighbors of the querypoint
	int k_count = 0;										//keep a track of the number of elements inside the nearest_neighbors_list

	//push all the mbrs into the queue if the focusNode is the root
	if (focusNode == root) {

		for (int i = 0; i < focusNode->n; i++) {


			new_knn.push( std::make_tuple(focusNode->contents[i], focusNode, calc_distance(querypoint, std::get<pair_of_coordinates_t>(focusNode->contents[i]))));

		}


		//FOR DISPLAYING PURPOSES

		/*  
		for (int i = 0; i < focusNode->n; i++) {

			std::cout << std::get<pair_of_coordinates_t>(std::get<0>(new_knn.top())).first.first <<",";
			std::cout << std::get<pair_of_coordinates_t>(std::get<0>(new_knn.top())).first.second<<std::endl;
			
			std::cout << "distance: " << std::get<2>(new_knn.top())<<std::endl;
		}
		*/
	}

	//save the element that is on the top of the queue
	std::tuple < std::variant<coordinate_t, pair_of_coordinates_t>, Node*, double > current_top_element = new_knn.top();

	while (!new_knn.empty()) {

		//check if the current element at the top of the priority queue is an MBR
		if (!std::get<1>(current_top_element)->check_leaf()) {

			new_knn.pop();

			//find the index of the element that is at the top of the priority queue. We will use this to traverse into this element's (MBR is the element in this case) child
			auto top_index = std::find(std::get<1>(current_top_element)->contents.begin(), std::get<1>(current_top_element)->contents.end(), std::get<0>(current_top_element)) - std::get<1>(current_top_element)->contents.begin();

			//std::cout << "The index of value passed is " << top_index << std::endl;

			focusNode = std::get<1>(current_top_element)->children[top_index];   //need the index to know that we're checking the top element's child node

			


			//pushes elements to the new_knn priority queue along with the node that their in and their distances to the querypoint
			push_elements_to_queue(focusNode, querypoint);

			current_top_element = new_knn.top();    //set the current_top_element variable to hold the updated top after pushing the previous top element's child node's contents into the queue

		}


		//the top of the queue now contains a datapoint
		else {

				//the top of the priority queue will always contain that element which has the least distance to the querypoint. so we simply push that element into the nearest neighbors list
			nearest_neighbor_list.push_back(std::get<coordinate_t>(std::get<0>(new_knn.top())));

			
			k_count++;		//increase k_count to match the number of elements in the nearest neighbors list


			// FOR DISPLAYING PURPOSES : uncomment if you wish to see the exact distances of the datapoints to the trees.
			/*
			
			std::cout << "nearest neighbor distance: " << std::get<2>(new_knn.top()) << std::endl;


			std::cout << "neares neighbor is: " << std::get<coordinate_t>(std::get<0>(new_knn.top())).first << "," << std::get<coordinate_t>(std::get<0>(new_knn.top())).second << std::endl;
			*/
	

			//if the nearest neighbors list contains the same number of elements as k, return the list and break out of the loop.
			if (k_count == k) { 
				
				return nearest_neighbor_list;
				break; }
			

			//pop the top element off and restart the loop
			new_knn.pop();
			current_top_element = new_knn.top();
			
			
		}
	}

}
	
//pushes elements to the new_knn priority queue along with the node that their in and their distances to the querypoint

      void RTree::push_elements_to_queue(Node* focusNode, coordinate_t querypoint) {

		  //if it is a data node
		  if (focusNode->check_leaf()) {


			  for (int i = 0; i < focusNode->n; i++) {

				  new_knn.push(std::make_tuple(focusNode->contents[i], focusNode, calc_distance(querypoint, std::get<coordinate_t>(focusNode->contents[i]))));

			  }
		  }

		  //if it is an MBR node

		  else {

			  for (int i = 0; i < focusNode->n; i++) {

				  new_knn.push(std::make_tuple(focusNode->contents[i], focusNode, calc_distance(querypoint, std::get<pair_of_coordinates_t>(focusNode->contents[i]))));

			  }

		  }


}