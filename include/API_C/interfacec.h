#ifndef INTERFACEC
#define INTERFACEC

#ifdef __cplusplus
#define EXTERN_C_BEGIN \
    extern "C"         \
    {
#define EXTERN_C_END }
#define INLINE inline
#else
#define EXTERN_C_BEGIN 
#define EXTERN_C_END 
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define INLINE inline
#else
#define INLINE
#endif
#endif
#ifdef DLIB_EXPORT
#define DLIB_API_EXPORT __declspec(dllexport)
#else
#define DLIB_API_EXPORT
#endif

EXTERN_C_BEGIN
// #define _FILE_OFFSET_BITS 64
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

    // int a = 0;
    void c_say_hello();

    // 1. 定义日志级别
typedef enum
{
    LOG_DEBUG,
    LOG_INFO,
    LOG_ERROR,
    LOG_FATAL
} LogLevel;

// 2. 通过宏控制全局日志级别，默认为 INFO
#ifndef CURRENT_LOG_LEVEL
#define CURRENT_LOG_LEVEL LOG_INFO
#endif

// 3. 核心日志函数
void log_output(LogLevel level, const char *file, const char *func, int line, const char *fmt, ...);

// 4. 为每个日志级别创建便捷的宏
#define CLOG_DEBUG(fmt, ...) log_output(LOG_DEBUG, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define CLOG_INFO(fmt, ...) log_output(LOG_INFO, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define CLOG_ERROR(fmt, ...) log_output(LOG_ERROR, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define CLOG_FATAL(fmt, ...) log_output(LOG_FATAL, __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)



    struct buf_ary
{
    u_int64_t size;
    u_int64_t capacity;
    char *dt;
};
//需要改为外部控制capacity

/// @brief 获得一个初始容器capacity大小,size为0的buf_ary实例
struct buf_ary *get_bfry(u_int64_t capacity);

/// @brief 给buf扩容
/// @param buf 
/// @param capacity 
/// @return 
bool scale_bfry(struct buf_ary **buf,u_int64_t  capacity);

/// @brief 给ori追加内容
/// @param ori 
/// @param cnt 
/// @param cnt_sz 
/// @return 
bool bfry_apd(struct buf_ary ** ori,const char* cnt,u_int64_t cnt_sz);

void bfry_free(struct buf_ary **buf);


/**
 * 返回两个字符串拼接后的大小,若为0则失败
 * rt为拼接后的字符串指针
 * src*为需要拼接的两个字符串
 * *_len是两个字符串的长度
 * free是代表是否要帮你释放src1（当前无用）
 */

int64_t dg_append(char **rt, char *src1, int64_t c1_len, char *src2, int64_t c2_len, bool free);

void dg_append_free(char *ptr);
/**
 * 以二进制方式将读取文件所有内容
 * path为文件路径
 * rt为文件所有内容
 */

int64_t dg_read_all(char *path, char **rt);

void dg_read_all_free(char *ptr);

/**
 * 以二进制方式读取所有内容 不同实现
 * path为文件路径
 * rt为文件所有内容
 */
int64_t f_read_all(const char *const path, char **rt);

void f_read_all_free(char *ptr);

int64_t fd_read_all(FILE* fd,char **rt,bool ex);


int64_t f_read_line(FILE *fd,char ** rt,bool ex);
void f_read_line_free(char*prt);

EXTERN_C_END
#endif /* INTERFACEC */
