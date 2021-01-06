# C++中Json库的使用

nlohmann json库是C++项目中应用最广泛的库，下面我们将介绍该json库的基本用法。

### 1. Json基本语法

json语法可以表示一下三种类型的值：

+ 简单值：字符串、数值、布尔值和Null
+ 对象：由一组无序的键值对组成
+ 数组：表示一组有序的列表，数组元素可以是不同的类型

JSON对象

```json
{
    "name": "Nicolas",
    "age": 29
}
```

JSON要求必须给对象属性加引号。

JSON数组

```json
["Nicolas", 29]
```

### 2. 将nlohmann json集成到当前项目中

从`https://github.com/nlohmann/json`网址下载项目，然后将项目中`single_include`下的头文件文件夹拷贝到自己的项目头文件目录下即可。

```c++
#include <nlohmann/json.hpp>
```

在使用到`json`库的源文件中包含该头文件即可。

### 3. 声明与构造JSON对象

```c++
json j1;
json j2 = json::object();
json j3 = json::array();
```

上面的代码中我们创建一个空的json实例、一个object类型的json实例和一个array类型的json实例。

### 4. 内容构造

```c++
json j4 = R"(
    {
        "name": "Judd Trump",
        "credits": 1754500,
        "ranking": 1
    }
)"_json;

json j5 = {
    {"name", "Judd Trump"},
    {"credits", 1754500},
    {"ranking", 1}
};
```

构造了json实例，并设置了内容。

### 5. 解析json

```c++
std::string json_str = R"(
    {
        "name": "Judd Trump",
        "credits": 1754500,
        "ranking": 1
    }       
)";

json j6 = json::parse(json_str);
std::string name1 = j6["name"].get<std::string>();
std::string name2;
j6["name"].get_to<std::string>(name2);
```

使用`parse`静态方法将json字符串转换为json对象，使用get/get_to方法获取指定键对应的值，两者的区别在于get将值作为返回值，get_to接受参数，并将值赋值给该参数。

### 6. 序列化json

```c++
std::string j5_str = j5.dump();
```

### 7. 读取json文件和导出json文件

```c++
#include <fstream>

json j7;
std::ifstream in("/home/cenmmy/Documents/cxx-lib-usage/json/codejson/input.json");
in >> j7;
in.close();
// 导出json文件
std::ofstream out("/home/cenmmy/Documents/cxx-lib-usage/json/codejson/output.json");
out << j4;
out.close();
```

### 8. json对象与C++对象之前的相互转换

```c++
struct Person {
    std::string name;
    int credits;
    int ranking;  
};

void to_json(json& j, const Person& p) {
    j = json{
        {"name", p.name},
        {"credits", p.credits},
        {"ranking", p.ranking}
    };
}

void from_json(const json& j, Person& p) {
    j.at("name").get_to(p.name);
    j.at("credits").get_to(p.credits);
    j.at("ranking").get_to(p.ranking);
}

class Dog {
    std::string name;
    int age;
public:
    Dog(std::string name, int age):name(name), age(age) {}
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Dog, name, age);
};
```

当使用自定义对象构造json实例时，会调用相应的`to_json`函数，当使用`get`/`get_to`函数时，会自动调用`from_json`将json转化为对象。

为了方便编码，`json`库提供了`NLOHMANN_DEFINE_TYPE_INTRUSIVE`和`NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE`。

使用NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE或NLOHMANN_DEFINE_TYPE_INTRUSIVE宏自动生成to_json和from_json函数。NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE是非侵入式的，它不能访问类的私有成员变量，因此通常为结构体生成to_json和from_json函数
。NLOHMANN_DEFINE_TYPE_INTRUSIVE是侵入式的，它定义为类的public成员，可以访问类的似有成员变量