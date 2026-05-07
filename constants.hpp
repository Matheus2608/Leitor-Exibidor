#include <string>
#include <cstdint>

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
enum class AccessFlags : uint16_t {
    ACC_PUBLIC      = 0x0001,  // Declarada pública
    ACC_FINAL       = 0x0010,  // Declarada final
    ACC_SUPER       = 0x0020,  // Chama métodos de superclasse
    ACC_INTERFACE   = 0x0200,  // É interface
    ACC_ABSTRACT    = 0x0400,  // Declarada abstrata
    ACC_SYNTHETIC   = 0x1000,  // Não presente no fonte
    ACC_ANNOTATION  = 0x2000,  // Tipo annotation
    ACC_ENUM        = 0x4000   // Tipo enum
};

// Verifica se um flag está ativo em um valor
inline bool hasAccessFlag(u2 flags, AccessFlags flag) {
    return (flags & static_cast<u2>(flag)) != 0;
}

// Converte access flags para string legível
inline std::string getAccessFlagsString(u2 flags) {
    std::string result;
    
    if (hasAccessFlag(flags, AccessFlags::ACC_PUBLIC))    result += "PUBLIC ";
    if (hasAccessFlag(flags, AccessFlags::ACC_FINAL))     result += "FINAL ";
    if (hasAccessFlag(flags, AccessFlags::ACC_SUPER))     result += "SUPER ";
    if (hasAccessFlag(flags, AccessFlags::ACC_INTERFACE)) result += "INTERFACE ";
    if (hasAccessFlag(flags, AccessFlags::ACC_ABSTRACT))  result += "ABSTRACT ";
    if (hasAccessFlag(flags, AccessFlags::ACC_SYNTHETIC)) result += "SYNTHETIC ";
    if (hasAccessFlag(flags, AccessFlags::ACC_ANNOTATION))result += "ANNOTATION ";
    if (hasAccessFlag(flags, AccessFlags::ACC_ENUM))      result += "ENUM ";
    
    // Remove trailing space
    if (!result.empty()) {
        result.pop_back();
    }
    
    return result.empty() ? "[nenhum flag]" : result;
}