#include "a2/rtree/RTree.hpp"

#include <iostream>  


int main() {

   
   // RTree tree;

    //tree.root = new Node{ variety_content_list_t{ pair_of_coordinates_t{ {1,2}, {2,7} }, pair_of_coordinates_t{ {5,8} , {8,10} } } };
    
    //tree.root->children[0] = new Node{ variety_content_list_t{ coordinate_t{1,2}, coordinate_t{2,4}, coordinate_t{1,7} } };
   // tree.root->children[1] = new Node{ variety_content_list_t{coordinate_t{5,9},coordinate_t{7,8},coordinate_t{8,10}} };

    //tree.depthFirstTraversal(tree.root);

    //tree.IncNearest({ 1,2 }, tree);

    RTree tree;

    std::vector<coordinate_t> v;

    tree.root = new Node{ variety_content_list_t{pair_of_coordinates_t{ {3,2}, {5,3} }, pair_of_coordinates_t{ {2,7},{5,9} } } };

    tree.root->children[0] = new Node{ variety_content_list_t{coordinate_t{3,2}, coordinate_t{5,3} } };
    tree.root->children[1] = new Node{ variety_content_list_t{coordinate_t{2,7}, coordinate_t{5,9} } };
  // double distance = tree.calc_distance(coordinate_t{ 2,4 }, std::get<pair_of_coordinates_t>(tree.root->contents[0]));

  // std::cout << distance<<std::endl;

   v =  tree.IncNearest({ 2,4 }, tree, 4);

   for (int i = 0; i < v.size(); i++) {

       std::cout << "neares neighbor number " << i << " is : " << v[i].first <<
           "," << v[i].second<<std::endl;
   }

    std::cin.get();

}