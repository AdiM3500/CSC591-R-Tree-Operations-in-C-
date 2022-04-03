/**
 * Set of unit tests with which to evaluate the lookup/find function in the R-Tree implementation.
 */

#include "catch2/catch.hpp"
#include "a2/rtree/RTree.hpp"
#include <optional>


//case 1:
SCENARIO("We perform a lookup on an empty tree")
{

    GIVEN("An empty R-Tree and a search datapoint")
    {

        auto tree = RTree{};
        auto const datapoint = coordinate_t{ 1,2 };

        WHEN("We lookup if the key is found in the tree")
        {
            auto const actual_result = tree.find(datapoint);

            THEN("The result is null")
            {
                auto const expected_result = std::nullopt;
                REQUIRE(actual_result == expected_result);
            }
           
        }
    }
}


SCENARIO("We perform a lookup on a tree with one node ")
{

    //case 2:
    GIVEN("An R-Tree with a single data node")

    {
        RTree tree;

     //   variety_content_list_t mbr = { pair_of_coordinates_t{ {1,2},{4,5} }  };

        variety_content_list_t datanode = { coordinate_t{1,2}, coordinate_t{3,5}, coordinate_t{4,3} };

        tree.root = new Node(datanode);

      //  tree.root->children[0] = new Node (datanode);

        auto const datapoint = coordinate_t{ 7,8 };


        WHEN("We lookup a key that is not in the tree")
        {

            auto const actual_result = tree.find(datapoint);
            
            THEN("The result is not found")
            {
                
                auto const expected_result = std::nullopt;

                REQUIRE(actual_result == std::nullopt);
            }

        }

        //case 2, part 2: Needed to check if the root node is being returned if the datapoint DOES EXIST in the RTree
        WHEN("We lookup a key that is in the tree")
        {

            auto const actual_result = tree.find(coordinate_t{ 3,5 });

            THEN("The root node is returned")
            {
                auto const expected_result = tree.root;

                CHECK(actual_result != std::nullopt);

                REQUIRE(*actual_result == expected_result);
            }
        }
        

    }
}


SCENARIO("We perform a lookup on a tree of height 2")
{
    GIVEN("An R-tree with 1 MBR Node that contains 2 MBRs which point to 2 datanodes ")
    {
        RTree tree;

        tree.root = new Node{ variety_content_list_t{ pair_of_coordinates_t{ {1,2}, {2,7} }, pair_of_coordinates_t{ {5,8} , {8,10} } } };

        tree.root->children[0] = new Node{ variety_content_list_t{ coordinate_t{1,2}, coordinate_t{2,4}, coordinate_t{1,7} } };
        tree.root->children[1] = new Node{ variety_content_list_t{coordinate_t{5,9},coordinate_t{7,8},coordinate_t{8,10}} };

        //case 3:
        WHEN("We lookup a datapoint outside the area indexed by the tree")
        {
            auto const actual_result = tree.find(coordinate_t{6,6});

            THEN("The result is not found")
            {
                //auto const expected_result = std::nullopt;

                REQUIRE(actual_result == std::nullopt);
            }
        }


        //case 4:
        WHEN("We lookup a datapoint that is definitely in the tree")
        {
            auto const actual_result = tree.find(coordinate_t{5,9});

            THEN("The rightmost data node that contains the datapoint is returned ")
            {

                auto const expected_result = tree.root->children[1];

                CHECK(actual_result != std::nullopt);

                    REQUIRE(*actual_result == expected_result);
            }
        }

        //case 5:
      WHEN("We lookup a datapoint thaat is not in the tree but could be inside one of the leaf MBR nodes")
        {

            auto const actual_result = tree.find(coordinate_t{7,9});

            THEN("The Node that could contain the datapoint is returned")
            {
                auto const expected_result = tree.root;

                CHECK(actual_result != std::nullopt);
                REQUIRE(*actual_result == expected_result);
            }


        }

    
    }
}


//case 7:
SCENARIO("We perform a lookup on a tree of height 3")
{
    GIVEN("An R-tree with 6 MBR nodes and 4 data Nodes")
    {
        RTree tree;

     //   variety_content_list_t root_mbr = { pair_of_coordinates_t{ {5,1},{11,10} } };

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
     //   tree.root->children


        WHEN("We lookup a point inside the tree")
        {
            auto const actual_result = tree.find(coordinate_t{ 8,4 });

            THEN("The datanode containing the point is returned")
            {

                auto const expected_result = tree.root->children[1]->children[1];

                CHECK(actual_result != std::nullopt);
                REQUIRE(*actual_result == expected_result);
            }
        }



        //case 7:
        WHEN("We lookup a point outside the tree")
        {
            auto const actual_result = tree.find(coordinate_t{4,6});

            THEN("The result is not found")
            {
                auto const expected_result = std::nullopt;

                REQUIRE(actual_result == expected_result);
               
            }

        }
    }
}


// case 1: search for a point in an empty tree
// case 2: search for a point not in a tree with just one data node
// case 3: search for a point outside the area indexed by a tree of height two
// case 4: search for a point that is in a tree of height two
// case 5: search for a point not in a tree of height two but inside one of the leaf MBR's
// case 6: search for a point that is in a tree of height three
// case 7: search for a point htat is outside the area indexed by the leaves of a tree of height three
