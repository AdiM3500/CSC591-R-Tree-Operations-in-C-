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




/*
The insertion test cases start below:
*/




SCENARIO( "We add new keys to the B-Tree", "[btree][insert]")
{

    //case 1:
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
    
    //case 2:
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

        //case 3:
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

        //case 4:
    GIVEN("A B-tree of height 2 with a non-full leaf node ")
    {
        
        auto tree = BTree{ new Node(3) };

        tree.root->children[0] = new Node(1);        //non-full leaf node
        tree.root->children[1] = new Node{ {5,7} };


        WHEN("We insert into a non-root, non-full leaf node ")
        {
            auto const new_key = 2;
            tree.AddKey(new_key);     //going into non-full leaf node tree.root->children[0]

            THEN("The non-full leaf node now contains the new inserted key")
            {
                BTree const expected_solution{ new Node(3) };
                expected_solution.root->children[0] = new Node{ {1, new_key} };
                expected_solution.root->children[1] = new Node{ {5,7} };

                REQUIRE(tree == expected_solution);
            }
            
        }
    }

    //case 5:
    GIVEN("A B-tree of height 2 with a full leaf node ")
    {

        auto tree = BTree{ new Node(3) };

        tree.root->children[0] = new Node(1);
        tree.root->children[1] = new Node{ {5,7} }; //full leaf node


        WHEN("We insert into a non-root, full leaf node ")
        {
            auto const new_key = 6;
            tree.AddKey(new_key);     //going into full leaf node tree.root->children[1] which will cause a split of the node and the middle element will be proprogated up to the root

            THEN("The node gets split into 2 nodes and the median element of the overloaded node is propogated up to the root")
            {
                BTree const expected_solution{ new Node { {3, new_key} } };
                expected_solution.root->children[0] = new Node(1);
                expected_solution.root->children[1] = new Node (5);
                expected_solution.root->children[2] = new Node (7);


                REQUIRE(tree == expected_solution);
            }

        }
    }


    //case 6: Passes only under the condition that the full leaf node into which the new_key is inserted into is the rightchild, therefore, does not pass this test completely
    GIVEN("A B-tree of height 2 with a full leaf node and a full root node ")
    {

        auto tree = BTree{ new Node { { 3, 7} } };  //full root node

        tree.root->children[0] = new Node(1);
        tree.root->children[1] = new Node(5) ; 
        tree.root->children[2] = new Node{ {9,11} };  //full leaf node


        WHEN("We insert into a full leaf node ")
        {
            auto const new_key = 13;
            tree.AddKey(new_key);     

            THEN("The leaf node gets split, the median element gets propogated above which results in a root split above")
            {
                BTree const expected_solution{ new Node(7) };
                expected_solution.root->children[0] = new Node(3);
                expected_solution.root->children[1] = new Node(11);
                
                expected_solution.root->children[0]->children[0] = new Node(1);
                expected_solution.root->children[0]->children[1] = new Node(5);
                
                expected_solution.root->children[1]->children[0] = new Node(9);
                expected_solution.root->children[1]->children[1] = new Node(new_key);


                REQUIRE(tree == expected_solution);
            }

        }
    }

    //case 7: FAILS 
    GIVEN("A B-tree of height 3")
    {

        auto tree = BTree{ new Node (7)};  

        tree.root->children[0] = new Node{{1,3}};
        tree.root->children[1] = new Node(11);

        tree.root->children[0]->children[0] = new Node(0);
        tree.root->children[0]->children[1] = new Node(2);
        tree.root->children[0]->children[2] = new Node{{4,5}};  //we will insert into this leaf node
        
        tree.root->children[1]->children[0] = new Node(9);
        tree.root->children[1]->children[1] = new Node(13);
        
      


        WHEN("We insert into a full leaf node ")
        {
            auto const new_key = 6;
            tree.AddKey(new_key); 

            THEN("The insertion is propogate up two levels in the tree")
            {
                BTree const expected_solution{ new Node{{3,7}} };
                expected_solution.root->children[0] = new Node(1);
                expected_solution.root->children[1] = new Node(5);
                expected_solution.root->children[2] = new Node(11);
                

                expected_solution.root->children[0]->children[0] = new Node(0);
                expected_solution.root->children[0]->children[1] = new Node(2);

                expected_solution.root->children[1]->children[0] = new Node(4);
                expected_solution.root->children[1]->children[1] = new Node(new_key);
                
                expected_solution.root->children[2]->children[0] = new Node(9);
                expected_solution.root->children[2]->children[1] = new Node(13);


                  REQUIRE(tree == expected_solution);
            }

        }
    }
} 


// Case 1: Insertion into empty tree
// Case 2: Insertion into tree with one non-full node
// Case 3: Insertion into tree with one full node
// Case 4: Insertion into non-root non-full leaf node
// Case 5: Insertion into non-root full leaf node
// Case 6: Insertion causes root split above
// Case 7: Insertion propagates up two levels, raising tree from height 2 to height 3
