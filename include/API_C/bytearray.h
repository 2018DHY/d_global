#ifndef BYTEARRAY
#define BYTEARRAY
#include "../commom.h"
#include <stdint.h>
#include <stdbool.h>

struct byte_array
{
    uint64_t size;
    uint64_t capacity;
    uint8_t *dt;
};
//需要改为外部控制capacity


/// @brief 获得一个初始容器capacity大小,size为0的buf_ary实例
DLIB_API_EXPORT struct byte_array *get_btry(uint64_t capacity);

/// @brief 给buf扩容
/// @param buf 
/// @param capacity 
/// @return 
DLIB_API_EXPORT bool scale_btry(struct byte_array *buf,uint64_t  capacity);

/// @brief 给ori追加内容
/// @param ori 
/// @param cnt 
/// @return 
DLIB_API_EXPORT bool btry_apd(struct byte_array * ori,struct byte_array *cnt);

DLIB_API_EXPORT struct byte_array* btry_mid(struct byte_array * ori,uint64_t pos);
DLIB_API_EXPORT struct byte_array* btry_mid_len(struct byte_array * ori,uint64_t pos,uint64_t lenth);

DLIB_API_EXPORT struct byte_array* btry_indexof(struct byte_array * ori,const char* pattern);

DLIB_API_EXPORT void btry_free(struct byte_array *buf);

#endif /* BYTEARRAY */
