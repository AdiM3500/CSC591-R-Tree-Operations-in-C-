#include "a2/rtree/RTree.hpp"

#include <iostream>  


int main() {

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

    tree.inOrderTraversal(tree.root);

    //case 3:
}
