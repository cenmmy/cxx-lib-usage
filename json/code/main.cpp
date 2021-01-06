#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

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

// NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Dog, name, age);

int main()
{
    // 声明与构造
    json j1;
    json j2 = json::object();
    json j3 = json::array();

    std::cout << j1.type_name() << std::endl;
    std::cout << j2.type_name() << std::endl;
    std::cout << j3.type_name() << std::endl;

    // 内容构造
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

    // 解析json，字符串-->json对象
    std::string json_str = R"(
        {
            "name": "Judd Trump",
            "credits": 1754500,
            "ranking": 1
        }       
    )";

    json j6 = json::parse(json_str);
    std::cout << j6.type_name() << std::endl;
    std::cout << j6["name"].get<std::string>() << std::endl;

    // 序列化json，json对象-->字符串
    std::string j5_str = j5.dump();
    std::cout << j5_str << std::endl;

    // 读取json文件
    json j7;
    std::ifstream in("/home/cenmmy/Documents/cxx-lib-usage/json/code/json/input.json");
    in >> j7;
    std::cout << j7["name"].get<std::string>() << ": " << j7["age"].get<int>() << std::endl;
    in.close();

    // 导出json文件
    std::ofstream out("/home/cenmmy/Documents/cxx-lib-usage/json/code/json/output.json");
    out << j4;
    out.close();

    // 转换成C++对象, 当向json的构造函数中传递你的类型时，
    // 自动调用`to_json`函数，当调用get<your_type>()或get_to(your_type&)会自动调用from_json函数
    Person p = {"cheng", 100, 1};
    json j8 = p;
    Person p1 = j8.get<Person>();
    std::cout << p1.name << " " << p1.credits << " " << p1.ranking << std::endl;
    // 使用NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE或NLOHMANN_DEFINE_TYPE_INTRUSIVE宏自动生成to_json和from_json函数
    // NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE是非侵入式的，它不能访问类的私有成员变量，因此通常为结构体生成to_json和from_json函数
    // NLOHMANN_DEFINE_TYPE_INTRUSIVE是侵入式的，它定义为类的public成员，可以访问类的似有成员变量
    Dog dog = {"xiaohuang", 8};
    json j9 = dog;
    std::cout << j9.dump() << std::endl;
    return 0;
}