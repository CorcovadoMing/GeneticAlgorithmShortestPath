#include <iostream>
#include "GeneticAlgorithm.h"

int main(int argc, const char * argv[])
{
    if (argc != 4) return 0;
    else
    {
        std::cout << argv[1] << std::endl;
        std::cout << "src: " << argv[2] << std::endl;
        std::cout << "dst: " << argv[3] << std::endl;
    }
    
    GeneticAlgorithm geneticAlgorithm(0.15);
    geneticAlgorithm.setGraphSize(20);
    geneticAlgorithm.buildGraphWithFile("input.txt");
    geneticAlgorithm.goal(0, 19);

    geneticAlgorithm.initial();
    do
    {
        geneticAlgorithm.selection();
        geneticAlgorithm.crossover();
        geneticAlgorithm.mutation();
    }
    while (geneticAlgorithm.notConverge());
    geneticAlgorithm.printSolution();
    //std::cout << geneticAlgorithm.getSolution() << std::endl;
    return 0;
}
