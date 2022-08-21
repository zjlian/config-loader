#pragma once

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

#include "nlohmann/json.hpp"

namespace toy
{
    /// 解析 json 文件的解析器
    class JsonParser
    {
    public:
        using ValueType = nlohmann::json;

        ValueType operator()(const std::string &filename)
        {
            std::ifstream in{filename};
            if (!in.is_open())
            {
                std::cerr << "文件打开失败: " << filename << std::endl;
                return {};
            }

            return nlohmann::json::parse(in);
        }
    };

} // namespace toy