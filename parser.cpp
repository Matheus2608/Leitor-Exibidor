#include "parser.hpp"
#include <iostream>
using namespace std;

// gere um Leitor que vai ser uma variavel privada da classe Parser, e use ele para ler os dados do arquivo .class
Parser::Parser(const string &filename) : classInfo(), leitor(filename) {}

Parser::~Parser() = default;

class_info Parser::parse()
{
    magicCheck();
    minorVersionCheck();
    majorVersionCheck();
    constantPoolCountCheck();
    constantPoolCheck();
    return classInfo;
}

void Parser::magicCheck()
{
    u4 magic = leitor.readu4();
    if (!(magic == 0xCAFEBABE))
    {
        // throw error
        cout << "Arquivo Java invalido! Magic number incorreto." << endl;
        cout << "Valor lido: 0x" << hex << magic << dec << endl;
        throw std::runtime_error("Arquivo Java invalido!");
    }

    cout << "Arquivo Java valido!" << endl;

    classInfo.magic_number = magic;
}

void Parser::minorVersionCheck()
{
    u2 minor_version = leitor.readu2();
    classInfo.minor_version = minor_version;
}

void Parser::majorVersionCheck()
{
    u2 major_version = leitor.readu2();
    classInfo.major_version = major_version;
}

void Parser::constantPoolCountCheck()
{
    u2 constant_pool_count = leitor.readu2();
    classInfo.constant_pool_count = constant_pool_count;
}

void Parser::constantPoolCheck()
{
    classInfo.constant_pool = new cp_info[classInfo.constant_pool_count];
    for (u2 i = 1; i < classInfo.constant_pool_count; ++i)
    {
        classInfo.constant_pool[i].tag = leitor.readu1();
        switch (classInfo.constant_pool[i].tag)
        {
        case CONSTANT_Class:
            classInfo.constant_pool[i].container.Class.name_index = leitor.readu2();
            break;
        case CONSTANT_Fieldref:
        case CONSTANT_Methodref:
        case CONSTANT_InterfaceMethodref:
            classInfo.constant_pool[i].container.Fieldref.class_index = leitor.readu2();
            classInfo.constant_pool[i].container.Fieldref.name_and_type_index = leitor.readu2();
            break;
        case CONSTANT_String:
            classInfo.constant_pool[i].container.String.string_index = leitor.readu2();
            break;
        case CONSTANT_Integer:
        case CONSTANT_Float:
            classInfo.constant_pool[i].container.Integer.bytes = leitor.readu4();
            break;
        case CONSTANT_Long:
        case CONSTANT_Double:
            classInfo.constant_pool[i].container.Long.high_bytes = leitor.readu4();
            classInfo.constant_pool[i].container.Long.low_bytes = leitor.readu4();
            i++; // Long e Double ocupam duas entradas
            break;
        case CONSTANT_NameAndType:
            classInfo.constant_pool[i].container.NameAndType.name_index = leitor.readu2();
            classInfo.constant_pool[i].container.NameAndType.descriptor_index = leitor.readu2();
            break;
        case CONSTANT_Utf8:
        {
            u2 length = leitor.readu2();
            classInfo.constant_pool[i].container.Utf8.length = length;
            classInfo.constant_pool[i].container.Utf8.bytes = new uint8_t[length];
            leitor.read(classInfo.constant_pool[i].container.Utf8.bytes, length);
            break;
        }
        }
    }
}