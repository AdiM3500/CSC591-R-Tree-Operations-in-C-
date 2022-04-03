#include "a2/rtree/RTree.hpp"

#include <iostream>  


int main() {

   
    RTree tree;

    tree.root = new Node{ variety_content_list_t{ pair_of_coordinates_t{ {1,2}, {2,7} }, pair_of_coordinates_t{ {5,8} , {8,10} } } };

    tree.root->children[0] = new Node{ variety_content_list_t{ coordinate_t{1,2}, coordinate_t{2,4}, coordinate_t{1,7} } };
    tree.root->children[1] = new Node{ variety_content_list_t{coordinate_t{5,9},coordinate_t{7,8},coordinate_t{8,10}} };

    tree.depthFirstTraversal(tree.root);


    std::cin.get();

}
