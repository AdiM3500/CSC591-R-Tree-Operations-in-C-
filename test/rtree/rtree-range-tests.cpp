/**
 * Set of unit tests with which to evaluate the range query/ find function in the R-Tree implementation.
 */

#include "catch2/catch.hpp"
#include "a2/rtree/RTree.hpp"
#include <optional>



SCENARIO("We perform a range search on a tree of height 2")
{
	GIVEN("An R-Tree with 2 MBRs that point to 2 data nodes")
	{
		RTree tree;

		tree.root = new Node{ variety_content_list_t{ pair_of_coordinates_t{ {1,2}, {2,7} }, pair_of_coordinates_t{ {5,8} , {8,10} } } };

		tree.root->children[0] = new Node{ variety_content_list_t{ coordinate_t{1,2}, coordinate_t{2,4}, coordinate_t{1,7} } };
		tree.root->children[1] = new Node{ variety_content_list_t{coordinate_t{5,9},coordinate_t{7,8},coordinate_t{8,10} } };


		//case 1:
 		WHEN("We lookup a search rectangle that does not overlap any of the MBRs")
		{
			auto const actual_result = tree.find(pair_of_coordinates_t{ {4,3},{8,7} });

	

	
		
			THEN("The result is empty")
			{
				

				auto const expected_result = datapoint_list_t{};

				REQUIRE(actual_result == expected_result);
			}
		}

		
		//case 2:
		WHEN("We lookup a degenerate search rectangle that corresponds to a datapoint in one of the MBRs ")
		{

			auto const actual_result = tree.find(pair_of_coordinates_t{ {2,4},{2,4} });


			THEN("The datapoint corresponding to the degenerate MBR is returned")
			{

				auto const expected_result = datapoint_list_t{ coordinate_t{2,4} };

				REQUIRE(actual_result == expected_result);
			}
		}

	
			
		//case 3:
		WHEN("We lookup a search rectangle that spans a single MBR")
		{

			auto const actual_result = tree.find(pair_of_coordinates_t{ {5,8} , {8,10} });

			THEN("The datapoints contained within that MBR are returned")
			{

				auto const expected_result = datapoint_list_t{ coordinate_t{5,9},coordinate_t{7,8},coordinate_t{8,10} };

				REQUIRE(actual_result == expected_result);
			}


		}

		
		//case 4:
		WHEN("We lookup a search rectangle that spans the entire tree")
		{
			auto const actual_result = tree.find(pair_of_coordinates_t{ {1,2},{8,10} });


			THEN("All datapoints contained within the tree are returned")
			{

				auto const expected_result = datapoint_list_t{ coordinate_t{1,2}, coordinate_t{2,4}, coordinate_t{1,7}, coordinate_t{5,9},coordinate_t{7,8},coordinate_t{8,10} };

				REQUIRE(actual_result == expected_result);
			}
		}

		
		//case 5:
		WHEN("We lookup a search rectangle that partially overlaps both the MBRs in tree")
		{

			auto const actual_result = tree.find(pair_of_coordinates_t{ {1,3},{6,10} });

			THEN("Only those datapoints from the two MBRs that are contained within the search rectangle are returned")
			{

				auto const expected_result = datapoint_list_t{ coordinate_t{2,4}, coordinate_t{1,7}, coordinate_t{5,9} };

				REQUIRE(actual_result == expected_result);
			}
		}

		
		
	}
}





SCENARIO("We perform a range search on an R-Tree of height 3")
{

	GIVEN("An R-Tree with 6 MBR nodes and 4 datanodes")
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
		

		//case 6:
		WHEN("We lookup a search rectangle that spans the largest MBR in the tree")
		{

			auto const actual_result = tree.find( pair_of_coordinates_t{ {5,1},{11,10} } );

			THEN("All datapoints contained within that largest MBR are returned")
			{

				auto const expected_result = datapoint_list_t{ coordinate_t{5,9},coordinate_t{7,8},coordinate_t{8,10}, coordinate_t{6,6},coordinate_t{7,5},coordinate_t{8,4},
				coordinate_t{9,2},coordinate_t{10,1},coordinate_t{11,3} };

				REQUIRE(actual_result == expected_result);
			}
		}

		//case 7:
		WHEN("We lookup a search rectangle that partially overlaps 2 datapoints in the first MBR of the root and 2 datapoints in the second MBR of the root ")
		{

			auto const actual_result = tree.find(pair_of_coordinates_t{ {1,3},{6,10} });

			THEN("The 4 datapoints that are overlapped by the search rectangle are returned")
			{

				auto const expected_result = datapoint_list_t{ coordinate_t{2,4}, coordinate_t{1,7}, coordinate_t{5,9}, coordinate_t{6,6} };

				REQUIRE(actual_result == expected_result);
			}
		}
	}
}




//case 1: We do a range search of a search rectangle that does not overlap any MBRs in an R-Tree of height 2
//case 2: We do a range search of a degenerate search ractangle in an R-tree of height 2.
//case 3: We do a range search of a search rectangle that spans a single MBR in a tree of height 2.
//case 4: We do a range search of a search rectangle that spans the entire tree of height 2.
//case 5: We look for a search rectangle that partially overlaps 2 MBRs on a tree of height 2.
//case 6: We look for a search rectangle that spans the largest MBR in a tree of height 3.
//case 7: We look for a search rectangle that partially spans both root MBRs in a tree of height 3.





//note: the range query will return all the datapoints that are present within the search rectangle