#pragma once
#include <vector>

class Graph
{
public:
    void size(const int);
    void build(const int, const int, const int);
    void build(const int, const int);
    const std::vector<int> neighbors(const int, const std::vector<int> &) const;
    const int weight(const int, const int) const;
    const int weight(const int) const;
    const int size() const
    {
        return size_;
    }
private:
    int size_;
    std::vector< std::vector<int> > graph_;

};