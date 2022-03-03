/**
 * Set of unit tests with which to evaluate the public-facing methods in the BTree implementation.
 */

#include "catch2/catch.hpp"
#include "a1/btree/BTree.hpp"

SCENARIO( "We need to know if a B-Tree node is a leaf node", "[btree][leaf]")
{
    GIVEN( "A B-Tree containing a single key" )
    {
        auto const key_val = 3u;
        BTree tree{ new Node( key_val ) };

        WHEN( "We check if the root is a leaf" )
        {
            THEN( "The check_leaf() function returns true" )
            {
              CHECK( tree.root != NULL );
              REQUIRE( tree.root->check_leaf() );
            }
        }
    }
}


SCENARIO( "We compare two B-Tree objects", "[btree][equal][comparator]")
{
    GIVEN( "An empty B-Tree" )
    {
        BTree tree;

        WHEN( "We create another empty B-Tree" )
        {
            BTree tree2;

            THEN( "The two trees are considered to be equal" )
            {
                REQUIRE( tree == tree2 );
            }
        }
        WHEN( "We create a non-empty B-Tree" )
        {
            auto const key_val = 3u;
            BTree tree2{ new Node( key_val ) };

            THEN( "The two trees are *not* considered to be equal" )
            {
                REQUIRE( ! ( tree == tree2 ) );
            }
        }
    }

    GIVEN( "A B-Tree with a single key" )
    {
        auto const key_val = 3u;
        BTree tree{ new Node( key_val ) };

        WHEN( "We create a copy of the B-Tree" )
        {
            BTree copy( tree );

            THEN( "The original tree and the copy and considered to be equal" )
            {
                REQUIRE( tree == copy );
            }
        }
    }
}


SCENARIO( "We add new keys to the B-Tree", "[btree][insert]")
{
    GIVEN( "An empty B-Tree" )
    {
        auto const key_val = 3;
        BTree tree;

        WHEN( "We insert a single key" )
        {
            tree.AddKey( key_val );

            THEN( "The tree contains a single node with a single key" )
            {
                BTree const expected_solution{ new Node( key_val ) };

                CHECK( tree.root != NULL );
                REQUIRE( tree == expected_solution );
            }
        }
    }
    
    GIVEN( "A B-Tree with a single key" )
    {
        auto const original_key = 3;
        BTree tree{ new Node( original_key ) };

        WHEN( "We insert a single key that is larger than original key" )
        {
            auto const new_key = original_key + 2;
            tree.AddKey( new_key );

            THEN( "The tree contains a single node with the original_key before the new_key" )
            {
                // [original_key, new_key, ?]
                BTree const expected_solution{ new Node( original_key ) };
                CHECK( tree.root != NULL );
                expected_solution.root->keys[ 1 ] = new_key;

                REQUIRE( tree == expected_solution );
            }
        }

        WHEN( "We insert a single key that is less than original key" )
        {
            auto const new_key = original_key - 2;
            tree.AddKey( new_key );

            THEN( "The tree contains a single node with the original_key before the new_key" )
            {
                // [new_key, original_key, ?]
                BTree const expected_solution{ new Node( new_key ) };
                CHECK( tree.root != NULL );
                expected_solution.root->keys[ 1 ] = original_key;

                REQUIRE( tree == expected_solution );
            }
        }

        WHEN( "We insert a single key that is the same as the original key" )
        {
            tree.AddKey( original_key );

            THEN( "The tree contains a single node with the original_key before the new_key" )
            {
                // [original_key, original_key, ?]
                BTree const expected_solution{ new Node( original_key ) };
                CHECK( tree.root != NULL );
                expected_solution.root->keys[ 1 ] = original_key;

                REQUIRE( tree == expected_solution );
            }
        }
    }

        
    GIVEN( "A B-Tree containing 2 keys (at the root node)" )
    {   
        auto const original_key_1 = 3;
        auto const original_key_2 = 5;
        BTree tree{ new Node( original_key_1 )};

        tree.AddKey(original_key_2);
        

        WHEN( "We insert a single key that is larger than the 2nd key" )
        {
            auto const new_key = original_key_2 + 2;
            tree.AddKey( new_key );

/*

                        [key 1 key 2] -> root

                                                            [key 1 key 3 key 2]
                             [key 2]

                        /               \
                    [key 1]         [key 3]

*/
            THEN( "The current node gets split and the middle element of the node becomes the new root with its children becoming 1st key and 3rd key respectively" )
            {
               
               
                BTree const expected_solution{ new Node( original_key_2 ) };
                CHECK( tree.root != NULL );
                expected_solution.root->keys[0] = original_key_2;
                expected_solution.root->children[0] = new Node(original_key_1);
                expected_solution.root->children[1] = new Node(new_key);

                REQUIRE( tree == expected_solution );
            }
        }
    }

//A full right child, but capacity exists in the root and the left child
    GIVEN( "A B-Tree containing 4 keys, we add a 5th key")
    {   
        auto const original_key_1 = 3;
        auto const original_key_2 = 5;
        auto const original_key_3 = 7;
        auto const original_key_4 = 9;


        BTree tree{ new Node( original_key_1 )};

        tree.AddKey(original_key_2);
        tree.AddKey(original_key_3);
        tree.AddKey(original_key_4);




        WHEN( "We insert a single key that is larger than the 4th key" )
        {
            auto const new_key = original_key_4 + 2;
            tree.AddKey( new_key );

            THEN( "The current leaf node size from 2 to 3")
            {
               
               
                BTree const expected_solution{ new Node( original_key_2 ) };
                CHECK( tree.root != NULL );
                expected_solution.root->keys[0] = original_key_2;
                expected_solution.root->children[0] = new Node(original_key_1);
                expected_solution.root->children[0]->keys[1] = key_9;

                expected_solution.root->children[1] = new Node(new_key);

                REQUIRE(  ==  );
            }
        }
    }
} 


