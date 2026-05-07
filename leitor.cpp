#include "leitor.hpp"
#include <iostream>
#include "constants.hpp"

using namespace std;

Leitor::Leitor(const string &filename) : filename(filename), file(filename, ios::binary) {}

Leitor::~Leitor() = default;

void Leitor::read()
{
    cout << "lendo arquivo " << filename << endl;
    if (!file)
    {
        cout << "Nao foi possivel abrir o arquivo." << endl;
        return;
    }

    magicCheck();
    minorVersionCheck();
    majorVersionCheck();
    constantPoolCountCheck();
    constantPoolCheck();
}

u2 Leitor::toBigEndian(u2 value)
{
    return (value >> 8) | (value << 8);
}

u4 Leitor::toBigEndian(u4 value)
{
    return ((value >> 24) & 0x000000FF) |
           ((value >> 8) & 0x0000FF00) |
           ((value << 8) & 0x00FF0000) |
           ((value << 24) & 0xFF000000);
}

u4 Leitor::readu4()
{
    u1 buffer[4];
    file.read(reinterpret_cast<char *>(buffer), 4);
    return (static_cast<u4>(buffer[0]) << 24) |
           (static_cast<u4>(buffer[1]) << 16) |
           (static_cast<u4>(buffer[2]) << 8) |
           static_cast<u4>(buffer[3]);
}

u2 Leitor::readu2()
{
    u1 buffer[2];
    file.read(reinterpret_cast<char *>(buffer), 2);
    return (static_cast<u2>(buffer[0]) << 8) |
           static_cast<u2>(buffer[1]);
}

u1 Leitor::readu1()
{
    u1 buffer[1];
    file.read(reinterpret_cast<char *>(buffer), 1);
    return buffer[0];
}

void Leitor::magicCheck()
{
    u4 magic = readu4();
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

void Leitor::minorVersionCheck()
{
    u2 minor_version = readu2();
    classInfo.minor_version = minor_version;
}

void Leitor::majorVersionCheck()
{
    u2 major_version = readu2();
    classInfo.major_version = major_version;
}

void Leitor::constantPoolCountCheck()
{
    u2 constant_pool_count = readu2();
    classInfo.constant_pool_count = constant_pool_count;
}

void Leitor::constantPoolCheck()
{
    classInfo.constant_pool = new cp_info[classInfo.constant_pool_count];
    for (u2 i = 1; i < classInfo.constant_pool_count; ++i)
    {
        classInfo.constant_pool[i].tag = readu1();
        switch (classInfo.constant_pool[i].tag)
        {
        case CONSTANT_Class:
            classInfo.constant_pool[i].container.Class.name_index = readu2();
            break;
        case CONSTANT_Fieldref:
        case CONSTANT_Methodref:
        case CONSTANT_InterfaceMethodref:
            classInfo.constant_pool[i].container.Fieldref.class_index = readu2();
            classInfo.constant_pool[i].container.Fieldref.name_and_type_index = readu2();
            break;
        case CONSTANT_String:
            classInfo.constant_pool[i].container.String.string_index = readu2();
            break;
        case CONSTANT_Integer:
        case CONSTANT_Float:
            classInfo.constant_pool[i].container.Integer.bytes = readu4();
            break;
        case CONSTANT_Long:
        case CONSTANT_Double:
            classInfo.constant_pool[i].container.Long.high_bytes = readu4();
            classInfo.constant_pool[i].container.Long.low_bytes = readu4();
            i++; // Long e Double ocupam duas entradas
            break;
        case CONSTANT_NameAndType:
            classInfo.constant_pool[i].container.NameAndType.name_index = readu2();
            classInfo.constant_pool[i].container.NameAndType.descriptor_index = readu2();
            break;
        case CONSTANT_Utf8:
        {
            u2 length = readu2();
            classInfo.constant_pool[i].container.Utf8.length = length;
            classInfo.constant_pool[i].container.Utf8.bytes = new uint8_t[length];
            file.read(reinterpret_cast<char *>(classInfo.constant_pool[i].container.Utf8.bytes), length);
            break;
        }
        }
    }
}
