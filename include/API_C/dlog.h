#ifndef DLOG_H
#define DLOG_H
#include <stdarg.h>
#include <stdio.h>

#include "commom.h"

EXTERN_C_BEGIN
// 1. 定义日志级别
typedef enum
{
    LOG_INFO,
    LOG_DEBUG,
    LOG_ERROR,
    LOG_FATAL
} LogLevel;

// 2. 通过宏控制全局日志级别，默认为 INFO
#ifndef CURRENT_LOG_LEVEL
#define CURRENT_LOG_LEVEL LOG_DEBUG
#endif

// 3. 核心日志函数
DLIB_API void log_output(LogLevel level, const char *file, const char *func, int line, const char *fmt, ...);

// 4. 为每个日志级别创建便捷的宏
#define CLOG_DEBUG(fmt, ...) log_output(LOG_DEBUG, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define CLOG_INFO(fmt, ...) log_output(LOG_INFO, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define CLOG_ERROR(fmt, ...) log_output(LOG_ERROR, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define CLOG_FATAL(fmt, ...) log_output(LOG_FATAL, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)

EXTERN_C_END

#endif // DLOG_H