#include "Solution.h"
#include <iostream>
#include <algorithm>
#include <sstream>

Solution::Solution(const Solution &other)
{
    for (size_t i = 0; i < other.solution_.size(); i++)
    {
        solution_.push_back(other.solution_[i]);
    }
}

void Solution::print() const
{
    for (const auto i : solution_)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

const std::string Solution::printString() const
{
    std::string out = "";
    std::stringstream ss(out);
    for (auto i : solution_)
    {
        ss << i << " ";
    }
    return ss.str();
}

void Solution::insteadAll(std::vector<int> &other)
{
    solution_.swap(other);
}

const std::vector<int> Solution::intersect(Solution other) const
{
    std::vector<int> my(solution_), intersect;
    my.erase(my.begin());
    other.solution_.erase(other.solution_.begin());
    my.pop_back();
    other.pop_back();
    std::sort(other.solution_.begin(), other.solution_.end());
    std::sort(my.begin(), my.end());
    std::set_intersection(other.solution_.begin(), other.solution_.end(), my.begin(), my.end(), std::back_inserter(intersect));
    return intersect;
}

void Solution::exchangeWithCutValue(Solution &other, const int cut_value)
{
    std::vector<int> my_tails, other_tails;
    while (solution_[solution_.size() - 1] != cut_value)
    {
        my_tails.push_back(solution_[solution_.size() - 1]);
        solution_.pop_back();
    }
    while (other.solution_[other.solution_.size() - 1] != cut_value)
    {
        other_tails.push_back(other.solution_[other.solution_.size() - 1]);
        other.solution_.pop_back();
    }
    while (!my_tails.empty())
    {
        other.solution_.push_back(my_tails[my_tails.size() - 1]);
        my_tails.pop_back();
    }
    while (!other_tails.empty())
    {
        solution_.push_back(other_tails[other_tails.size() - 1]);
        other_tails.pop_back();
    }
}

void Solution::concatenateWith(const std::vector<int> &tails)
{
    for (const auto i : tails)
    {
        solution_.push_back(i);
    }
}

void Solution::cutTailsFrom(const int index)
{
    while (solution_.size() != index + 1)
    {
        solution_.pop_back();
    }
}

