#include "GeneticAlgorithm.h"
#include "Solution.h"
#include "RandomRange.h"
#include <vector>
#include <algorithm>
#include <fstream>

void findPath(const int src, const int des, const Graph &graph, std::vector<int> &path, const int active_barrier = 0, const int barrier = 0)
{

    std::vector<int> isVisited(graph.size(), 0);
    int visiting = src;
    bool stuck = false;
    active_barrier ? isVisited[barrier] = 1 : isVisited[barrier];

    do
    {
        stuck = false;
        while (visiting != des)
        {
            path.push_back(visiting);
            isVisited[visiting] = 1;
            const std::vector<int> neighbors = graph.neighbors(visiting, isVisited);
            if (neighbors.empty())
            {
                stuck = true;
                isVisited = std::vector<int>(graph.size(), 0);
                path.clear();
                visiting = src;
                active_barrier ? isVisited[barrier] = 1 : isVisited[barrier];
                break;
            }
            do
            {
                const int i = RandomRange::random<int>(0, static_cast<int>(neighbors.size()) - 1);
                visiting = neighbors[i];
            }
            while (isVisited[visiting]);
        }
    }
    while (stuck);
    path.push_back(des);
}

//-----------------------------------------------------

GeneticAlgorithm::GeneticAlgorithm(const double mutation_rate) : mutation_rate_(mutation_rate)
{
}

void GeneticAlgorithm::goal(const int src, const int des)
{
    src_ = src;
    des_ = des;
}

void GeneticAlgorithm::printSolution() const
{
    //best_solution_.print();
    std::cout << best_fitness_ << std::endl;
}

const std::string GeneticAlgorithm::getSolution() const
{
    return best_solution_.printString();

}

void GeneticAlgorithm::setGraphSize(const int size)
{
    graph_.size(size);
    population_ = size;
}

void GeneticAlgorithm::buildGraphWithFile(const std::string &filename)
{
    std::ifstream file(filename.c_str());
    if (!file) exit(1);
    int from, to, weight;
    while (!file.eof())
    {
        file >> from >> to >> weight;
        buildGraph(from, to, weight);
    }
    file.close();
}

void GeneticAlgorithm::initial()
{
    still_ = converge_;
    best_fitness_ = INT_MAX;
    last_best_fitness_ = INT_MAX;

    solutions_ = std::vector<Solution>(population_, Solution());
    fitness_ = std::vector<int>(solutions_.size(), 0);
    for (size_t i = 0; i < solutions_.size(); i += 1)
    {
        std::vector<int> path;
        findPath(src_, des_, graph_, path);
        solutions_[i].insteadAll(path);
        fitness_[i] = fitnessFunction_(solutions_[i]);
    }
}

void GeneticAlgorithm::selection()
{
    selected_.clear();
    const size_t tournament_size_ = 2;
    for (size_t i = 0; i < solutions_.size(); i += tournament_size_)
    {
        fitness_[i] < fitness_[i + 1] ? selected_.push_back((int)i) : selected_.push_back((int)i + 1);
    }
    if (selected_.size() % 2) selected_.pop_back();
}


void GeneticAlgorithm::crossover()
{
    std::random_shuffle(selected_.begin(), selected_.end());
    for (int i = 0; i < selected_.size(); i += 2)
    {
        std::vector<int> intersection = solutions_[selected_[i]].intersect(solutions_[selected_[i + 1]]);
        if (intersection.empty())
        {
            continue;
        }
        const int cut_value = intersection[RandomRange::random<int>(0, static_cast<int>(intersection.size()) - 1)];
        Solution first_child(solutions_[selected_[i]]), second_child(solutions_[selected_[i + 1]]);
        first_child.exchangeWithCutValue(second_child, cut_value);
        fitnessFunction_(first_child) < fitnessFunction_(solutions_[selected_[i]]) ? solutions_[selected_[i]] = first_child : solutions_[selected_[i]];
        fitnessFunction_(second_child) < fitnessFunction_(solutions_[selected_[i + 1]]) ? solutions_[selected_[i + 1]] = second_child : solutions_[selected_[i + 1]];
    }
}

void GeneticAlgorithm::mutation()
{
    for (size_t i = 0; i < population_; i += 1)
    {
        if (solutions_[i].size() > 3 && RandomRange::random<double>(0, 1) < mutation_rate_)
        {
            const int mutation_point = RandomRange::random<int>(1, (int)solutions_[i].size() - 3);
            const int barrier = solutions_[i].gene(mutation_point + 1);
            solutions_[i].cutTailsFrom(mutation_point);
            std::vector<int> new_tails;
            findPath(solutions_[i].gene(mutation_point), des_, graph_, new_tails, 1, barrier);
            solutions_[i].concatenateWith(new_tails);
        }
    }
}

void GeneticAlgorithm::evaluate_()
{
    for (size_t i = 0; i < solutions_.size(); i += 1)
    {
        const int fitness__ = fitnessFunction_(solutions_[i]);
        if (best_fitness_ > fitness__)
        {
            best_fitness_ = fitness__;
            best_solution_ = Solution(solutions_[i]);
        }
        fitness_[i] = fitness__;
    }
}

const int GeneticAlgorithm::fitnessFunction_(const Solution &solution) const
{
    int fitness = 0;
    for (size_t i = 0; i < solution.size() - 1; i += 1)
    {
        fitness += graph_.weight(solution.gene(i), solution.gene(i + 1));
        fitness += graph_.weight(solution.gene(i));
    }
    fitness += graph_.weight(solution.gene(solution.size() - 1));
    return fitness;
}

const bool GeneticAlgorithm::notConverge()
{
    evaluate_();
    if (best_fitness_ == last_best_fitness_)
    {
        if (still_ == 0) return false;
        else still_--;
        return true;
    }
    else
    {
        still_ = converge_;
        last_best_fitness_ = best_fitness_;
        return true;
    }
}
