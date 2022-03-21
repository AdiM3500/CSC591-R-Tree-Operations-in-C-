/**
 * Set of unit tests with which to evaluate the lookup/find function in the BTree implementation.
 */

#include "catch2/catch.hpp"
#include "a2/rtree/RTree.hpp"

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


SCENARIO( "We perform a lookup on a tree with only one node", "[btree][root][lookup][a1]")
{
    GIVEN( "A B-Tree with a single node" )
    {
        auto const key_in_tree = 3;
        auto tree = BTree{ new Node{ { 1, key_in_tree } } };

        WHEN( "We lookup a key that is in the tree" )
        {
            auto const actual_result = tree.find( key_in_tree );

            THEN( "The root node is returned" )
            {
                auto const expected_result = tree.root;

                CHECK( actual_result != std::nullopt );

                REQUIRE( *actual_result == expected_result );
            }
        }

        WHEN( "We lookup a key that is not in the tree" )
        {
            auto const actual_result = tree.find( 42u );

            THEN( "The result is null" )
            {
                auto const expected_result = tree.root;


                REQUIRE( actual_result == std::nullopt );
            }
        }
    }
}

SCENARIO("We perform a lookup on a tree with 4 nodes (root node, left child, middle child, right child)")
{
    GIVEN("A B-Tree with 4 nodes")
    {
        auto tree = BTree{new Node{{3, 6}}};
        
        tree.root->children[0] = new Node{ {1,2} };
        tree.root->children[1] = new Node(5);
        tree.root->children[2] = new Node{ {7,9} };

        //case 4:
        WHEN("When we lookup a key that is in the left child")
        {
            auto const actual_result = tree.find(1);
            

            THEN("The left Node is returned")
            {
                auto const expected_result = tree.root->children[0];
                

               
                REQUIRE(*actual_result == expected_result);
            }

        }

        //case 5:
        WHEN("When we lookup a key that is in the middle child")
        {
            auto const actual_result = tree.find(5);

            THEN("The middle Node is returned")
            {
                
                auto const expected_result = tree.root->children[1];

                REQUIRE(*actual_result == expected_result);
            }
        }
    }
}


SCENARIO("We perform a lookup on a tree with 7 nodes (root, leftchild, rightChild, leftchild->leftchild, leftchild->rightChild, rightChild->leftChild, rightChild->rightChild")
{
    GIVEN("A Tree with 7 nodes")
    {
        auto tree = BTree{ new Node(7)};


        tree.root->children[0] = new Node(3); //leftChild
        tree.root->children[1] = new Node(11); //middlechild
        
        
        tree.root->children[0]->children[0] = new Node(1); //leftchild->leftChild
        tree.root->children[0]->children[1] = new Node(5); //leftchild->rightChild

        tree.root->children[1]->children[0] = new Node(9); //rightChild->leftchild
        tree.root->children[1]->children[1] = new Node(13); //rightChild->rightChild

        //case 6:
        WHEN("We lookup a key left then right")
        {
            auto const actual_result = tree.find(5);

                THEN("The right child of the left node is returned")
                {

                auto const expected_result = tree.root->children[0]->children[1];

                REQUIRE(*actual_result == expected_result);



                }


        }

        //case 7:
        WHEN("We lookup a key right then left")
        {

            auto const actual_result = tree.find(9);

            THEN("The left child of the right node is returned")
            {

                auto const expected_result = tree.root->children[1]->children[0];
                REQUIRE(*actual_result == expected_result);

            }
        } 

    }
}
// case 4: search for a key in a left child
// case 5: search for a key in a middle child
// case 6: search for a key left then right
// case 7: search for a key right then left
