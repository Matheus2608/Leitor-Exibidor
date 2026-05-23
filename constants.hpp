#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
#include <cstdint>

#include "estrutura_dados.hpp"

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


// Access Flags (podem ser combinadas com bitwise OR)
enum class ClassAccessFlags : u2 {
    ACC_PUBLIC     = 0x0001,
    ACC_FINAL      = 0x0010,
    ACC_SUPER      = 0x0020,
    ACC_INTERFACE  = 0x0200,
    ACC_ABSTRACT   = 0x0400,
    ACC_SYNTHETIC  = 0x1000,
    ACC_ANNOTATION = 0x2000,
    ACC_ENUM       = 0x4000
};

enum class MethodAccessFlags : u2 {
    ACC_PUBLIC       = 0x0001,
    ACC_PRIVATE      = 0x0002,
    ACC_PROTECTED    = 0x0004,
    ACC_STATIC       = 0x0008,
    ACC_FINAL        = 0x0010,
    ACC_SYNCHRONIZED = 0x0020,
    ACC_BRIDGE       = 0x0040,
    ACC_VARARGS      = 0x0080,
    ACC_NATIVE       = 0x0100,
    ACC_ABSTRACT     = 0x0400,
    ACC_STRICT       = 0x0800,
    ACC_SYNTHETIC    = 0x1000
};

enum class FieldAccessFlags : u2 {
    ACC_PUBLIC     = 0x0001,
    ACC_PRIVATE    = 0x0002,
    ACC_PROTECTED  = 0x0004,
    ACC_STATIC     = 0x0008,
    ACC_FINAL      = 0x0010,
    ACC_VOLATILE   = 0x0040,
    ACC_TRANSIENT  = 0x0080,
    ACC_SYNTHETIC  = 0x1000,
    ACC_ENUM       = 0x4000
};

template <typename FlagEnum>
inline bool hasAccessFlag(u2 flags, FlagEnum flag) {
    return (flags & static_cast<u2>(flag)) != 0;
}

inline std::string finalizeAccessFlagsString(std::string result) {
    if (!result.empty()) {
        result.pop_back();
    }

    if (result.empty()) {
        return "package-private";
    }

    return result;
}

inline std::string getClassAccessFlagsString(u2 flags) {
    std::string result;

    if (hasAccessFlag(flags, ClassAccessFlags::ACC_PUBLIC))    result += "public ";
    if (hasAccessFlag(flags, ClassAccessFlags::ACC_FINAL))     result += "final ";
    if (hasAccessFlag(flags, ClassAccessFlags::ACC_SUPER))     result += "super ";
    if (hasAccessFlag(flags, ClassAccessFlags::ACC_INTERFACE)) result += "interface ";
    if (hasAccessFlag(flags, ClassAccessFlags::ACC_ABSTRACT))  result += "abstract ";
    if (hasAccessFlag(flags, ClassAccessFlags::ACC_SYNTHETIC)) result += "synthetic ";
    if (hasAccessFlag(flags, ClassAccessFlags::ACC_ANNOTATION))result += "annotation ";
    if (hasAccessFlag(flags, ClassAccessFlags::ACC_ENUM))      result += "enum ";

    return finalizeAccessFlagsString(result);
}

inline std::string getMethodAccessFlagsString(u2 flags) {
    std::string result;

    if (hasAccessFlag(flags, MethodAccessFlags::ACC_PUBLIC))       result += "public ";
    if (hasAccessFlag(flags, MethodAccessFlags::ACC_PRIVATE))      result += "private ";
    if (hasAccessFlag(flags, MethodAccessFlags::ACC_PROTECTED))    result += "protected ";
    if (hasAccessFlag(flags, MethodAccessFlags::ACC_STATIC))       result += "static ";
    if (hasAccessFlag(flags, MethodAccessFlags::ACC_FINAL))        result += "final ";
    if (hasAccessFlag(flags, MethodAccessFlags::ACC_SYNCHRONIZED)) result += "synchronized ";
    if (hasAccessFlag(flags, MethodAccessFlags::ACC_BRIDGE))       result += "bridge ";
    if (hasAccessFlag(flags, MethodAccessFlags::ACC_VARARGS))      result += "varargs ";
    if (hasAccessFlag(flags, MethodAccessFlags::ACC_NATIVE))       result += "native ";
    if (hasAccessFlag(flags, MethodAccessFlags::ACC_ABSTRACT))     result += "abstract ";
    if (hasAccessFlag(flags, MethodAccessFlags::ACC_STRICT))       result += "strictfp ";
    if (hasAccessFlag(flags, MethodAccessFlags::ACC_SYNTHETIC))    result += "synthetic ";

    return finalizeAccessFlagsString(result);
}

inline std::string getFieldAccessFlagsString(u2 flags) {
    std::string result;

    if (hasAccessFlag(flags, FieldAccessFlags::ACC_PUBLIC))    result += "public ";
    if (hasAccessFlag(flags, FieldAccessFlags::ACC_PRIVATE))   result += "private ";
    if (hasAccessFlag(flags, FieldAccessFlags::ACC_PROTECTED)) result += "protected ";
    if (hasAccessFlag(flags, FieldAccessFlags::ACC_STATIC))    result += "static ";
    if (hasAccessFlag(flags, FieldAccessFlags::ACC_FINAL))     result += "final ";
    if (hasAccessFlag(flags, FieldAccessFlags::ACC_VOLATILE))  result += "volatile ";
    if (hasAccessFlag(flags, FieldAccessFlags::ACC_TRANSIENT)) result += "transient ";
    if (hasAccessFlag(flags, FieldAccessFlags::ACC_SYNTHETIC)) result += "synthetic ";
    if (hasAccessFlag(flags, FieldAccessFlags::ACC_ENUM))      result += "enum ";

    return finalizeAccessFlagsString(result);
}

#endif // CONSTANTS_HPP
