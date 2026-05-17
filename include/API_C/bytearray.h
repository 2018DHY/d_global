#ifndef BYTEARRAY
#define BYTEARRAY
#include "../commom.h"
#include <stdint.h>
#include <stdbool.h>
const static uint16_t DEF_CPT = 1024; // default capacity

struct byte_array
{
    uint64_t size;
    uint64_t capacity;
    uint8_t *dt;
    struct byte_array_ops *ops;
};
// 需要改为外部控制capacity

struct byte_array_ops
{
    bool (*scale)(struct byte_array *self, uint64_t capacity);
    bool (*apd_byte)(struct byte_array *self, uint8_t byte);
    bool (*append)(struct byte_array *ori, struct byte_array *cnt);
    struct byte_array *(*mid)(struct byte_array *ori, uint64_t pos);
    struct byte_array *(*mid_len)(struct byte_array *ori, uint64_t pos, uint64_t lenth);
    int64_t (*indexof_hex)(struct byte_array *self, uint64_t index, const char *pattern);
};

/// @brief 获得一个初始容器capacity大小,size为0的buf_ary实例
DLIB_API_EXPORT struct byte_array *init_btry(uint64_t capacity);

/// @brief 给buf扩容
/// @param buf
/// @param capacity
/// @return
DLIB_API_EXPORT bool scale_btry(struct byte_array *self, uint64_t capacity);

/// @brief 给ori追加内容
/// @param ori
/// @param cnt
/// @return
DLIB_API_EXPORT bool btry_apd(struct byte_array *self, struct byte_array *other);

DLIB_API_EXPORT bool btry_apd_byte(struct byte_array *self, uint8_t byte);

DLIB_API_EXPORT struct byte_array *btry_mid(struct byte_array *self, uint64_t pos);
DLIB_API_EXPORT struct byte_array *btry_mid_len(struct byte_array *self, uint64_t pos, uint64_t lenth);

DLIB_API_EXPORT uint8_t *str_trim(const char *str);

DLIB_API_EXPORT struct byte_array *hexstrTohex_ary(const char *hex_str_);

// 认为pattern内容是16进制形式
DLIB_API_EXPORT int64_t btry_indexof_hex(struct byte_array *self, uint64_t index, const char *pattern);

DLIB_API_EXPORT void btry_free(struct byte_array *buf);

#endif /* BYTEARRAY */
