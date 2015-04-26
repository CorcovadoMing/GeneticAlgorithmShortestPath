#include <iostream>
#include "GeneticAlgorithm.h"

int main(int argc, const char * argv[]) {
	GeneticAlgorithm geneticAlgorithm(0.15);
	geneticAlgorithm.setGraphSize(20);
	geneticAlgorithm.buildGraphWithFile("input.txt");
	geneticAlgorithm.goal(0, 19);
	
	geneticAlgorithm.initial();
	do {
		geneticAlgorithm.selection();
		geneticAlgorithm.crossover();
		geneticAlgorithm.mutation();
	} while (geneticAlgorithm.notConverge());
	geneticAlgorithm.printSolution();
	//std::cout << geneticAlgorithm.getSolution() << std::endl;
	return 0;
}
