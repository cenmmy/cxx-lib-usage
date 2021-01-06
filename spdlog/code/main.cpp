#include <iostream>
#include "spdlog/spdlog.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/async.h>
#include <spdlog/sinks/daily_file_sink.h>

int main()
{
    // 控制台日志输出
    spdlog::info("Hello, {}!!", "Spdlog");
    // 文件日志输出
    try {
        std::string basic_log_file = R"(/home/cenmmy/Documents/cxx-lib-usage/spdlog/code/logs/basic_logger_file.txt)";
        std::string rotate_log_file = R"(/home/cenmmy/Documents/cxx-lib-usage/spdlog/code/logs/rotate_logger_file.txt)";
        std::string async_log_file = R"(/home/cenmmy/Documents/cxx-lib-usage/spdlog/code/logs/async_logger_file.txt)";
        std::string daily_log_file = R"(/home/cenmmy/Documents/cxx-lib-usage/spdlog/code/logs/daily_logger_file.txt)";
        auto basic_file_logger = spdlog::basic_logger_mt("basic_file_logger", basic_log_file);
        basic_file_logger->info("spdlog initilization {}", "success");
        auto rotate_file_logger = spdlog::rotating_logger_mt("rorate_file_logger", rotate_log_file, 1024, 3, false);
        for (int i = 0; i < 100; ++i) {
            rotate_file_logger->info("abcdefghijklmnopqrstuvwxyz");
        }
        spdlog::init_thread_pool(1000, 1);
        auto async_file_logger = spdlog::basic_logger_mt<spdlog::async_factory>("async_file_logger", async_log_file);
        for (int i = 0; i < 101; ++i) {
            async_file_logger->info("Async message #{}", i);
        }

        auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(daily_log_file, 13, 51);
        auto net_logger = std::make_shared<spdlog::logger>("net", daily_sink);
        auto hw_logger  = std::make_shared<spdlog::logger>("hw",  daily_sink);
        auto db_logger  = std::make_shared<spdlog::logger>("db",  daily_sink);

        net_logger->info("net");
        hw_logger->info("hw");
        db_logger->info("db");
        sleep(60);
        net_logger->info("net");
        hw_logger->info("hw");
        db_logger->info("db");

    } catch (spdlog::spdlog_ex& ex) {
        std::cout << "spdlog initialization failed!" << std::endl;
    }
}