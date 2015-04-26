#pragma once
#include <vector>
#include <iostream>

class Solution
{
public:
    Solution() {}
    Solution(const Solution &);
    void print() const;
    const std::string printString() const;
    const size_t size() const
    {
        return solution_.size();
    }
    const int gene(const std::size_t index) const
    {
        return solution_[index];
    }
    void push_back(const int data)
    {
        solution_.push_back(data);
    }
    void pop_back()
    {
        solution_.pop_back();
    }
    void insteadAll(std::vector<int> &);
    const std::vector<int> intersect(Solution) const;
    void exchangeWithCutValue(Solution &, const int);
    void concatenateWith(const std::vector<int> &);
    void cutTailsFrom(const int index);

private:
    std::vector<int> solution_;
};