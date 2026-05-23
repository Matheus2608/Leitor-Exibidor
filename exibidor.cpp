#include "exibidor.hpp"
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <cstring>

namespace
{
    std::string utf8FromConstantPool(const class_info &info, u2 index)
    {
        if (index == 0 || index >= info.constant_pool.size())
        {
            throw std::runtime_error("Exibidor: indice invalido na constant pool");
        }

        const cp_info &entry = info.constant_pool[index];
        if (entry.tag != CONSTANT_Utf8)
        {
            throw std::runtime_error("Exibidor: entrada da constant pool nao e Utf8");
        }

        const auto &utf8 = entry.container.Utf8;
        if (utf8.length == 0)
        {
            return "";
        }

        if (utf8.bytes == nullptr)
        {
            throw std::runtime_error("Exibidor: bytes Utf8 nulos");
        }

        return std::string(reinterpret_cast<const char *>(utf8.bytes), utf8.length);
    }

    std::string classNameFromConstantPool(const class_info &info, u2 index)
    {
        if (index == 0 || index >= info.constant_pool.size())
        {
            throw std::runtime_error("Exibidor: indice invalido de classe na constant pool");
        }

        const cp_info &entry = info.constant_pool[index];
        if (entry.tag != CONSTANT_Class)
        {
            throw std::runtime_error("Exibidor: entrada da constant pool nao e Class");
        }

        return utf8FromConstantPool(info, entry.container.Class.name_index);
    }

    std::string parseTypeDescriptor(const std::string &descriptor, size_t &position)
    {
        size_t arrayDimensions = 0;
        while (position < descriptor.size() && descriptor[position] == '[')
        {
            ++arrayDimensions;
            ++position;
        }

        if (position >= descriptor.size())
        {
            throw std::runtime_error("Exibidor: descriptor invalido");
        }

        std::string baseType;
        char current = descriptor[position++];
        switch (current)
        {
        case 'B':
            baseType = "byte";
            break;
        case 'C':
            baseType = "char";
            break;
        case 'D':
            baseType = "double";
            break;
        case 'F':
            baseType = "float";
            break;
        case 'I':
            baseType = "int";
            break;
        case 'J':
            baseType = "long";
            break;
        case 'S':
            baseType = "short";
            break;
        case 'Z':
            baseType = "boolean";
            break;
        case 'V':
            baseType = "void";
            break;
        case 'L':
        {
            size_t end = descriptor.find(';', position);
            if (end == std::string::npos)
            {
                throw std::runtime_error("Exibidor: descriptor de referencia invalido");
            }
            baseType = descriptor.substr(position, end - position);
            position = end + 1;
            break;
        }
        default:
            throw std::runtime_error("Exibidor: tipo de descriptor desconhecido");
        }

        for (size_t i = 0; i < arrayDimensions; ++i)
        {
            baseType += "[]";
        }

        return baseType;
    }

    std::string formatMethodParameters(const std::string &descriptor)
    {
        size_t openParen = descriptor.find('(');
        size_t closeParen = descriptor.find(')');
        if (openParen == std::string::npos || closeParen == std::string::npos || closeParen < openParen)
        {
            throw std::runtime_error("Exibidor: assinatura de metodo invalida");
        }

        std::string result;
        size_t position = openParen + 1;
        bool first = true;

        while (position < closeParen)
        {
            std::string type = parseTypeDescriptor(descriptor, position);

            if (!first)
            {
                result += ", ";
            }
            result += type;
            first = false;
        }

        return result;
    }

    std::string formatMethodReturnType(const std::string &descriptor)
    {
        size_t closeParen = descriptor.find(')');
        if (closeParen == std::string::npos || closeParen + 1 >= descriptor.size())
        {
            throw std::runtime_error("Exibidor: tipo de retorno invalido");
        }

        size_t position = closeParen + 1;
        return parseTypeDescriptor(descriptor, position);
    }

    std::string formatFieldType(const std::string &descriptor)
    {
        size_t position = 0;
        std::string type = parseTypeDescriptor(descriptor, position);
        if (position != descriptor.size())
        {
            throw std::runtime_error("Exibidor: descriptor de campo invalido");
        }

        return type;
    }

    std::string nameAndTypeStr(const class_info &info, u2 index)
    {
        if (index == 0 || index >= info.constant_pool.size()) return "";
        const cp_info &entry = info.constant_pool[index];
        if (entry.tag != CONSTANT_NameAndType) return "";
        return utf8FromConstantPool(info, entry.container.NameAndType.name_index) + ":" +
               utf8FromConstantPool(info, entry.container.NameAndType.descriptor_index);
    }

    // Retorna string legível para qualquer entrada do pool — usada como comentário "// ..."
    std::string cpEntryComment(const class_info &info, u2 index)
    {
        if (index == 0 || index >= info.constant_pool.size()) return "";
        const cp_info &entry = info.constant_pool[index];
        switch (entry.tag) {
        case CONSTANT_Class:
            return utf8FromConstantPool(info, entry.container.Class.name_index);
        case CONSTANT_Fieldref:
        case CONSTANT_Methodref:
        case CONSTANT_InterfaceMethodref:
            return classNameFromConstantPool(info, entry.container.Fieldref.class_index) + "." +
                   nameAndTypeStr(info, entry.container.Fieldref.name_and_type_index);
        case CONSTANT_String:
            return utf8FromConstantPool(info, entry.container.String.string_index);
        case CONSTANT_NameAndType:
            return nameAndTypeStr(info, index);
        case CONSTANT_MethodType:
            return utf8FromConstantPool(info, entry.container.MethodType.descriptor_index);
        default:
            return "";
        }
    }
}

using namespace std;

Exibidor::Exibidor(const std::string &filename) : filename(filename) {}

Exibidor::~Exibidor() = default;

void Exibidor::display()
{
    cout << "Exibindo informações do arquivo " << filename << endl;
    // deve pegar o class info do leitor
    Parser parser(filename);
    classInfo = parser.parse();

    // Informacoes Gerais
    cout << "------------------------------------------------------" << endl;
    cout << " Informações Gerais" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "Magic Number: 0x" << hex << classInfo.magic_number << dec << endl;
    cout << "Minor Version: " << classInfo.minor_version << endl;
    cout << "Major Version: " << classInfo.major_version << endl;
    cout << "Access Flags: 0x" << hex << classInfo.access_flags << dec << endl;
    cout << "This Class Index: " << classInfo.this_class << endl;
    cout << "Super Class Index: " << classInfo.super_class << endl;
    cout << "Interfaces Count: " << classInfo.interfaces_count << endl;
    cout << "Fields Count: " << classInfo.fields_count << endl;
    cout << "Constant Pool Count: " << classInfo.constant_pool_count << endl;
    cout << "Attributes Count: " << classInfo.attributes_count << endl;
    cout << "Methods Count: " << classInfo.methods_count << endl;
    cout << "------------------------------------------------" << endl;
    constantPoolDisplay();
    methodsDisplay();
    fieldsDisplay();
}

void Exibidor::constantPoolDisplay()
{
    using namespace std;

    cout << "------------------------------------------------------" << endl;
    cout << " Constant Pool (" << classInfo.constant_pool_count - 1 << " entradas)" << endl;
    cout << "------------------------------------------------------" << endl;

    for (u2 i = 1; i < classInfo.constant_pool_count; ++i) {
        const cp_info &entry = classInfo.constant_pool[i];

        // Slot vazio: segundo slot de Long/Double
        if (entry.tag == 0) continue;

        cout << "  #" << left << setw(4) << i << " = ";

        string comment = cpEntryComment(classInfo, i);

        switch (entry.tag) {
        case CONSTANT_Class:
            cout << left << setw(19) << "Class"
                 << " #" << entry.container.Class.name_index;
            break;
        case CONSTANT_Fieldref:
            cout << left << setw(19) << "Fieldref"
                 << " #" << entry.container.Fieldref.class_index
                 << ".#" << entry.container.Fieldref.name_and_type_index;
            break;
        case CONSTANT_Methodref:
            cout << left << setw(19) << "Methodref"
                 << " #" << entry.container.Methodref.class_index
                 << ".#" << entry.container.Methodref.name_and_type_index;
            break;
        case CONSTANT_InterfaceMethodref:
            cout << left << setw(19) << "InterfaceMethodref"
                 << " #" << entry.container.InterfaceMethodref.class_index
                 << ".#" << entry.container.InterfaceMethodref.name_and_type_index;
            break;
        case CONSTANT_String:
            cout << left << setw(19) << "String"
                 << " #" << entry.container.String.string_index;
            break;
        case CONSTANT_Integer: {
            int32_t val = static_cast<int32_t>(entry.container.Integer.bytes);
            cout << left << setw(19) << "Integer" << " " << val;
            comment = to_string(val);
            break;
        }
        case CONSTANT_Float: {
            float val;
            u4 bits = entry.container.Float.bytes;
            memcpy(&val, &bits, sizeof(float));
            cout << left << setw(19) << "Float" << " " << val << "f";
            comment = to_string(val) + "f";
            break;
        }
        case CONSTANT_Long: {
            int64_t val = (int64_t)(((uint64_t)entry.container.Long.high_bytes << 32)
                                    | entry.container.Long.low_bytes);
            cout << left << setw(19) << "Long" << " " << val << "l";
            comment = to_string(val) + "l";
            break;
        }
        case CONSTANT_Double: {
            uint64_t bits = ((uint64_t)entry.container.Double.high_bytes << 32)
                            | entry.container.Double.low_bytes;
            double val;
            memcpy(&val, &bits, sizeof(double));
            cout << left << setw(19) << "Double" << " " << val;
            comment = to_string(val);
            break;
        }
        case CONSTANT_NameAndType:
            cout << left << setw(19) << "NameAndType"
                 << " #" << entry.container.NameAndType.name_index
                 << ".#" << entry.container.NameAndType.descriptor_index;
            break;
        case CONSTANT_Utf8:
            cout << left << setw(19) << "Utf8" << " "
                 << string(reinterpret_cast<const char *>(entry.container.Utf8.bytes),
                            entry.container.Utf8.length);
            break;
        case CONSTANT_MethodHandle:
            cout << left << setw(19) << "MethodHandle"
                 << " " << static_cast<int>(entry.container.MethodHandle.reference_kind)
                 << " #" << entry.container.MethodHandle.reference_index;
            break;
        case CONSTANT_MethodType:
            cout << left << setw(19) << "MethodType"
                 << " #" << entry.container.MethodType.descriptor_index;
            break;
        case CONSTANT_InvokeDynamic:
            cout << left << setw(19) << "InvokeDynamic"
                 << " #" << entry.container.InvokeDynamic.bootstrap_method_attr_index
                 << ".#" << entry.container.InvokeDynamic.name_and_type_index;
            break;
        default:
            cout << "Unknown (tag=" << static_cast<int>(entry.tag) << ")";
            break;
        }

        if (!comment.empty()) {
            cout << "   // " << comment;
        }
        cout << "\n";
    }
}

void Exibidor::fieldsDisplay()
{
    cout << "Campos:" << endl;
    for (u2 i = 0; i < classInfo.fields_count; ++i)
    {
        field_info field = classInfo.fields.at(i);
        cout << getAccessFlagsString(field.access_flags) << " " << formatFieldType(utf8FromConstantPool(classInfo, field.descriptor_index)) << " "
             << utf8FromConstantPool(classInfo, field.name_index) << endl;
        // cout << "Field " << i + 1 << ":" << endl;
        // cout << "  Access Flags: 0x" << hex << field.access_flags << dec << endl;
        // cout << "  Acess flags string: " <<  << endl;
        // cout << "  Name: " << utf8FromConstantPool(classInfo, field.name_index) << endl;
        // cout << "  Descriptor: " << utf8FromConstantPool(classInfo, field.descriptor_index) << endl;
        // cout << "  Attributes Count: " << field.attributes_count << endl;
    }
}

void Exibidor::methodsDisplay()
{
    for (u2 i = 0; i < classInfo.methods_count; ++i)
    {
        method_info method = classInfo.methods.at(i);
        cout << "Method " << i + 1 << ":" << endl;
        // cout << "  Access Flags: 0x" << hex << method.access_flags << dec << endl;
        // cout << "  Acess flags string: " << getAccessFlagsString(method.access_flags) << endl;
        // cout << "  Name: " << utf8FromConstantPool(classInfo, method.name_index) << endl;
        // cout << "  Descriptor: " << utf8FromConstantPool(classInfo, method.descriptor_index) << endl;
        // cout << "  Attributes Count: " << method.attributes_count << endl;

        std::pair<string, string> signature = getMethodSignature(method);
        string methodName = utf8FromConstantPool(classInfo, method.name_index);
        if (methodName == "<clinit>")
        {
            cout << "  Assinatura: " << "static { " << getAccessFlagsString(method.access_flags) << " " << signature.first << " "
                 << methodName << "(" << signature.second << ")" << " }" << endl;
            continue;
        }

        if (methodName == "<init>")
        {
            methodName = classNameFromConstantPool(classInfo, classInfo.this_class);
        }

        cout << "  Assinatura: " << getAccessFlagsString(method.access_flags) << " " << signature.first << " "
             << methodName << "(" << signature.second << ")" << endl;
    }

    cout << "-----------------------------------------------" << endl;
}

std::pair<string, string> Exibidor::getMethodSignature(const method_info &method)
{
    string descriptor = utf8FromConstantPool(classInfo, method.descriptor_index);
    return {formatMethodReturnType(descriptor), formatMethodParameters(descriptor)};
}

void Exibidor::attributesDisplay()
{
    // TODO
}