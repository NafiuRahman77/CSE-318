#include <iostream>
#include <climits>
#include <math.h>
#include "decision_tree.hpp"

DecisionTree::DecisionTree()
{
    
}

std::vector<std::vector<Car>> DecisionTree::split_by_attr(std::vector<Car> carlist, int attr)
{

    std::vector<std::vector<Car>> split(d.attribute_value_names[attr].size());

    for (int i = 0; i < carlist.size(); i++)
    {
        split[carlist[i].own_attribute_values[attr]].push_back(carlist[i]);
    }

    return split;
}

double DecisionTree::entropy(std::vector<Car> carlist)
{

    std::unordered_map<int, int> verdict_counts;
    for (const Car &car : carlist)
    {
        verdict_counts[car.verdict]++;
    }

    double entropy = 0.0;
    int total_samples = carlist.size();

    for (const auto &pair : verdict_counts)
    {
        double probability = static_cast<double>(pair.second) / total_samples;
        entropy -= probability * log2(probability);
    }

    return entropy;
}

double DecisionTree::gain(std::vector<Car> carlist, int attr)
{
    std::vector<std::vector<Car>> split = split_by_attr(carlist, attr);
    double curr_entropy = entropy(carlist);
    int S = 0;

    for (const auto &row : split)
    {
        S += row.size();
    }
    for (int i = 0; i < d.attribute_value_names[attr].size(); i++)
    {
        curr_entropy -= ((double)(split[i].size()) / (double)(S)) * ((double)entropy(split[i]));
    }
    return curr_entropy;
}

void DecisionTree::learn(std::vector<Car> examples, std::vector<bool> attribute, std::vector<Car> parent_examples)
{
    DecisionTree dt;
    if (examples.size() == 0)
    {

        isLeaf = true;
        verdict = plurality(parent_examples);
    }
    else if (all_same(examples))
    {
        isLeaf = true;
        verdict = plurality(examples);
    }
    else if (attribute_empty(attribute))
    {
        isLeaf = true;
        verdict = plurality(examples);
    }
    else if (examples.size() == parent_examples.size())
    {
        isLeaf = true;
        verdict = plurality(parent_examples);
    }
    else
    {
        current_attribute = best_attr(attribute, examples);
        std::vector<std::vector<Car>> splitted = split_by_attr(examples, current_attribute);
        attribute[current_attribute] = false;
        for (int i = 0; i < d.attribute_value_names[current_attribute].size(); i++)
        {
            DecisionTree child;
            child.learn(splitted[i], attribute, examples);
            children.push_back(child);
        }
    }
}

int DecisionTree::infer(Car newcar)
{
    if (isLeaf)
    {
        return this->verdict;
    }
    return children[newcar.own_attribute_values[current_attribute]].infer(newcar);
}

int DecisionTree::best_attr(std::vector<bool> attribute, std::vector<Car> carlist)
{
    double mx = INT_MIN;
    int index = 0;
    for (int i = 0; i < attribute.size(); i++)
    {
        if (attribute[i] == true)
        {
            double g = gain(carlist, i);
            if (g > mx)
            {
                mx = g;
                index = i;
            }
        }
    }
    return index;
}

bool DecisionTree::attribute_empty(std::vector<bool> attribute)
{
    int flag = 0;
    for (int i = 0; i < attribute.size(); i++)
    {
        if (attribute[i])
            flag = 1;
    }
    if (flag)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool DecisionTree::all_same(std::vector<Car> carlist)
{
    int verd = carlist[0].verdict;
    int flag = 0;

    for (int i = 1; i < carlist.size(); ++i)
    {
        if (carlist[i].verdict != verd)
        {
            flag = 1;
        }
    }

    if (flag)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int DecisionTree::plurality(std::vector<Car> carlist)
{
    std::unordered_map<int, int> verdictCount; // Map to store counts of each number

    for (int i = 0; i < carlist.size(); i++)
    {
        verdictCount[carlist[i].verdict]++;
    }

    int mostCommonVerdict = carlist[0].verdict;      // Initialize with the first verdict
    int maxCount = verdictCount[carlist[0].verdict]; // Initialize with the count of the first verdict

    for (const auto &entry : verdictCount)
    {
        if (entry.second > maxCount)
        {
            mostCommonVerdict = entry.first;
            maxCount = entry.second;
        }
    }

    return mostCommonVerdict;
}
