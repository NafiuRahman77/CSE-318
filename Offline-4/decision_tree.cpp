#include <iostream>
#include <climits>
#include <math.h>
#include "decision_tree.hpp"

DecisionTree::DecisionTree()
{
    isLeaf = false;
    current_attribute = INT_MAX;
    verdict = INT_MAX;
    // std::vector<bool> attribute_used(6, true);
}

std::vector<std::vector<Car>> DecisionTree::split_by_attr(std::vector<Car> carlist, int attr)
{
    // std::cout << "split debug" << std::endl;
    std::vector<std::vector<Car>> split(d.attribute_value_names[attr].size());

    for (int i = 0; i < carlist.size(); i++)
    {
        // std::cout << carlist[i].own_attribute_values[attr]<< " ";
        split[carlist[i].own_attribute_values[attr]].push_back(carlist[i]);
    }
    // for (int i = 0; i < split.size(); i++)
    // {
    //     for (int j = 0; j < split[i].size(); j++)
    //     {
    //         //std::cout << split[i][j].verdict_string << " ";
    //     }
    //     //std::cout << std::endl;
    // }
    return split;
}

double DecisionTree::entropy(std::vector<Car> carlist)
{
    std::vector<int> temp(d.verdict.size(), 0);
    for (int i = 0; i < carlist.size(); i++)
    {
        int j = carlist[i].verdict;
        temp[j]++;
    }

    double ans = 0;
    for (int i = 0; i < d.verdict.size(); i++)
    {
        if (temp[i] > 0)
        {
            double f = (double)temp[i] / (double)carlist.size();
            f *= log(1.0 / (double)f) / log(2.0);
            ans += f;
        }
    }
    return ans;
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
        // std::cout <<"debug" << std::endl;
        isLeaf = true;
        verdict = plurality(examples);
    }
    else if (attribute_empty(attribute))
    {
        isLeaf = true;
        verdict = plurality(examples);
    }
    else if(examples.size()==parent_examples.size()){
        isLeaf=true;
        verdict=plurality(parent_examples);
    }
    else
    {
        current_attribute = best_attr(attribute, examples);
        // std::cout << current_attribute << "debug" << std::endl;
        std::vector<std::vector<Car>> splitted = split_by_attr(examples, current_attribute);
        attribute[current_attribute] = false;
        for (int i = 0; i < d.attribute_value_names[current_attribute].size(); i++)
        {
            DecisionTree child;
            child.learn(splitted[i], attribute, examples);
            children.push_back(child);
        }
        attribute[current_attribute] = true;
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
        // std::cout<<"bip"<<std::endl;
        if (attribute[i] == true)
        {
            double g = gain(carlist, i);
            // std::cout<<"g "<<g<<std::endl;
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
    for (int i = 0; i < attribute.size(); i++)
    {
        if (attribute[i])
            return false;
    }
    return true;
}

bool DecisionTree::all_same(std::vector<Car> carlist)
{
    int verd = carlist[0].verdict;

    for (int i = 1; i < carlist.size(); ++i)
    {
        if (carlist[i].verdict != verd)
        {
            return false;
        }
    }

    return true;
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
