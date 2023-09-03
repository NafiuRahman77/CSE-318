
#include "dataset.hpp"
Dataset::Dataset()
{
    attribute = {0, 1, 2, 3, 4, 5};
    attribute_name = {"buying", "maint", "doors", "persons", "lug_boot", "safety"};
    for (std::size_t i = 0; i < attribute.size(); ++i)
    {
        attribute_name_mapper[attribute_name[i]] = attribute[i];
    }
    verdict = {0, 1, 2, 3};
    verdict_name = {"unacc", "acc", "good", "vgood"};
    for (std::size_t i = 0; i < verdict.size(); ++i)
    {
        verdict_name_mapper[verdict_name[i]] = verdict[i];
    }

    std::vector<std::string> buying={"vhigh", "high", "med", "low"};
    std::vector<std::string> maint={"vhigh", "high", "med", "low"};
    std::vector<std::string> doors={"2", "3", "4", "5more"};
    std::vector<std::string> persons={"2", "4", "more"};
    std::vector<std::string> lug_boot={"small", "med", "big"};
    std::vector<std::string> safety={"low", "med", "high"};

    attribute_value_names.push_back(buying); attribute_value_names.push_back(maint); attribute_value_names.push_back(doors);
    attribute_value_names.push_back(persons);attribute_value_names.push_back(lug_boot);attribute_value_names.push_back(safety);

    auto createMap = [](const std::vector<std::string>& values) -> std::unordered_map<std::string, int> {
        std::unordered_map<std::string, int> map;
        for (int i = 0; i < values.size(); ++i) {
            map[values[i]] = i;
        }
        return map;
    };

    // Insert maps into attribute_value_mapper
    attribute_value_mapper.push_back(createMap(buying));
    attribute_value_mapper.push_back(createMap(maint));
    attribute_value_mapper.push_back(createMap(doors));
    attribute_value_mapper.push_back(createMap(persons));
    attribute_value_mapper.push_back(createMap(lug_boot));
    attribute_value_mapper.push_back(createMap(safety));

}