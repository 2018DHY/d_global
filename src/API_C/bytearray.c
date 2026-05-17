#include "../../include/API_C/bytearray.h"
#include "../../include/API_C/interfacec.h"
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static const struct byte_array_ops baOps = {
    .scale = scale_btry,
    .apd_byte = btry_apd_byte,
    .append = btry_apd,
    .mid = btry_mid,
    .mid_len = btry_mid_len,
    .indexof_hex = btry_indexof_hex};

DLIB_API_EXPORT struct byte_array *init_btry(uint64_t capacity)
{
    if (capacity > 0)
    {
        struct byte_array *ptr = (struct byte_array *)malloc(sizeof(struct byte_array));
        memset(ptr, 0, sizeof(struct byte_array));
        ptr->dt = (uint8_t *)malloc(capacity);
        if (ptr->dt != NULL)
        {
            ptr->capacity = capacity;
            ptr->ops = &baOps;
            return ptr;
        }
    }
    return NULL;
}

DLIB_API_EXPORT bool scale_btry(struct byte_array *self, uint64_t capacity)
{
    if (self != NULL)
    {
        if (capacity <= self->capacity)
        {
            return false;
        }
        uint8_t *o_dt = self->dt; // 用于将旧数据拷贝
        uint8_t *dt_ptr = (uint8_t *)malloc(capacity);
        if (dt_ptr != NULL)
        {
            if (self->size)
            {
                memcpy(dt_ptr, o_dt, self->size);
                free(self->dt);
                self->dt = dt_ptr;
                self->capacity = capacity;
                return true;
            }
        }
    }

    return false;
}

DLIB_API_EXPORT bool btry_apd_byte(struct byte_array *self, uint8_t byte)
{
    if (self->size + 1 > self->capacity)
        if (!self->ops->scale(self, self->capacity * 2))
        {
            CLOG_DEBUG("scale fail!");
            return false;
        }

    self->dt[self->size] = byte;
    self->size++;
    return true;
}

DLIB_API_EXPORT struct byte_array *btry_mid(struct byte_array *self, uint64_t pos)
{
    return NULL;
}

DLIB_API_EXPORT struct byte_array *btry_mid_len(struct byte_array *self, uint64_t pos, uint64_t lenth)
{
    return NULL;
}

DLIB_API_EXPORT bool btry_apd(struct byte_array *self, struct byte_array *other)
{
    return false;
}

DLIB_API_EXPORT void btry_free(struct byte_array *buf)
{
    if (buf != NULL)
    {
        if (buf->dt != NULL)
        {
            free(buf->dt);
        }
        free(buf);
    }
    return;
}

DLIB_API_EXPORT uint8_t *str_trim(const char *str)
{
    uint64_t str_len = strlen(str);
    uint8_t *rt = (uint8_t *)malloc(str_len);
    if (rt == NULL)
    {
        return NULL;
    }
    uint64_t j = 0;
    for (uint64_t i = 0; i < str_len; i++)
    {
        if (isspace(str[i]))
        {
            continue;
        }
        rt[j] = str[i];
        j++;
    }
    return rt;
}

DLIB_API_EXPORT struct byte_array *hexstrTohex_ary(const char *hex_str_)
{
    uint8_t *hex_str = str_trim(hex_str_);
    uint64_t str_len = strlen(hex_str);
    const char *c_type = setlocale(LC_CTYPE, NULL);
    CLOG_INFO("LC_CTYPE is %s", c_type);
    if ((str_len % 2) != 0)
    {
        CLOG_ERROR("hex hex_str word num is Not an integer multiple of 2 ");
        return NULL;
    }
    struct byte_array *hex = init_btry(DEF_CPT);
    uint8_t one_byte = 0;
    uint8_t temp;
    for (uint64_t i = 0; i < str_len; i++)
    {
        temp = 0;
        if (isdigit(hex_str[i]))
        {
            temp = hex_str[i] - 0x30;
        }
        else if (isalpha(hex_str[i]))
        {
            if (isupper(hex_str[i]))
            {
                temp = hex_str[i] - 0x37;
            }

            if (islower(hex_str[i]))
            {
                temp = hex_str[i] - 0x57;
            }
        }
        else
        {
            CLOG_ERROR("illegal character!!!");
            btry_free(hex);
            hex = NULL;
            break;
        }
        if ((i + 1) % 2 != 0)
        {
            one_byte |= 16 * temp;
        }
        else
        {
            one_byte |= temp;
            hex->ops->apd_byte(hex, one_byte);
            one_byte = 0;
        }
    }

    return hex;
}

DLIB_API_EXPORT int64_t btry_indexof_hex(struct byte_array *self, uint64_t index, const char *pattern)
{
    struct byte_array *hexs = hexstrTohex_ary(pattern);

    int64_t rt = -1;
    uint64_t hex_len = hexs->size;
    uint64_t j = 0;
    // BF算法 暴力匹配
    for (uint64_t i = 0; i < (self->size - hex_len); i++)
    {
        for (j = 0; j < hex_len; j++)
        {
            if (self->dt[i + j] != hexs->dt[j])
            {
                break;
            }
        }
        if (j == hex_len - 1)
        {
            rt = i;
        }
    }
    btry_free(hexs);
    return rt;
}