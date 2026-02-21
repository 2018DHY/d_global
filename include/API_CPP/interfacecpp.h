#ifndef INTERFACECPP
#define INTERFACECPP
#include "../commom.h"
#include <filesystem>
#include <iostream>
// 目前在windows下使用
#include <stdbool.h>
#include <stdint.h>
#include <string>
#include <vector>

#include <bit>
#include <concepts>
#include <cstdint>
#include <type_traits>

template <std::integral T>
constexpr T dToBigEndian(T value) noexcept {
    if constexpr (std::endian::native == std::endian::big) {
        // 如果系统本身就是大端序，直接返回
        return value;
    } else {
        // 如果是小端序，交换字节
        return std::byteswap(value);
    }
};


template <std::integral T>
constexpr T dFromBigEndian(T big_endian_value) noexcept {
    // 如果当前系统是大端序，big-endian值就是原生值，直接返回
    if constexpr (std::endian::native == std::endian::big) {
        return big_endian_value;
    }
    // 如果是小端序，需要交换字节
    else if constexpr (std::endian::native == std::endian::little) {
        return std::byteswap(big_endian_value);
    }
    // 处理混合字节序的情况（理论上很少见，保持原样）
    else {
        return big_endian_value;
    }
};

void cpp_say_hello();
// void TLog(const std::string &x);

/// @brief 按照slice对文本做分割
/// @param str 待处理的文本
/// @param slice 分隔符
/// @return 
DLIB_API_EXPORT std::vector<std::string> textSplit(const char * str,char slice);

/// @brief 用来对单行文本去除两端的不可见空字符
/// @param str 待处理的单行文本
/// @return 
DLIB_API_EXPORT std::string trim(const std::string &str);

DLIB_API_EXPORT std::vector<std::string> textSplit(const char * str,char slice);
/// @brief 从(char*)from中的offset位置读取len字节数据到rt中
/// @param offset 偏移量
/// @param from 数据源
/// @param len 数据长度(单位char,1字节)
/// @param rt 外部传入的std::string,外部rt管理自身内存
/// @return 
DLIB_API_EXPORT int64_t read_line(int64_t offset, char *from, int64_t len, std::string &rt);

#endif /* INTERFACECPP */
