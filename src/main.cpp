#include "a2/rtree/RTree.hpp"

#include <iostream>  

int main() {

	RTree theTree;

	DataNode datas{ {{1,2 }, {3, 5 }, {4, 3} } };

	for (int i = 0; i < datas.array_size; i++) {


		std::cout << datas.dpoints[i].first << std::endl;
		std ::cout << datas.dpoints[i].second << std::endl;

	} 

	std::cout << "data point size: " << datas.array_size <<std::endl;
	

	theTree.root = new Node( &datas );
	
	//For displaying purposes only

	std::cout <<"min x: "<<theTree.root->mbr[0].first.first << std::endl;
	std::cout <<"min y: "<<theTree.root->mbr[0].first.second << std::endl;
	
	std::cout <<"max x: "<<theTree.root->mbr[0].second.first << std::endl;
	std::cout <<"max y: "<<theTree.root->mbr[0].second.second <<std::endl;

	std::cout << "-------------------------------------------------------" << std::endl <<std::endl;
	std::cout << "The current MBR points to the datapoints: " << std::endl;

//	std::cout << "the datas pointer: " << &datas << std::endl;
	for (int i = 0; i < theTree.root->dataPtr[0]->array_size; i++) {

		std::cout << "(" << theTree.root->dataPtr[0]->dpoints[i].first << "," << theTree.root->dataPtr[0]->dpoints[i].second <<")";
		


	}
	
	


	std::cin.get();
}
