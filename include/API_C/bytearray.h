#ifndef BYTEARRAY
#define BYTEARRAY
//byte_array的构成是想得到一个轻量的QByteArray实现
#include "commom.h"
#include "dlog.h"
#include <stdint.h>
#include <stdbool.h>
const static uint16_t DEF_CPT = 1024; // default capacity

struct byte_array
{
    int64_t size;
    int64_t capacity;
    uint8_t *dt;
    const struct byte_array_ops *ops;
};
// 需要改为外部控制capacity

struct byte_array_ops
{
    bool (*scale)(struct byte_array *self, int64_t capacity);
    bool (*apd_byte)(struct byte_array *self, uint8_t byte);
    bool (*append)(struct byte_array *ori, struct byte_array *cnt);
    struct byte_array *(*mid)(struct byte_array *ori, int64_t pos);
    struct byte_array *(*mid_len)(struct byte_array *ori, int64_t pos, int64_t lenth);
    int64_t (*indexof_hex)(struct byte_array *self, int64_t index, const char *pattern);
};

/// @brief 获得一个初始容器capacity大小,size为0的buf_ary实例,容器内字节已初始化为0x00;
DLIB_API struct byte_array *init_btry(int64_t capacity);

/// @brief 给buf扩容
/// @param buf
/// @param capacity
/// @return
DLIB_API bool btry_scale(struct byte_array *self, int64_t capacity);

/// @brief 给本字节数组追加other中包含的内容
/// @param self 
/// @param other 
/// @return 
DLIB_API bool btry_apd(struct byte_array *self, struct byte_array *other);

/// @brief 给字节数组追加一个字节内容,内容为byte
/// @param self 本字节数组
/// @param byte 实际内容
/// @return 
DLIB_API bool btry_apd_byte(struct byte_array *self, uint8_t byte);

/// @brief 返回一个从pos开始到本byte_array结束的新的byte_array对象,若pos位置非法,则返回空指针
/// @param pos 数组中的起始位置
DLIB_API struct byte_array *btry_mid(struct byte_array *self, int64_t pos);
/// @brief 返回一个从pos开始总长为lenth的新的byte_array对象,若pos位置非法,则返回空指针
/// @brief 若pos+lenth>=size,则返回从pos开始到本数组结束
/// @param pos 数组中的起始位置
DLIB_API struct byte_array *btry_mid_len(struct byte_array *self, int64_t pos, int64_t lenth);

DLIB_API uint8_t *str_trim(const char *str);
/// @brief 将16进制字符串转化存储到byte_array中 hex字符串形式形如"1a cf fc 1d"
DLIB_API struct byte_array *hexstrTohex_ary(const char *hex_str_);

// 认为pattern内容是16进制形式
DLIB_API int64_t btry_indexof_hex(struct byte_array *self, int64_t index, const char *pattern);

/// @brief 借鉴libevent2的接口形式,使用一级指针
/// @param buf 
/// @return 
DLIB_API void btry_free(struct byte_array *buf);

#endif /* BYTEARRAY */
