#include "parser.hpp"

#include <iostream>
#include <stdexcept>

using namespace std;

Parser::Parser(const string &filename) : classInfo(), leitor(filename) {}

Parser::~Parser() = default;

class_info Parser::parse()
{
    magicCheck();
    minorVersionCheck();
    majorVersionCheck();
    constantPoolCountCheck();
    constantPoolCheck();
    acessFlagsCheck();
    thisClassCheck();
    superClassCheck();
    interfacesCountCheck();
    interfacesCheck();
    fieldsCountCheck();
    fieldsCheck();
    methodsCountCheck();
    methodsCheck();
    attributesCountCheck();
    attributesCheck();
    return classInfo;
}

void Parser::magicCheck()
{
    u4 magic = leitor.readu4();
    if (magic != 0xCAFEBABE)
    {
        cout << "Arquivo Java invalido! Magic number incorreto." << endl;
        cout << "Valor lido: 0x" << hex << magic << dec << endl;
        throw runtime_error("Arquivo Java invalido!");
    }

    cout << "Arquivo Java valido!" << endl;
    classInfo.magic_number = magic;
}

void Parser::minorVersionCheck()
{
    classInfo.minor_version = leitor.readu2();
}

void Parser::majorVersionCheck()
{
    classInfo.major_version = leitor.readu2();
}

void Parser::constantPoolCountCheck()
{
    classInfo.constant_pool_count = leitor.readu2();
}

void Parser::constantPoolCheck()
{
    classInfo.constant_pool.resize(classInfo.constant_pool_count);

    for (u2 i = 1; i < classInfo.constant_pool_count; ++i)
    {
        cp_info &entry = classInfo.constant_pool[i];
        entry.tag = leitor.readu1();

        switch (entry.tag)
        {
        case CONSTANT_Class:
            entry.container.Class.name_index = leitor.readu2();
            break;
        case CONSTANT_Fieldref:
        case CONSTANT_Methodref:
        case CONSTANT_InterfaceMethodref:
            entry.container.Fieldref.class_index = leitor.readu2();
            entry.container.Fieldref.name_and_type_index = leitor.readu2();
            break;
        case CONSTANT_String:
            entry.container.String.string_index = leitor.readu2();
            break;
        case CONSTANT_Integer:
        case CONSTANT_Float:
            entry.container.Integer.bytes = leitor.readu4();
            break;
        case CONSTANT_Long:
        case CONSTANT_Double:
            entry.container.Long.high_bytes = leitor.readu4();
            entry.container.Long.low_bytes = leitor.readu4();
            ++i;
            break;
        case CONSTANT_MethodHandle:
            entry.container.MethodHandle.reference_kind = leitor.readu1();
            entry.container.MethodHandle.reference_index = leitor.readu2();
            break;
        case CONSTANT_MethodType:
            entry.container.MethodType.descriptor_index = leitor.readu2();
            break;
        case CONSTANT_InvokeDynamic:
            entry.container.InvokeDynamic.bootstrap_method_attr_index = leitor.readu2();
            entry.container.InvokeDynamic.name_and_type_index = leitor.readu2();
            break;
        case CONSTANT_NameAndType:
            entry.container.NameAndType.name_index = leitor.readu2();
            entry.container.NameAndType.descriptor_index = leitor.readu2();
            break;
        case CONSTANT_Utf8:
        {
            u2 length = leitor.readu2();
            entry.container.Utf8.length = length;
            entry.container.Utf8.bytes = new uint8_t[length];
            leitor.read(entry.container.Utf8.bytes, length);
            break;
        }
        default:
            throw runtime_error("Parser: constante da constant pool nao suportada: tag=" + to_string(entry.tag));
        }
    }
}

void Parser::acessFlagsCheck()
{
    classInfo.access_flags = leitor.readu2();
}

void Parser::thisClassCheck()
{
    classInfo.this_class = leitor.readu2();
}

void Parser::superClassCheck()
{
    classInfo.super_class = leitor.readu2();
}

void Parser::interfacesCountCheck()
{
    classInfo.interfaces_count = leitor.readu2();
}

void Parser::interfacesCheck()
{
    classInfo.interfaces.resize(classInfo.interfaces_count);
    for (u2 i = 0; i < classInfo.interfaces_count; ++i)
    {
        classInfo.interfaces[i] = leitor.readu2();
    }
}

void Parser::fieldsCountCheck()
{
    classInfo.fields_count = leitor.readu2();
}

void Parser::fieldsCheck()
{
    classInfo.fields.resize(classInfo.fields_count);
    for (u2 i = 0; i < classInfo.fields_count; ++i)
    {
        field_info &field = classInfo.fields[i];
        field.access_flags = leitor.readu2();
        field.name_index = leitor.readu2();
        field.descriptor_index = leitor.readu2();
        field.attributes_count = leitor.readu2();
        field.attributes.resize(field.attributes_count);

        for (u2 j = 0; j < field.attributes_count; ++j)
        {
            attribute_info &attribute = field.attributes[j];
            attribute.attribute_name_index = leitor.readu2();
            attribute.attribute_length = leitor.readu4();
            attribute.info = leitor.read_bytes(attribute.attribute_length);
        }
    }
}

void Parser::methodsCountCheck()
{
    classInfo.methods_count = leitor.readu2();
}

void Parser::methodsCheck()
{
    classInfo.methods.resize(classInfo.methods_count);
    for (u2 i = 0; i < classInfo.methods_count; ++i)
    {
        method_info &method = classInfo.methods[i];
        method.access_flags = leitor.readu2();
        method.name_index = leitor.readu2();
        method.descriptor_index = leitor.readu2();
        method.attributes_count = leitor.readu2();
        method.attributes.resize(method.attributes_count);

        for (u2 j = 0; j < method.attributes_count; ++j)
        {
            attribute_info &attribute = method.attributes[j];
            attribute.attribute_name_index = leitor.readu2();
            attribute.attribute_length = leitor.readu4();
            attribute.info = leitor.read_bytes(attribute.attribute_length);
        }
    }
}

void Parser::attributesCountCheck()
{
    classInfo.attributes_count = leitor.readu2();
}

void Parser::attributesCheck()
{
    classInfo.attributes.resize(classInfo.attributes_count);
    for (u2 i = 0; i < classInfo.attributes_count; ++i)
    {
        attribute_info &attribute = classInfo.attributes[i];
        attribute.attribute_name_index = leitor.readu2();
        attribute.attribute_length = leitor.readu4();
        attribute.info = leitor.read_bytes(attribute.attribute_length);
    }
}