/**
 * Set of unit tests with which to evaluate the lookup/find function in the BTree implementation.
 */

#include "catch2/catch.hpp"
#include "a1/btree/BTree.hpp"

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
        auto tree = BTree{ new Node{ { 1, 3, 5 } } };

        WHEN( "We lookup a range wider than that in the tree" )
        {
            auto const lower = key_t{ 0 };
            auto const upper = key_t{ 42 };
            auto const actual_result = tree.find( lower, upper );

            THEN( "The entire range is returned in sorted order" )
            {
                auto const expected_result = key_list_t{ 1, 3, 5};

                REQUIRE( actual_result == expected_result );
            }
        }
    }
}

// case 3: full traversal on a tree of height 2
// case 4: traversal only retrieves the middle half at height 2
// case 5: lower == upper on tree of height 2, contains key
// case 6: full traversal on a tree of height 3
// case 7: traversal only gets largest half of elements in tree of height 3
