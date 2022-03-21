/**
 * Set of unit tests with which to evaluate the lookup/find function in the BTree implementation.
 */

#include "catch2/catch.hpp"
#include "a2/rtree/RTree.hpp"

SCENARIO( "We perform a range lookup on an empty tree", "[btree][empty][range][a1]")
{
    GIVEN( "An empty B-Tree and a search range" )
    {
        auto tree = BTree{};
        auto const lower = key_t{ 12 };
        auto const upper = key_t{ 13 };

        WHEN( "We lookup all the keys in the tree within the range" )
        {
            auto const actual_result = tree.find( lower, upper );

            THEN( "The result is empty" )
            {
                auto const expected_result = key_list_t{};
                REQUIRE( actual_result == expected_result );
            }
        }
    }
}


SCENARIO( "We perform a range lookup on a tree with only one node", "[btree][root][range][a1]")
{
    GIVEN( "A B-Tree with a single node" )
    {
        auto tree = BTree{ new Node{ { 1, 3 } } };

        
        WHEN( "We lookup a range wider than that in the tree" )
        {
            auto const lower = key_t{ 0 };
            auto const upper = key_t{ 42 };
            auto const actual_result = tree.find( lower, upper );

            THEN( "The entire range is returned in sorted order" )
            {
                auto const expected_result = key_list_t{ 1, 3};

                REQUIRE( actual_result == expected_result );
            }
        }

        WHEN ("We lookup a range smaller than that in the tree")
        {
            auto const lower = key_t{ 0 };
            auto const upper = key_t{ 2 };
            auto const actual_result = tree.find( lower, upper );

            THEN( "The entire range is returned in sorted order" )
            {
                auto const expected_result = key_list_t{ 1 };

                REQUIRE( actual_result == expected_result );
            }
        }
    }
}


//Aaditya's written tests
SCENARIO("We perform a range lookup on a tree with three nodes i.e. height of the tree is 2","[btree][root][range2][a1]")
{

    GIVEN("A B-tree with 4 nodes")
    {
        
        auto tree = BTree{ new Node{ { 3, 7 } } };
        tree.root->children[0] = new Node(1);
        tree.root->children[1] = new Node(5);
        tree.root->children[2] = new Node{ {9,11} };

       //case 3:
        WHEN("We lookup a range equal to that of the tree")
        {
            auto const lower = key_t{ 1 };
            auto const upper = key_t{ 12 };
            auto const actual_result = tree.find(lower, upper);


               
            THEN("The full traversal is returned in sorted order") 
            {

                auto const expected_result = key_list_t{ 1, 3, 5, 7, 9, 11};

                REQUIRE(actual_result == expected_result);
            }
        }

        //case 4:
        WHEN("We lookup a range that only retrieves the middle half at height 2")
        {

            auto const lower = key_t{ 1 };
            auto const upper = key_t{ 6 };
            auto const actual_result = tree.find(lower, upper);

             THEN("Only half of the tree (smaller half) is returned in sorted order") 
            {

                auto const expected_result = key_list_t{ 1, 3, 5};

                REQUIRE(actual_result == expected_result);
            }


        }

        //case 5:
        WHEN("the lower bound is equal to the upper bound")
        {

            auto const lower = key_t{ 5 };
            auto const upper = key_t{ 5 };
            auto const actual_result = tree.find(lower, upper);

             THEN("the return value contains the key") 
            {

                auto const expected_result = key_list_t{ 5 };

                REQUIRE(actual_result == expected_result);
            }


        }
            
    }
}



SCENARIO("We perform a range lookup on a tree of height 3")
{

    GIVEN("A b-tree with 10 nodes")
    {
        auto tree = BTree{ new Node{ { 4, 10 } } };
        tree.root->children[0] = new Node(2);
        tree.root->children[1] = new Node(7);
        tree.root->children[2] = new Node(16);

        tree.root->children[0]->children[0] = new Node(1);
        tree.root->children[0]->children[1] = new Node(3);

        tree.root->children[1]->children[0] = new Node(5);
        tree.root->children[1]->children[1] = new Node(8);

        tree.root->children[2]->children[0] = new Node(13);
        tree.root->children[2]->children[1] = new Node(19);

        //case 6:
        WHEN("We lookup a range equal to that of a tree")
        {
            auto const lower = key_t{ 1 };
            auto const upper = key_t{ 20 };
            auto const actual_result = tree.find(lower, upper);


            THEN("The full traversal is returned in sorted order")
            {

                auto const expected_result = key_list_t{ 1, 2, 3, 4, 5, 7, 8, 10, 13, 16, 19 };

                REQUIRE(actual_result == expected_result);
            }
        }

        //case 7:
        WHEN("We lookup a range that starts from the middle element of the B-tree till the end of the B-tree")
        {
            auto const lower = key_t{ 7 };
            auto const upper = key_t{ 20 };
            auto const actual_result = tree.find(lower, upper);


            THEN("The largest half of elements are returned in sorted order")
            {

                auto const expected_result = key_list_t{ 7, 8, 10, 13, 16, 19 };

                REQUIRE(actual_result == expected_result);
            }
        }
        
    }
    
}
// case 3: full traversal on a tree of height 2
// case 4: traversal only retrieves the middle half at height 2
// case 5: lower == upper on tree of height 2, contains key
// case 6: full traversal on a tree of height 3
// case 7: traversal only gets largest half of elements in tree of height 3
