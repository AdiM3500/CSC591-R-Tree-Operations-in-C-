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
    GIVEN("An R-Tree with a single MBR node that points to a datanode")

    {
        RTree tree;

        variety_content_list_t mbr = { pair_of_coordinates_t{ {1,2},{4,5} }  };

        variety_content_list_t datanode = { coordinate_t{1,2}, coordinate_t{3,5}, coordinate_t{4,3} };

        tree.root = new Node(mbr);

        tree.root->children[0] = new Node (datanode);

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


// case 1: search for a point in an empty tree
// case 2: search for a point not in a tree with just one data node
// case 3: search for a point outside the area indexed by a tree of height two
// case 4: search for a point that is in a tree of height two
// case 5: search for a point not in a tree of height two but inside one of the leaf MBR's
// case 6: search for a point that is in a tree of height three
// case 7: search for a point htat is outside the area indexed by the leaves of a tree of height three
