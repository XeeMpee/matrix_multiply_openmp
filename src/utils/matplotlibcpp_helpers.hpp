#pragma once
#include <string>

namespace plthelpers {

template <typename T>
std::vector<std::string> ylabels(std::vector<T> data)
{
    std::vector<std::string> labels = {};
    for (auto& e : data)
    {
        labels.push_back(std::to_string(e));
    }
    return labels;
}

template <typename T>
std::vector<int> indxs(std::vector<T> data)
{
    std::vector<int> indxs = {};
    for (int i = 0; i < data.size(); i++)
    {
        indxs.push_back(i);
    }
    return indxs;
}


} // namespace plthelpers