#pragma once

#include <cassert>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <string_view>

namespace toy
{

    template <typename Parser>
    class ConfigLoader
    {
    public:
        using ValueType = typename Parser::ValueType;

        /// 加载指定文件
        void Load(const std::string &filename)
        {
            namespace fs = std::filesystem;

            fs::path path{filename};
            if (!fs::exists(path))
            {
                std::cerr << "配置文件不存在: " << filename << std::endl;
                abort();
            }

            // 解析配置文件后存入
            config_[path.stem().string()] = parser_(filename);
        }

        /// 加载指定目录下的全部配置文件
        /// @param directory 搜索的目标目录
        /// @param extension 配置文件的拓展名称
        void LoadAll(const std::string &directory, const std::string &extension)
        {
            namespace fs = std::filesystem;

            fs::path path{directory};
            if (!fs::is_directory(path))
            {
                std::cerr << "参数提供的不是一个有效的目录: " << directory
                          << std::endl;
            }

            for (const auto &p : fs::directory_iterator(path))
            {
                if (!p.is_directory() && p.path().extension() == extension)
                {
                    Load(p.path());
                }
            }
        }

        /// 获取指定的配置文件，返回值是对应的配置文件解析器解析后的实例对象
        const ValueType &Get(const std::string &config_name)
        {
            auto iterator = config_.find(config_name);
            if (iterator == config_.end())
            {
                std::cerr << "配置文件不存在: " << config_name << std::endl;
                abort();
            }
            return config_[config_name];
        }

    private:
        Parser parser_{};
        std::map<std::string, ValueType> config_{};
    };

} // namespace toy