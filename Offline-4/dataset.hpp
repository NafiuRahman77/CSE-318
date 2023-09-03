#pragma once
#include <vector>
#include <string>
#include <unordered_map>

class Dataset
{
public:
    std::vector<int> attribute;
    std::vector<std::string> attribute_name;
    std::unordered_map<std::string, int> attribute_name_mapper;
    std::vector<int> verdict;
    std::vector<std::string> verdict_name;
    std::unordered_map<std::string, int> verdict_name_mapper;
    std::vector<std::vector<std::string>> attribute_value_names;
    std::vector<std::unordered_map<std::string, int>> attribute_value_mapper;

    Dataset();
};