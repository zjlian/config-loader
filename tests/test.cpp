#include "config_loader/config_loader.h"
#include "config_loader/json_parser.h"

#include <cassert>
#include <iostream>

int main()
{
    using namespace toy;
    ConfigLoader<JsonParser> config;
    // config.Load("test.json");
    config.LoadAll(".", ".json");
    std::cout << config.Get("test") << std::endl;
    std::cout << config.Get("test copy") << std::endl;
    std::cout << config.Get("test copy 2") << std::endl;
    std::cout << config.Get("test copy 3") << std::endl;
    std::cout << config.Get("test copy 4") << std::endl;
}