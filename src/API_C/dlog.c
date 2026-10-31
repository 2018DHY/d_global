#include "dlog.h"

// 3. 核心日志函数
void log_output(LogLevel level, const char *file, const char *func, int line, const char *fmt, ...)
{
	// 判断当前日志级别，过低级别的日志不输出[6](@ref)
	if (level < CURRENT_LOG_LEVEL)
	{
		return;
	}

	// 添加颜色前缀或级别标签，便于识别
	const char *level_str[] = {"[DEBUG]", "[INFO]", "[ERROR]", "[FATAL]"};
	fprintf(stderr, "%s [%s %s():%d] ", level_str[level], file, func, line);

	// 处理可变参数并打印用户消息
	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	fprintf(stderr, "\n");
};