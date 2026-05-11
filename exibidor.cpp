#include "exibidor.hpp"
#include <iostream>

using namespace std;

Exibidor::Exibidor(const std::string &filename) : filename(filename) {}

Exibidor::~Exibidor() = default;

void Exibidor::display()
{
    cout << "Exibindo informações do arquivo " << filename << endl;
    // deve pegar o class info do leitor
    Parser parser(filename);
    class_info info = parser.parse();
    
    // Exibir informações da classe
    cout << "Magic Number: 0x" << hex << info.magic_number << dec << endl;
    cout << "Minor Version: " << info.minor_version << endl;
    cout << "Major Version: " << info.major_version << endl;
    cout << "Constant Pool Count: " << info.constant_pool_count << endl;
    constantPoolDisplay();

    // o resto só faz sentido se o constant pool for exibido, então deixo para depois 


    // cout << "Access Flags: 0x" << hex << info.access_flags << dec << endl;
    // cout << "This Class Index: " << info.this_class << endl;
    // cout << "Super Class Index: " << info.super_class << endl;
    // cout << "Interfaces Count: " << info.interfaces_count << endl;
    // cout << "Fields Count: " << info.fields_count << endl;
    // fieldsDisplay();
    // cout << "Methods Count: " << info.methods_count << endl;
    // methodsDisplay();
    // cout << "Attributes Count: " << info.attributes_count << endl;
    // attributesDisplay();
}

void Exibidor::constantPoolDisplay() {
     // Exibir informações do constant pool
    // for (u2 i = 1; i < info.constant_pool_count; ++i)
    // {
    //     cout << "Constant Pool [" << i << "]: Tag = " << (int)info.constant_pool[i].tag << endl;
    //     // Exibir detalhes específicos de cada tipo de constante
    //     switch (info.constant_pool[i].tag)
    //     {
    //     case CONSTANT_Class:
    //         cout << "  Class Name Index: " << info.constant_pool[i].container.Class.name_index << endl;
    //         break;
    //     case CONSTANT_Fieldref:
    //     case CONSTANT_Methodref:
    //     case CONSTANT_InterfaceMethodref:
    //         cout << "  Class Index: " << info.constant_pool[i].container.Fieldref.class_index << endl;
    //         cout << "  Name and Type Index: " << info.constant_pool[i].container.Fieldref.name_and_type_index << endl;
    //         break;
    //     case CONSTANT_String:
    //         cout << "  String Index: " << info.constant_pool[i].container.String.string_index << endl;
    //         break;
    //     case CONSTANT_Integer:
    //         cout << "  Integer Bytes: " << info.constant_pool[i].container.Integer.bytes << endl;
    //         break;
    //     case CONSTANT_Float:
    //         cout << "  Float Bytes: " << info.constant_pool[i].container.Float.bytes << endl;
    //         break;
    //     case CONSTANT_Long:
    //         cout << "  Long High Bytes: " << info.constant_pool[i].container.Long.high_bytes << endl;
    //         cout << "  Long Low Bytes: " << info.constant_pool[i].container.Long.low_bytes << endl;
    //         break;
    //     case CONSTANT_Double:
    //         cout << "  Double High Bytes: " << info.constant_pool[i].container.Double.high_bytes << endl;
    //         cout << "  Double Low Bytes: " << info.constant_pool[i].container.Double.low_bytes << endl;
    //         break;
    //     case CONSTANT_NameAndType:
    //         cout << "  Name Index: " << info.constant_pool[i].container.NameAndType.name_index << endl;
    //         cout << "  Descriptor Index: " << info.constant_pool[i].container.NameAndType.descriptor_index << endl;
    //         break;
    //     case CONSTANT_Utf8:
    //         cout << "  Utf8 Length: " << info.constant_pool[i].container.Utf8.length << endl;
    //         // Exibir os bytes como string (assumindo que são caracteres UTF-8)
    //         cout.write(reinterpret_cast<char *>(info.constant_pool[i].container.Utf8.bytes), info.constant_pool[i].container.Utf8.length);
    //         cout << endl;
    //         break;
    //         // ... outras tags menos comuns (MethodHandle, etc) --- IGNORE --- --- IGNORE ---
    //     }
    // }
}

void Exibidor::fieldsDisplay() {
    // TODO
}

void Exibidor::methodsDisplay() {
    // TODO
}

void Exibidor::attributesDisplay() {
    // TODO
}