#define CONSTANT_Class              7
#define CONSTANT_Fieldref           9
#define CONSTANT_Methodref          10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String             8
#define CONSTANT_Integer            3
#define CONSTANT_Float              4
#define CONSTANT_Long               5
#define CONSTANT_Double             6
#define CONSTANT_NameAndType        12
#define CONSTANT_Utf8               1
#define CONSTANT_MethodHandle       15
#define CONSTANT_MethodType         16
#define CONSTANT_InvokeDynamic      18

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