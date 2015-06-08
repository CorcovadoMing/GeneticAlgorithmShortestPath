#pragma once

#include <vector>
#include <iostream>
#include <climits>
#include "Solution.h"
#include "Graph.h"

class GeneticAlgorithm
{
public:
    GeneticAlgorithm(const double);
    void goal(const int, const int);
    const int maxNode() const { return graph_.size() - 1; }
    void printSolution() const;
    const std::string getSolution() const;
    void setGraphSize(const int size);
    void buildGraphWithFile(const std::string &filename);
    void buildGraph(const int from, const int to, const int weight) { graph_.build(from, to, weight); }
    void initial();
    void selection();
    void crossover();
    void mutation();
    const bool notConverge();

private:
    void evaluate_();
    const int fitnessFunction_(const Solution &) const;
    int population_, src_, des_, best_fitness_ = INT_MAX, last_best_fitness_ = INT_MAX;
    const int converge_ = 40;
    int still_ = converge_;
    Solution best_solution_;
    double mutation_rate_;
    std::vector<Solution> solutions_;
    std::vector<int> fitness_, selected_;
    Graph graph_;
};
