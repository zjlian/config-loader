# 配置文件加载库
功能如题，就是用来读取配置文件的。

## 用法
### 读取单个 JSON 文件
目前 config-loader 只实现了对 json 文件的读取，解析 json 文件用的是开源库 [nlohmann/json](https://github.com/nlohmann/json)。   
`toy::ConfigLoader` 是一个通用的配置文件加载和存储类模板，他具体能加载什么配置文件和如何存储是由第一个模板参数传入的解析器决定的，这里的 `toy::JsonParser` 实现了对 json 文件的解析。   

```c++
#include "config_loader/config_loader.h"
#include "config_loader/json_parser.h"

// 创建一个使用 toy::JsonParser 作为解析器的配置文件加载器实例
toy::ConfigLoader<toy::JsonParser> config;
// 读取同级目录下的文件 test.json
config.Load("test.json");
// 通过文件名获取解析后的数据，Get() 返回值的类型由解析器决定
auto data = config.Get("test");
```

### 读取目录下的全部 JSON 文件
```c++
#include "config_loader/config_loader.h"
#include "config_loader/json_parser.h"

// 创建一个使用 toy::JsonParser 作为解析器的配置文件加载器实例
toy::ConfigLoader<toy::JsonParser> config;
// 读取同级目录下的文件所有配置文件，第二个参数指定配置文件的后缀名
config.LoadAll(".", ".json");
// 通过文件名获取解析后的数据，Get() 返回值的类型由解析器决定
auto data1 = config.Get("test");
auto data2 = config.Get("test2");
```

### 自定义配置文件解析器
想要拓展自定义的配置文件解析器也十分简单，只需要实现拥有如下成员的类就可以了。   
```c++
class AnyParser
{
    using ValueType = YourConfigType;
    YourConfigType operator()(const std::string &filename);
}
```
