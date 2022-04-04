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





//case 1: Insert into an empty tree, causing a degenerate MBR to form
//case 2: Insert into a datanode with one datapoint, causing an MBR to form in the root
//case 3: Insert into a tree of height 2 with a non-full MBR root node and a non-full datanode (causing the datanode to become full)
//case 4: Insert into tree of height 2 with a non-full MBR root node and a full datanode (causing a split in the datanodes and a new MBR to form)
//case 5: Insert into a tree of height 2 with a non-full MBR root node containing two MBRs which point to two full datanodes. Insertion causes a 3rd MBR to form and the root becomes full.
//case 6:  Insert into a tree of height 2 with a full MBR root node and non-full datanode (all datanodes are full except for one)
//case 7: Insert into a tree of height 2 with a full MBR root node and full datanode (causing a split to propogate up twice, changing the height from 2 to 3)

