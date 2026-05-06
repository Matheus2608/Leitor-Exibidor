#ifndef ESTRUTURA_DADOS_HPP
#define ESTRUTURA_DADOS_HPP
#include <cstdint>
#endif // ESTRUTURA_DADOS_HPP

struct cp_info {
    uint8_t tag;
    union {
        struct { uint16_t name_index; } Class;
        struct { uint16_t class_index; uint16_t name_and_type_index; } Fieldref, Methodref, InterfaceMethodref;
        struct { uint16_t string_index; } String;
        struct { uint32_t bytes; } Integer, Float;
        struct { uint32_t high_bytes; uint32_t low_bytes; } Long, Double;
        struct { uint16_t name_index; uint16_t descriptor_index; } NameAndType;
        struct { uint16_t length; uint8_t *bytes; } Utf8;
        // ... outras tags menos comuns (MethodHandle, etc)
    } container;
};

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;