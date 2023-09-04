#pragma once
#include <vector>
#include "dataset.hpp"
#include "car.hpp"
class DecisionTree
{
public:
    Dataset d;
    int current_attribute;
    int verdict;
    bool isLeaf=false;
   // std::vector<bool> attribute_used;
    std::vector<DecisionTree> children;

    DecisionTree();
    std::vector<std::vector<Car>> split_by_attr(std::vector<Car> carlist, int attr);
    double entropy(std::vector<Car> carlist);
    double gain(std::vector<Car> carlist, int attr);
    void learn(std::vector<Car> examples, std::vector<bool> attribute, std::vector<Car> parent_examples);
    int infer(Car newcar);
    int best_attr(std::vector<bool> attribute, std::vector<Car> carlist);
    int plurality(std::vector<Car> carlist);
    bool attribute_empty(std::vector<bool> attribute);
    bool all_same(std::vector<Car> carlist);
};