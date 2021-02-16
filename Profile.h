//измер€ть каждый вид сортировки и общее врем€ Total
#pragma once
#include <iostream>
#include <chrono>
#include <string>

class LogDuration
{
private:
    std::chrono::steady_clock::time_point start;
    std::string message;
public:
    explicit LogDuration(const std::string& msg = "") : start(std::chrono::steady_clock::now()), message(msg + ": ") {}
    ~LogDuration()
    {
        auto finish = std::chrono::steady_clock::now();
        auto dur = finish - start;
        std::cerr << message << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << " ms" << std::endl << std::endl; //cerr отладочна€ информаци€
    }
};

#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)
#define LOG_DURATION(message) \
        LogDuration UNIQ_ID(__LINE__){message}; //объ€вл€ем индивидуальный идентификатор в пределах .ссp файла



