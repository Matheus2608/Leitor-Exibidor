#ifndef BYTECODE_UTILS_HPP
#define BYTECODE_UTILS_HPP

#include <vector>
#include <cstdint>
#include "estrutura_dados.hpp"

inline int16_t readS2(const std::vector<u1> &c, size_t i)
{
    return static_cast<int16_t>((static_cast<uint16_t>(c[i]) << 8) | c[i + 1]);
}

inline int32_t readS4(const std::vector<u1> &c, size_t i)
{
    return static_cast<int32_t>(
        (static_cast<uint32_t>(c[i])     << 24) |
        (static_cast<uint32_t>(c[i + 1]) << 16) |
        (static_cast<uint32_t>(c[i + 2]) <<  8) |
         static_cast<uint32_t>(c[i + 3]));
}

inline uint16_t readU2(const std::vector<u1> &c, size_t i)
{
    return static_cast<uint16_t>((static_cast<uint16_t>(c[i]) << 8) | c[i + 1]);
}

#endif // BYTECODE_UTILS_HPP
