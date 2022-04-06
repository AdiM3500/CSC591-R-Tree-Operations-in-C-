/**
 * Set of unit tests with which to evaluate the insertion query in the RTree implementation.
 */

#include "catch2/catch.hpp"
#include "a2/rtree/RTree.hpp"
#include <optional>


//PRE-CASE CHECKING THE COMPARISON OPERATOR
SCENARIO("We compare two R-Tree objects")
{

	GIVEN("An R-Tree of height 2")
	{
		RTree tree;

		tree.root = new Node{ variety_content_list_t{ pair_of_coordinates_t{ {1,2}, {2,7} }, pair_of_coordinates_t{ {5,8} , {8,10} } } };

		tree.root->children[0] = new Node{ variety_content_list_t{ coordinate_t{1,2}, coordinate_t{2,4}, coordinate_t{1,7} } };
		tree.root->children[1] = new Node{ variety_content_list_t{coordinate_t{5,9},coordinate_t{7,8},coordinate_t{8,10} } };

	//	std::cout << "\t Tree 1 traversal: \n";
		
		//tree.depthFirstTraversal(tree.root);

	//	std::cout << "\n-----------------------------------------\n";


		WHEN("We create an exact copy of the first R-Tree object")
		{
			RTree copy(tree);

			//std::cout << "\t Tree 2 traversal: \n";

			//copy.depthFirstTraversal(copy.root);

		//	std::cout << "\n-----------------------------------------\n";

			THEN("The two trees are considered equal")
			{

				REQUIRE(tree == copy);
			}
		}


		WHEN("We create an empty R-Tree object")
		{
			RTree copy2{};

			THEN("The two trees are *not* considered equal")
			{
				REQUIRE(! (tree == copy2) );
			}
		}


		WHEN("We create an r-tree object that is different than our current tree object")
		{

			RTree tree2;

			tree2.root = new Node{ variety_content_list_t{ pair_of_coordinates_t{ {1,2}, {2,7} } } };

			tree2.root->children[0] = new Node{ variety_content_list_t{ coordinate_t{1,2}, coordinate_t{2,4}, coordinate_t{1,7} } };

			
			THEN("The two trees are *not* considered equal")
			{

				REQUIRE(!(tree == tree2));
			}
		}

		WHEN("We create another tree that is similar to the first tree but is missing a couple datapoints")
		{

			RTree tree3;

			tree3.root = new Node{ variety_content_list_t{ pair_of_coordinates_t{ {1,2}, {2,7} }, pair_of_coordinates_t{ {5,8} , {8,10} } } };

			tree3.root->children[0] = new Node{ variety_content_list_t{ coordinate_t{1,2}, coordinate_t{2,4}, coordinate_t{1,7} } };
			tree3.root->children[1] = new Node{ variety_content_list_t{coordinate_t{5,9} } };


			THEN("The two trees are not equal")
			{

				REQUIRE(!(tree == tree3));
			}
		}
	


	}
}


 

//case 1:
SCENARIO("Insert into an empty tree") 
{

	GIVEN("An empty r-tree")
	{
		RTree tree;

		WHEN("We insert a datapoint into the tree")
		{

			tree.AddDatapoint(coordinate_t{ 2,4 }, tree.root);

			THEN("We end up with an R-Tree with a degenerate MBR pointing to a datanode containing that inserted datapoint")
			{

				RTree expected_solution;
				expected_solution.root = new Node{ variety_content_list_t{ pair_of_coordinates_t{ {2,4}, {2,4} } } };

				expected_solution.root->children[0] = new Node{ variety_content_list_t{coordinate_t{2,4} } };

			
				//tree.depthFirstTraversal(tree.root);

				REQUIRE(tree == expected_solution);
			}
		}
	}

}


//case 2:
SCENARIO("Insert into a tree of height 2 and a datapoint inside the area indexed")
{

	GIVEN("An r-tree of height 2 which contains two MBRs pointing to two datanodes, one of which is non-full")
	{

		RTree tree;

		auto const datapoint_to_insert = coordinate_t{ 7,5 };  //datapoint we're inserting

		tree.root = new Node{ variety_content_list_t{ pair_of_coordinates_t{ {1,2}, {2,7} }, pair_of_coordinates_t{ {6,4}, {8,6} } } };

		tree.root->children[0] = new Node{ variety_content_list_t{ coordinate_t{1,2},coordinate_t{2,4},coordinate_t{1,7} } };   //datanode is full
		tree.root->children[1] = new Node{ variety_content_list_t{ coordinate_t{6,6},coordinate_t{8,4} } };						//datanode is non-full

		WHEN("We insert a datapoint that is indexed within the area of one of the non-full MBRs")
		{
			tree.AddDatapoint(datapoint_to_insert, tree.root);

			THEN("The datapoint is inserted into the correct non-full datanode")
			{
				RTree expected_solution;

				expected_solution.root = new Node{ variety_content_list_t{ pair_of_coordinates_t{ {1,2}, {2,7} }, pair_of_coordinates_t{ {6,4}, {8,6} } } };
				expected_solution.root->children[0] = new Node{ variety_content_list_t{ coordinate_t{1,2},coordinate_t{2,4},coordinate_t{1,7} } };  
				expected_solution.root->children[1] = new Node{ variety_content_list_t{ coordinate_t{6,6},coordinate_t{8,4}, datapoint_to_insert} };	//datanode gets inserted with the datapoint


				REQUIRE(tree == expected_solution);
			}
		}
	}
}




//case 3:

SCENARIO("Insert into a tree of height 2 and a datapoint outside the area indexed by the tree")
{

	GIVEN("An r-tree of height 2 containing two MBRs which point to two data nodes")
	{
		RTree tree;

		tree.root = new Node{ variety_content_list_t{ pair_of_coordinates_t{ {1,2}, {2,4} }, pair_of_coordinates_t{ {6,4}, {8,6} } } };

		tree.root->children[0] = new Node{ variety_content_list_t{ coordinate_t{1,2}, coordinate_t{2,4} } };
		tree.root->children[1] = new Node{ variety_content_list_t{ coordinate_t{6,6}, coordinate_t{7,5}, coordinate_t{8,4} } };

		tree.depthFirstTraversal(tree.root);
		std::cout << std::endl;

		WHEN("We insert a datapoint that is outside of the indexed area of both the MBRS")
		{
			auto const datapoint_to_insert = coordinate_t{ 1,7 };
			tree.AddDatapoint(datapoint_to_insert, tree.root);

			THEN("The MBR closest to the datapoint gets expanded to accomodate for that datapoint")
			{

				RTree expected_solution;

				//the first MBR in the root gets expanded since it takes the least amount of area to grow and accomodate the datapoint
				expected_solution.root = new Node{ variety_content_list_t{ pair_of_coordinates_t{ {1,2}, {2,7} }, pair_of_coordinates_t{ {6,4}, {8,6} } } };

				expected_solution.root->children[0] = new Node{ variety_content_list_t{ coordinate_t{1,2}, coordinate_t{2,4}, datapoint_to_insert } };
				expected_solution.root->children[1] = new Node{ variety_content_list_t{ coordinate_t{6,6}, coordinate_t{7,5}, coordinate_t{8,4} } };

				//tree.depthFirstTraversal(tree.root);


				REQUIRE(tree == expected_solution);

			}

		}
		

	}
	


}


//case 6:

SCENARIO("We insert a datapoint into a tree of height 3")
{

	GIVEN("An r-tree of height 3")
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
		tree.root->children[1]->children[0] = new Node{ variety_content_list_t{ coordinate_t{5,8},coordinate_t{8,10} } };

		tree.root->children[1]->children[1] = new Node{ variety_content_list_t{ coordinate_t{6,6},coordinate_t{7,5},coordinate_t{8,4} } };

		tree.root->children[1]->children[2] = new Node{ variety_content_list_t{ coordinate_t{9,2},coordinate_t{10,1},coordinate_t{11,3} } };


		WHEN("We insert a datapoint that is not indexed by any of the root MBRs but is closest to the rightmost root MBR")
		{
			auto const datapoint_to_insert = coordinate_t{ 4,9 };

			tree.AddDatapoint(datapoint_to_insert, tree.root);

			THEN("The rightmost MBR in the root gets expanded to accomodate the datapoint. Also, that root MBR's leftmost child gets expanded to accomodate the datapoint as well.")
			{
				RTree expected_solution;
																														//rightmost root MBR gets expanded
				expected_solution.root = new Node{ variety_content_list_t{ pair_of_coordinates_t{ {1,2}, {2,7} }, pair_of_coordinates_t{ {4,1} , {11,10} } } };

				expected_solution.root->children[0] = new Node{ variety_content_list_t{ pair_of_coordinates_t{ {1,2}, {2,7} } } };

				//children[0] is a leaf mbr node that contains 1 MBR and points to a data node
				expected_solution.root->children[0]->children[0] = new Node{ variety_content_list_t{ coordinate_t{1,2},coordinate_t{2,4},coordinate_t{1,7} } };

					
				expected_solution.root->children[1] = new Node{ variety_content_list_t{ pair_of_coordinates_t{ {4,8}, {8,10} },     //leftmost child of rightmost root MBR gets expanded
					pair_of_coordinates_t{{6,4},{8,6}}, pair_of_coordinates_t{ {9,1}, {11,3} }   } };

				//children[1] is a leaf mbr node that contains 3 MBRs and points to 3 data nodes
				expected_solution.root->children[1]->children[0] = new Node{ variety_content_list_t{ coordinate_t{5,8},coordinate_t{8,10}, datapoint_to_insert } };

				expected_solution.root->children[1]->children[1] = new Node{ variety_content_list_t{ coordinate_t{6,6},coordinate_t{7,5},coordinate_t{8,4} } };

				expected_solution.root->children[1]->children[2] = new Node{ variety_content_list_t{ coordinate_t{9,2},coordinate_t{10,1},coordinate_t{11,3} } };

				//tree.depthFirstTraversal(tree.root);

				REQUIRE(tree == expected_solution);
			}

		}

	}
}


//CASE 4, CASE 5 AND CASE 7, which were unit_tests to test the functionality of the node-split have not been written

//case 1: Insert into an empty tree, causing a degenerate MBR to form
//case 2: Insert a datapoint into a tree of height 2 where the datapoint is contained within one of the mbrs
//case 3: Insert a datapoint into a tree of height 2 where the datapoint is *NOT* contained within any of its mbrs
//case 4: Insert a datapoint into a tree of height 2 which contains a single MBR that points to a full-datanode. Insertion will cause a node-split of the datanode and make two seperate MBRs in the root.
//case 5: Insert into a tree of height 2 with a full MBR root node and full datanode (causing a split to propogate up twice, changing the height from 2 to 3)
//case 6: Insert a datapoint into a tree of height 3 where the datapoint is *NOT* contained within any internal node MBRs (although the datapoint is contained in at least one of the root mbrs)
//case 7: Insert into a tree of height 2 with a full MBR root node and full datanode (causing a split to propogate up twice, changing the height from 2 to 3)

