#ifndef INTERFACEC
#define INTERFACEC

#include "commom.h"

EXTERN_C_BEGIN
// #define _FILE_OFFSET_BITS 64
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

// int a = 0;
DLIB_API void c_say_hello();

/**
 * 返回两个字符串拼接后的大小,若为0则失败
 * rt为拼接后的字符串指针
 * src*为需要拼接的两个字符串
 * *_len是两个字符串的长度
 * free是代表是否要帮你释放src1（当前无用）
 */

DLIB_API int64_t dg_append(char **rt, char *src1, int64_t c1_len, char *src2, int64_t c2_len, bool free);

DLIB_API void dg_append_free(char *ptr);


EXTERN_C_END
#endif /* INTERFACEC */
