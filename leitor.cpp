#include "leitor.hpp"

#include <iostream>

using namespace std;

Leitor::Leitor(const string& filename) : filename(filename) {}

Leitor::~Leitor() = default;

void Leitor::read() {
    cout << "lendo arquivo " << filename << endl;

    ifstream file(filename, ios::binary);
    if (!file) {
        cout << "Nao foi possivel abrir o arquivo." << endl;
        return;
    }

    u4 magic = readu4(file);
    if (magic == 0xCAFEBABE) {
        cout << "Arquivo Java valido!" << endl;
    }
}

u2 Leitor::toBigEndian(u2 value) {
    return (value >> 8) | (value << 8);
}

u4 Leitor::toBigEndian(u4 value) {
    return ((value >> 24) & 0x000000FF) |
           ((value >> 8) & 0x0000FF00) |
           ((value << 8) & 0x00FF0000) |
           ((value << 24) & 0xFF000000);
}

u4 Leitor::readu4(ifstream& f) {
    u1 buffer[4];
    f.read(reinterpret_cast<char*>(buffer), 4);
    return (static_cast<u4>(buffer[0]) << 24) |
           (static_cast<u4>(buffer[1]) << 16) |
           (static_cast<u4>(buffer[2]) << 8) |
           static_cast<u4>(buffer[3]);
}
