#ifndef DFILE_H
#define DFILE_H
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "commom.h"

EXTERN_C_BEGIN
/**
 * 以二进制方式将读取文件所有内容
 * path为文件路径
 * rt为文件所有内容
 */

DLIB_API int64_t dg_read_all(char *path, char **rt);

DLIB_API void dg_read_all_free(char *ptr);

/**
 * 以二进制方式读取所有内容 不同实现
 * path为文件路径
 * rt为文件所有内容
 */
DLIB_API int64_t f_read_all(const char *const path, char **rt);

DLIB_API void f_read_all_free(char *ptr);

DLIB_API int64_t fd_read_all(FILE* fd,char **rt,bool ex);


DLIB_API int64_t f_read_line(FILE *fd,char ** rt,bool ex);
DLIB_API void f_read_line_free(char*prt);

EXTERN_C_END
#endif // DFILE_H