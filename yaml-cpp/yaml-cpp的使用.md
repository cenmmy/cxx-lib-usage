# yaml-cpp库的使用

### 1. Node

`Node`是`yaml-cpp`中重要的概念，它用于存储解析后的`yaml`信息

生成`Node`的形式有很多种，常用的形式是通过`LoadFile`读取配置文件返回一个`Node`对象。这个节点对象也成为根节点，相当于html文件中的<html>标签。

```c++
#include <yaml-cpp/yaml.h>

int main() {
    YAML::Node node = YAML::LoadFile("./config.yaml");
}
```

获取到`Node`之后有关平配置文件的所有信息都能够检索到。

### 2. 准备配置文件

```yaml
first-name: cheng
last-name: manyuan
info: {height: 178, age: 25}
nums: [1, 2, 3, 4]
girl-firend: ~
```

### 3. 读取对象

```c++
std::string first_name = config["first-name"].as<std::string>();
std::string last-name = config["last-name"].as<std::string>();

std::string address = config["info"]["height"].as<sint>();
int age = config["info"]["age"].as<int>();
```

### 4. 读取数组

```c++
// 普通for循环
for (std::size_t i = 0; i < config["nums"]; ++i) {
    std::cout << config["nums"][i].as<int>() << std::endl;
}

// 迭代器
for(auto iter = config["nums"].begin(); iter != config["nums"].end(); ++iter) {
    std::cout << iter->as<int>() << std::endl;
}
```

同样对象也可以使用迭代器，如上面的info对象，可以通过下面的代码进行读取

```c++
for (auto iter = config["info"].begin(); iter != config["info"].end(); ++iter) {
    std::cout << iter->first.as<std::string>() << ": " << iter->second.as<int>() << std::endl;
}
```

### 5. 节点类型

有的时候我们需要判断节点的类型，yaml-cpp定义了下面的类型

```c++
namespace YAML {
    struct NodeType {
        enum value {
            Undefined,
            Null,
            Scalar,
            Sequence,
            Map
        }
    };(
}
```

我们可以通过节点的Type()方法获取节点的类型

```c++
if (YAML::NodeType::Null == config["girl-firend"].Type()) {

}
```