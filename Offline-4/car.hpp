#pragma once
#include <vector>
#include <string>
#include "dataset.hpp"
class Car
{
public:
    Dataset d;
    static const int attribute_count=6;
    std::vector<int> own_attribute_values;
    int verdict;
    std::vector<std::string>attribute_values_string;
    std::string verdict_string;

    Car();
    void map_to_int();
};
