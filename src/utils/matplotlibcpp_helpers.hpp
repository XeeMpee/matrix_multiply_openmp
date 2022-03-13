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

} // namespace plthelpers