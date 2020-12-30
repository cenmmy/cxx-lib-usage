#include <iostream>
#include <yaml-cpp/yaml.h>
#include <fstream>

int main()
{
    std::cout << "hello world!" << std::endl;
    std::string config_path = R"(/home/cenmmy/Documents/cxx-lib-usage/yaml-cpp/code/config.yaml)";
    // 加载配置文件，将其解析成为一个节点对象，这里的节点的概念与解析html dom树所使用的方法是类似的
    YAML::Node config = YAML::LoadFile(config_path);
    // 读取配置文件中的对象, yaml-cpp对配置文件的解析支持中文
    std::string first_name = config["first-name"].as<std::string>();
    std::string last_name = config["last-name"].as<std::string>();

    std::string address = config["info"]["address"].as<std::string>();
    int age = config["info"]["age"].as<int>();

    std::cout << first_name << " " << last_name << std::endl;
    std::cout << address << " " << age << std::endl;
    for (auto iter = config["contries"].begin(); iter != config["contries"].end(); ++iter)
    {
        std::cout << iter->first.as<std::string>() << ": " << iter->second.as<std::string>() << std::endl;
    }
    // 读取配置文件中的数组
    std::cout << "nums type is " << config["nums"].Type() << std::endl;
    for (std::size_t i = 0; i < config["nums"].size(); ++i)
    {
        std::cout << config["nums"][i].as<int>() << std::endl;
    }

    // 迭代器
    for (auto iter = config["nums"].begin(); iter != config["nums"].end(); ++iter)
    {
        std::cout << iter->as<int>() << std::endl;
    }
    // 判断节点类型
    if (config["girl-firend"].Type() == YAML::NodeType::Null) {
        std::cout << first_name << " " << last_name << "没有女朋友" << std::endl;
    }
    // 写配置到配置文件中
    std::ofstream fout(config_path);
    config["score"] = 90;
    // 节点对象重载了输出运算符
    fout << config;
    fout.close();
    return 0;
}