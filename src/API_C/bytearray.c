#include "../../include/API_C/bytearray.h"
#include <stdlib.h>
#include <string.h>


DLIB_API_EXPORT struct byte_array *get_btry(uint64_t capacity)
{
    if (capacity > 0)
    {
        struct byte_array *ptr = (struct byte_array *)malloc(sizeof(struct byte_array));
        memset(ptr, 0, sizeof(struct byte_array));
        ptr->dt = (uint8_t *)malloc(capacity);
        if (ptr->dt != NULL)
        {
            ptr->capacity = capacity;
            return ptr;
        }
    }
    return NULL;
}

DLIB_API_EXPORT bool scale_btry(struct byte_array *buf, uint64_t capacity)
{
    if (buf != NULL)
    {
        if (capacity <= buf->capacity)
        {
            return false;
        }
        uint8_t *o_dt = buf->dt; // 用于将旧数据拷贝
        uint8_t *dt_ptr = (uint8_t *)malloc(capacity);
        if (dt_ptr != NULL)
        {
            if (buf->size)
            {
                memcpy(dt_ptr, o_dt, buf->size);
                free(buf->dt);
                buf->dt = dt_ptr;
                buf->capacity=capacity;
                return true;
            }
        }
    }

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