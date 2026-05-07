#ifndef ESTRUTURA_DADOS_HPP
#define ESTRUTURA_DADOS_HPP
#include <cstdint>

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;

struct cp_info {
    u1 tag;
    union {
        struct { u2 name_index; } Class;
        struct { u2 class_index; u2 name_and_type_index; } Fieldref, Methodref, InterfaceMethodref;
        struct { u2 string_index; } String;
        struct { u4 bytes; } Integer, Float;
        struct { u4 high_bytes; u4 low_bytes; } Long, Double;
        struct { u2 name_index; u2 descriptor_index; } NameAndType;
        struct { u2 length; uint8_t *bytes; } Utf8;
    } container;
};

struct attribute_info {
    u2 attribute_name_index;
    u4 attribute_length;
    uint8_t* info;
};

struct field_info {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info* attributes;
};

struct method_info {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info* attributes;
};

struct class_info {
    u4 magic_number;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    cp_info* constant_pool;
    u2 access_flags;
    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    u2* interfaces;
    u2 fields_count;
    field_info* fields;
    u2 methods_count;
    method_info* methods;
    u2 attributes_count;
    attribute_info* attributes;
};

#endif // ESTRUTURA_DADOS_HPP

