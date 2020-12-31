# spdlog库的相关概念及使用方法

### 1. 安装

`spdlog`是一个纯头文件日志库，我们只需要将相关头文件拷贝到项目中即可。

#### 1.1 下载`spdlog`源代码

```shell
$ git clone https://github.com/gabime/spdlog.git
```

```shell
$ cd spdlog
$ ls
appveyor.yml  cmake           example  INSTALL  logos      scripts  tests
bench         CMakeLists.txt  include  LICENSE  README.md  src
```
#### 1.2 配置项目

将`include`文件夹拷贝到项目根目录下。

在`CMakeLists.txt`文件中添加如下代码

```cmake
set(CMAKE_CXX_STANDARD 11)

target_include_directories(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/include")
```

### 2. 使用样例

#### 2.1 控制台日志输出

```c++
#include <spdlog/spdlog.h>

int main() {
    spdlog::info("Hello, {}!!", "Spdlog")
}
```

输出：

```shell
[2020-12-31 10:16:12.638] [info] Hello, Spdlog!!
```

#### 2.2 文件日志输出

```c++
#include <iostream>
#include <spdlog/spdlog.h
#include <spdlog/basic_file_sink.h>

int main() {
    try {
        auto my_logger = spdlog::basic_logger_mt("basic_logger", "logs/basic.txt");
    } catch (const spdlog::spdlog_ex& ex) {
        std::cout << "Log initialization failed!" << std::endl;
    }
}
```

`basic_logger_mt`函数的第一个参数为日志输出器的名称，第二个参数为日志文件的路径。

#### 2.3 滚动日志文件输出

```c++
 #include <spdlog/sinks/rotating_file_sink.h>
 ...
auto rotate_file_logger = spdlog::rotating_logger_mt("rorate_file_logger", rotate_log_file, 1024, 3, false);
...
```

`rotating_logger_mt`函数的第一个参数为日志输出器的名称，第二个参数是日志文件的路径，第三个参数是单个滚动文件的大小，第四个参数是滚动文件的个数，第五个参数具体作用不清楚。

#### 2.4 使用工厂方法创建异步日志输出器

```c++
#include <spdlog/async.h>
...
auto async_file_logger = spdlog::basic_logger_mt<spdlog::async_factory>("async_file_logger", async_log_file);
for (int i = 0; i < 101; ++i) {
    async_file_logger->info("Async message #{}", i);
}
...
```

`basic_logger_mt`实际上是模板函数，其默认的模板参数是`spdlog::synchronous_factory`，从名称进行推断其应该是创建同步日志输出器的工厂类或函数。

我们可以手动指定模板参数为`spdlog::async_factory`，使其创建异步输出的日志器。

#### 2.5 创建多个日志输出器，使其共享同一个日志输出文件。

```c++
auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(daily_log_file, 23, 59);
auto net_logger = std::make_shared<spdlog::logger>("net", daily_sink);
auto hw_logger  = std::make_shared<spdlog::logger>("hw",  daily_sink);
auto db_logger  = std::make_shared<spdlog::logger>("db",  daily_sink); 

net_logger->info("net");
hw_logger->info("hw");
db_logger->info("db");
```

`daily_file_sink_mt`的第一个参数是日志输出文件的路径， 第二个和第三个参数分别表示程序不中断的情况下创建新的日志文件的时间节点。

#### 2.6 创建一个关联多个`sinks`的日志器，并且为每个`sink`设置不同的`level`和输出格式。

```c++
auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
console_sink->set_level(spdlog::level:warn);
console_sink->set_pattern("[multi_sink_example] [%^%l%$] %v");

auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/log.txt", true);
file_sink->set_level(spdlog::level_trace);

spdlog::sinks_init_list sink_list = {console_sink, file_sink};
spdlog::logger logger("multi_sink", sink_list.begin(), sink_list.end());
logger.set_level(spdlog::level::debug);
logger.warn("this should appear in both console and file");
logger.info("this message should not appear in the console, only in the file");
```

#### 2.7 打印用户自定义的对象

```c++
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h" // must be included
#include "spdlog/sinks/stdout_sinks.h"

class some_class {};
std::ostream& operator<<(std::ostream& os, const some_class& c)
{ 
    return os << "some_class"; 
}

void custom_class_example()
{
    some_class c;
    auto console = spdlog::stdout_logger_mt("console");
    console->info("custom class with operator<<: {}..", c);
}
```