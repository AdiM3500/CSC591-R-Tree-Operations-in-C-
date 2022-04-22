#include "catch2/catch.hpp"
#include "a2/rtree/RTree.hpp"
#include <optional>


SCENARIO("We search for nearest neighbors in an r-tree of height 1")
{
	GIVEN("An r-tree with one full datanode ")
	{
		RTree tree;

		//tree.AddDatapoint(coordinate_t{ 2,2 }, tree.root);
		//tree.AddDatapoint(coordinate_t{ 4,2 }, tree.root);
		//tree.AddDatapoint(coordinate_t{ 6,4 }, tree.root);

		tree.root = new Node{ variety_content_list_t{ pair_of_coordinates_t{ {2,2}, {6,4} } } };
		tree.root->children[0] = new Node{ variety_content_list_t{ coordinate_t{2,2},coordinate_t{4,2},coordinate_t{6,4} } };


		//case 1:
		WHEN("We lookup a closest neighbor to a querypoint NOT in the tree but in between the min and max keys (i.e. a querypoint just above the rectangle)")
		{
			auto querypoint = coordinate_t{4,5};
			auto real_solution = tree.IncNearest(querypoint, tree, 1);

			THEN("The closest datapoint to the querypoint is returned")
			{
				std::cout << std::endl;
				std::cout << std::endl;
			
				std::vector<coordinate_t> nearest_point = { coordinate_t{6,4} };

				std::cout << std::endl;

				REQUIRE(nearest_point == real_solution);
			}
		}


		//case 2:
		WHEN("We lookup a closest neighbor to a querypoint NOT in the tree and LARGER than the max key of the tree ")
		{
			auto querypoint = coordinate_t{ 8,7 };
			auto real_solution = tree.IncNearest(querypoint, tree, 1);
			THEN("The closest neighbor of the querypoint (which in this case is the MAX KEY) is returned")
			{
				std::vector<coordinate_t> nearest_point = { coordinate_t{6,4} };

				REQUIRE(nearest_point == real_solution);

				//std::cout << "\nlets see if its same or refreshed?\n";
				//for (const auto& x : nearest_point) {
				
					//std::cout << x.first << "," << x.second <<std::endl;
			//	}


			}
		}


		//case 3:
		WHEN("We look for 3 closest neighbors of a querypoint not in the tree")
		{
			auto querypoint = coordinate_t{ 4,1 };
			auto real_solution = tree.IncNearest(querypoint, tree, 3);

			THEN("The 3 closest neighbors are returned in the increasing order of their distances to the querypoint")
			{
				std::vector<coordinate_t> nearest_neighbors = { coordinate_t{4,2}, coordinate_t{2,2}, coordinate_t{6,4} };

				REQUIRE(nearest_neighbors == real_solution);

			}
		}
	}

}


SCENARIO("We do a nearest neighbor lookup on an r-tree of height 3")
{
	GIVEN("The usual r-tree of height 3")
	{
		RTree tree;

		//  tree.root is a root node that contains MBRs and points to two MBR nodes
		tree.root = new Node{ variety_content_list_t{ pair_of_coordinates_t{ {1,2}, {2,7} }, pair_of_coordinates_t{ {5,1} , {11,10} } } };

		tree.root->children[0] = new Node{ variety_content_list_t{ pair_of_coordinates_t{ {1,2}, {2,7} } } };

		//children[0] is a leaf mbr node that contains 1 MBR and points to a data node
		tree.root->children[0]->children[0] = new Node{ variety_content_list_t{ coordinate_t{1,2},coordinate_t{2,4},coordinate_t{1,7} } };


		tree.root->children[1] = new Node{ variety_content_list_t{ pair_of_coordinates_t{ {5,8}, {8,10} },
			pair_of_coordinates_t{{6,4},{8,6}}, pair_of_coordinates_t{ {9,1}, {11,3} }   } };

		//children[1] is a leaf mbr node that contains 3 MBRs and points to 3 data nodes
		tree.root->children[1]->children[0] = new Node{ variety_content_list_t{ coordinate_t{5,9},coordinate_t{7,8},coordinate_t{8,10} } };

		tree.root->children[1]->children[1] = new Node{ variety_content_list_t{ coordinate_t{6,6},coordinate_t{7,5},coordinate_t{8,4} } };

		tree.root->children[1]->children[2] = new Node{ variety_content_list_t{ coordinate_t{9,2},coordinate_t{10,1},coordinate_t{11,3} } };


		//case 4:
		WHEN("We look for the closest point to a querypoint that is IN the tree, inside the 3rd child mbr, of the 2nd root mbr")
		{
			auto querypoint = coordinate_t{ 11,1 };
			auto real_solution = tree.IncNearest(querypoint, tree, 1);

			THEN("The closest datapoint in the 3rd child mbr, of the 2nd root mbr is returned")
			{
				std::vector<coordinate_t> expected_solution = { coordinate_t{10,1} };

				REQUIRE(real_solution == expected_solution);
			}
		}

		//case 5:
		WHEN("We look for 2 closest points to a querypoint that is present in the tree, inside the 2nd root mbr, with the closest points being in different children of the parent")
		{

			auto querypoint = coordinate_t{ 7,7 };
			auto real_solution = tree.IncNearest(querypoint, tree, 2);
			THEN("The 2 closest datapoints are returned which belong to different mbrs inside the 2nd root mbr (tree.root->children[1]->children[0] and tree.root->children[1]->children[1] ), in the increasing order of their distances")
			{
				std::vector<coordinate_t> expected_solution = { coordinate_t{7,8}, coordinate_t{6,6} };

				REQUIRE(real_solution == expected_solution);
			}
		}

		//case 6:
		WHEN("We look for 2 closest points to a querypoint that is outside the r-tree, and the 2 closest points are present in different mbrs with distinct parent mbrs")
		{
			auto querypoint = coordinate_t{ 4,6 };
			auto real_solution = tree.IncNearest(querypoint, tree, 2);

			THEN("The 2 closest points from two different mbrs present in two distinct parents respectively are returned (tree.root->children[1]->children[1] and tree.root->children[0]->children[0])")
			{

				std::vector<coordinate_t> expected_solution = { coordinate_t{6,6}, coordinate_t{2,4} };

				

				REQUIRE(real_solution == expected_solution);
			}
		}

		//case 8:
		WHEN("We look for n nearest neighbors of a querypoint in a tree of height 3")
		{
			auto querypoint = coordinate_t{ 7,2 };
			auto real_solution = tree.IncNearest(querypoint, tree, 12);    //k = n, which is 12 in this case

			
			THEN("All points in the tree are returned")
			{
				std::vector<coordinate_t> expected_solution = { coordinate_t{9,2}, coordinate_t{8,4}, coordinate_t{7,5}, coordinate_t{10,1}, 
				coordinate_t{6,6}, coordinate_t{11,3}, coordinate_t{2,4}, coordinate_t{1,2}, coordinate_t{7,8}, coordinate_t{5,9}, coordinate_t{1,7}, coordinate_t{8,10} };

			
				REQUIRE(expected_solution == real_solution);

			}

		}
	}
}


SCENARIO("We do a nearest neighbor lookup for a querypoint where the nearest neighbors are all located in different mbrs")
{
	GIVEN("An r-tree of height 2")
	{
		RTree tree;

		tree.root = new Node{ variety_content_list_t{ pair_of_coordinates_t{ {1,3}, {2,7} }, pair_of_coordinates_t{ {4,8}, {6,10} }, pair_of_coordinates_t{ {4,4}, {7,6} } } };
	
		tree.root->children[0] = new Node{ variety_content_list_t{ coordinate_t{1,3}, coordinate_t{2,7} } };
		tree.root->children[1] = new Node{ variety_content_list_t{ coordinate_t{4,8}, coordinate_t{6,10} } };
		tree.root->children[2] = new Node{ variety_content_list_t{ coordinate_t{4,4}, coordinate_t{7,6} } };

		//case 7:
		WHEN("We look for 3 closest points to a querypoint which is equally distant from all the mbr's points")
		{
			auto querypoint = coordinate_t{5,7};
			auto real_solution = tree.IncNearest(querypoint, tree, 3);

			THEN("closest datapoints from 3 different mbrs are returned")
			{
				std::vector<coordinate_t> expected_solution = { coordinate_t{4,8}, coordinate_t{7,6}, coordinate_t{2,7} };
				
			//	for (const auto& x : tree.IncNearest(querypoint, tree, 3)) {

				//	std::cout << x.first << "," << x.second << std::endl;
				//}

				REQUIRE(expected_solution == real_solution);
			}
		}
	}
}


SCENARIO("We do a nearest neigbor lookup for a qurypoint that is equidistant from two mbrs")
{
	GIVEN("An r-tree of height 2")
	{
		RTree tree;

		tree.root = new Node{ variety_content_list_t{ pair_of_coordinates_t{ {1,2}, {3,7} }, pair_of_coordinates_t{ {5,2}, {6,6} } } };

		tree.root->children[0] = new Node{ variety_content_list_t{ coordinate_t{1,2}, coordinate_t{1,4},  coordinate_t{3,7} } };
		tree.root->children[1] = new Node{ variety_content_list_t{ coordinate_t{5,2}, coordinate_t{5,4}, coordinate_t{6,6} } };

		//case 9:
		WHEN("We look for a closest neighbor to a querypoint that is equidistant from both the mbrs")
		{

			auto querypoint = coordinate_t{4,5};

			auto real_solution = tree.IncNearest(querypoint, tree, 1);

			THEN("We get the datapoint that contains the smallest distance to the querypoint, regardless of the two equidistant mbrs")
			{
				std::vector<coordinate_t> expected_solution = { coordinate_t{5,4} };

				REQUIRE(real_solution == expected_solution);

			}
		}
	}
}

//case 10:

SCENARIO("We do a nearest neighbor lookup for a querypoint in an r-tree where all mbrs overlap each other")
{

	GIVEN("A tree of height 2 where all mbrs overlap")
	{

		RTree tree; 

		tree.root = new Node{ variety_content_list_t{ pair_of_coordinates_t{ {1,4}, {3,8} }, pair_of_coordinates_t{ {2,3}, {5,6} }, pair_of_coordinates_t{ {4,2}, {6,4} } } };

		tree.root->children[0] = new Node{ variety_content_list_t{ coordinate_t{1,4}, coordinate_t{2,7}, coordinate_t{3,8} } };
		tree.root->children[1] = new Node{ variety_content_list_t{ coordinate_t{2,3}, coordinate_t{3,3}, coordinate_t{5,6} } };
		tree.root->children[2] = new Node{ variety_content_list_t{ coordinate_t{4,2}, coordinate_t{4,4}, coordinate_t{6,4} } };   //3rd root mbr


		WHEN("We mark a querypoint that is inside the 2nd root mbr, and look for it's closest neighbor (which is contained in the 3rd root mbr in this case)")
		{
			auto querypoint = coordinate_t{ 4,5 };

			auto real_solution = tree.IncNearest(querypoint, tree, 1);

				

				THEN("A datapoint from the 3rd root mbr is returned, since it is the closest to the querypoint")
			{
					std::vector<coordinate_t> expected_solution = { coordinate_t{4,4} };

					REQUIRE(expected_solution == real_solution);
				
			}
		}
	}
}

//kNN Test cases :

//1. Search tree with 1 full node for 1 closest point, query point not in tree but between minand max keys
//2. Search tree with 1 full node for 1 closest point, query point larger than max key in tree
//3. Search tree with 1 full node for 3 closest points, query point not in tree
//4. Search tree of height 3 for 1 closest point, query point* in* tree
//5. Search tree for 2 closest points, each found in different MBR with common parent MBR
//6. Search tree for 2 closest points, each found in different MBR's with distinct parent MBR's
//7. Search tree for 3 closest points, each found in different MBR's'
//8. Search tree with height >= 2 for k closest points, where k = n(i.e., all points should be returned)
//9. Search tree for closest point, where two MBR's are equidistant from the query point
//10. Search tree with height 2 for closest point, where all child MBR's overlap each other
