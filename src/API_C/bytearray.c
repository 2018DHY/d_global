#include "bytearray.h"
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 1024 * 1024 = 2^20  ==> 1MB
// 1024 * 1024 *1024 = 2^30  ==> 1GB
// 1024 * 1024 *1024 * 2= 2^31  ==> 2GB    int32_t
// 1024 * 1024 *1024 * 4= 2^32  ==> 4GB
// 2 ^ 32 = 4,294,967,296 约42亿
// 2 ^ 33 = 8,589,934,592 约85亿
// 2^30 * 2 ^ 33 = 2 ^ 63 = 1GB * 85亿

static const struct byte_array_ops baOps = {
    .scale = btry_scale,
    .apd_byte = btry_apd_byte,
    .append = btry_apd,
    .mid = btry_mid,
    .mid_len = btry_mid_len,
    .indexof_hex = btry_indexof_hex};

struct byte_array *init_btry(int64_t capacity)
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

bool btry_scale(struct byte_array *self, int64_t capacity)
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

bool btry_apd_byte(struct byte_array *self, uint8_t byte)
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

struct byte_array *btry_mid(struct byte_array *self, int64_t pos)
{
    struct byte_array *rt = NULL;
    if (pos < 0 || pos > self->size - 1) // 如果位置小于0或超过数组最后位置
    {
        return NULL;
    }
    else
    {
        //    pos   end
        //     |     |
        // 0 1 2 3 4 5
        int64_t len = (self->size - 1) - pos + 1;
        int64_t cap = DEF_CPT; // 容量
        if (len > DEF_CPT)
        {
            cap = len + cap; // 比实际复制的字节容量多了DEF_CPT大小
        }
        rt = init_btry(cap);
        memcpy(rt->dt, self->dt + pos, len);
        rt->size = len;
        return rt;
    }
}

struct byte_array *btry_mid_len(struct byte_array *self, int64_t pos, int64_t lenth)
{
    struct byte_array *rt = NULL;
    if (pos < 0 || pos > self->size - 1 || lenth < 1) // 如果位置小于0或超过数组最后位置,或长度小与等于0
    {
        return NULL;
    }
    else
    {
        int64_t end = pos + lenth;
        if (end > self->size)
        {
            return self->ops->mid(self, pos);
        }
        else
        {
            int64_t cap = DEF_CPT; // 容量
            if (lenth > DEF_CPT)
            {
                cap = lenth + cap;
            }
            rt = init_btry(cap);
            memcpy(rt->dt, self->dt + pos, lenth);
            rt->size = lenth;
            return rt;
        }
    }
    return NULL;
}

bool btry_apd(struct byte_array *self, struct byte_array *other)
{
    if (self == NULL && other == NULL)
    {
        return false;
    }
    else
    {
        if (other->size > 0)
        {
            int64_t aft_len = self->size + other->size;
            if (aft_len > self->capacity)//如果追加后长度大于当前容量,先扩容
            {
                if (!btry_scale(self, aft_len + DEF_CPT))
                {
                    return false;
                }
            }
            memcpy(self->dt+self->size,other->dt,other->size);
            self->size=aft_len;
            return true;
        }
    }
    return false;
}

void btry_free(struct byte_array *buf)
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

uint8_t *str_trim(const char *str)
{
    int64_t str_len = strlen(str);
    uint8_t *rt = (uint8_t *)malloc(str_len);
    if (rt == NULL)
    {
        return NULL;
    }
    int64_t j = 0;
    for (int64_t i = 0; i < str_len; i++)
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

struct byte_array *hexstrTohex_ary(const char *hex_str_)
{
    uint8_t *hex_str = str_trim(hex_str_);
    int64_t str_len = strlen(hex_str);
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
    for (int64_t i = 0; i < str_len; i++)
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

int64_t btry_indexof_hex(struct byte_array *self, int64_t index, const char *pattern)
{
    struct byte_array *hexs = hexstrTohex_ary(pattern);
    int64_t rt = -1;

    if (index > self->size)
    {
        index = 0;
    }
    int64_t hex_len = hexs->size;
    int64_t j = 0;
    // BF算法 暴力匹配
    for (int64_t i = index; i < (self->size - hex_len); i++)
    {
        for (j = 0; j < hex_len; j++)
        {
            if (self->dt[i + j] != hexs->dt[j])
            {
                break;
            }
        }
        if (j == hex_len)
        {
            rt = i;
            break;
        }
    }
    btry_free(hexs);
    hexs = NULL;
    return rt;
}