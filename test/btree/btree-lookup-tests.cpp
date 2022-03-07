/**
 * Set of unit tests with which to evaluate the lookup/find function in the BTree implementation.
 */

#include "catch2/catch.hpp"
#include "a1/btree/BTree.hpp"

SCENARIO( "We perform a lookup on an empty tree", "[btree][empty][lookup][a1]")
{
    GIVEN( "An empty B-Tree and a search key" )
    {
        auto tree = BTree{};
        auto const key = key_t{ 12 };

        WHEN( "We lookup if the key is found in the tree" )
        {
            auto const actual_result = tree.find( key );

            THEN( "The result is null" )
            {
                auto const expected_result = std::nullopt;
                REQUIRE( actual_result == expected_result );
            }
        }
    }
}
