#pragma once

#include <iostream>

/// Console颜色输出
#define CONSOLE_COLOR_CODE_CLOSE "\033[0m" // 关闭所有属性
#define CONSOLE_COLOR_CODE_RESERVE "\033[7m" // 反显

#define CONSOLE_COLOR_CODE_BLACK "\033[30m" // 前景-黑色
#define CONSOLE_COLOR_CODE_RED "\033[31m"
#define CONSOLE_COLOR_CODE_GREEN "\033[32m"
#define CONSOLE_COLOR_CODE_YELLOW "\033[33m"
#define CONSOLE_COLOR_CODE_BLUE "\033[34m"
#define CONSOLE_COLOR_CODE_PURPLE "\033[35m"
#define CONSOLE_COLOR_CODE_LIGHTBLUE "\033[36m"
#define CONSOLE_COLOR_CODE_WHITE "\033[37m"

#define CONSOLE_COLOR_CODE_BLACK_RESERVE "\033[30m" CONSOLE_COLOR_CODE_RESERVE // 黑色-反显
#define CONSOLE_COLOR_CODE_RED_RESERVE "\033[31m" CONSOLE_COLOR_CODE_RESERVE
#define CONSOLE_COLOR_CODE_GREEN_RESERVE "\033[32m" CONSOLE_COLOR_CODE_RESERVE
#define CONSOLE_COLOR_CODE_YELLOW_RESERVE "\033[33m" CONSOLE_COLOR_CODE_RESERVE
#define CONSOLE_COLOR_CODE_BLUE_RESERVE "\033[34m" CONSOLE_COLOR_CODE_RESERVE
#define CONSOLE_COLOR_CODE_PURPLE_RESERVE "\033[35m" CONSOLE_COLOR_CODE_RESERVE
#define CONSOLE_COLOR_CODE_LIGHTBLUE_RESERVE "\033[36m" CONSOLE_COLOR_CODE_RESERVE
#define CONSOLE_COLOR_CODE_WHITE_RESERVE "\033[37m" CONSOLE_COLOR_CODE_RESERVE

#define CONSOLE_BACKGROUND_COLOR_CODE_BLACK "\033[40m" // 背景-黑色
#define CONSOLE_BACKGROUND_COLOR_CODE_RED "\033[41m" // 背景-红色
#define CONSOLE_BACKGROUND_COLOR_CODE_GREEN "\033[42m" // 背景-绿色
#define CONSOLE_BACKGROUND_COLOR_CODE_YELLOW "\033[43m" // 背景-黄色
#define CONSOLE_BACKGROUND_COLOR_CODE_BLUE "\033[44m" // 背景-蓝色
#define CONSOLE_BACKGROUND_COLOR_CODE_PURPLE "\033[45m" // 背景-紫色
#define CONSOLE_BACKGROUND_COLOR_CODE_LIGHTBLUE "\033[46m" // 背景-浅蓝色
#define CONSOLE_BACKGROUND_COLOR_CODE_WHITE "\033[47m" // 背景-白色

#define CONSOLE_COLOR_CODE_BLUE_WHITE CONSOLE_BACKGROUND_COLOR_CODE_BLUE CONSOLE_COLOR_CODE_WHITE // 背蓝-前白

/// 有色LOG定义
#ifndef LOG_LEVEL_ERROR
    #define LOG_LEVEL_ERROR 1 // error级别log输出使能
#endif
#ifndef LOG_LEVEL_INFO
    #define LOG_LEVEL_INFO 1 // info级别log输出使能
#endif
#ifndef LOG_LEVEL_DEBUG
    #define LOG_LEVEL_DEBUG 1 // debug级别log输出使能
#endif
#ifndef LOG_LEVEL_TRACE
    #define LOG_LEVEL_TRACE 1 // trace级别log输出使能
#endif

#ifndef LOG_ERROR
    #define LOG_ERROR if(LOG_LEVEL_ERROR) std::cout << CONSOLE_COLOR_CODE_RED_RESERVE << "[ERROR]"\
    << CONSOLE_COLOR_CODE_CLOSE << " " << CONSOLE_COLOR_CODE_RED
#endif
#ifndef LOG_INFO
    #define LOG_INFO if(LOG_LEVEL_INFO) std::cout << CONSOLE_COLOR_CODE_YELLOW_RESERVE << "[INFO]"\
    << CONSOLE_COLOR_CODE_CLOSE << " " << CONSOLE_COLOR_CODE_YELLOW
#endif
#ifndef LOG_DEBUG
    #define LOG_DEBUG if(LOG_LEVEL_DEBUG) std::cout << CONSOLE_COLOR_CODE_LIGHTBLUE_RESERVE << "[DEBUG]"\
    << CONSOLE_COLOR_CODE_CLOSE << " "
#endif
#ifndef LOG_TRACE
    #define LOG_TRACE if(LOG_LEVEL_TRACE) std::cout << CONSOLE_COLOR_CODE_CLOSE << "[TRACE] "
#endif

/// 函数定义：将输入的参数转化为字符串
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

/// 性能测试工具：耗时
#define TIMERSTART(tag) auto tag##_start = std::chrono::steady_clock::now(),tag##_end = tag##_start;
#define TIMEREND(tag) tag##_end = std::chrono::steady_clock::now();
#define DURATION_ms(tag) std::cout << CONSOLE_COLOR_CODE_PURPLE << "Performance@" << #tag\
                                   << " cost "<< std::chrono::duration_cast<std::chrono::milliseconds>(tag##_end - tag##_start).count()\
                                   << "ms\n" << CONSOLE_COLOR_CODE_CLOSE;
