#include "exibidor.hpp"
#include "leitor.hpp"
#include <iostream>
#include "constants.hpp"

using namespace std;

Exibidor::Exibidor(const std::string &filename) : filename(filename) {}

Exibidor::~Exibidor() = default;

void Exibidor::display()
{
    cout << "Exibindo informações do arquivo " << filename << endl;
    // deve pegar o class info do leitor
    Leitor leitor(filename);
    leitor.read();
    class_info info = leitor.getClassInfo();
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
    // TODO
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