#include "leitor.hpp"
#include <iostream>
#include "constants.hpp"

using namespace std;

Leitor::Leitor(const string &filename) : filename(filename), file(filename, ios::binary) {}

Leitor::~Leitor() = default;

void Leitor::read(u1 *buffer, size_t length)
{
    file.read(reinterpret_cast<char *>(buffer), length);
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
