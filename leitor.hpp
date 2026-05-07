#ifndef LEITOR_HPP
#define LEITOR_HPP

#include <fstream>
#include <string>

#include "estrutura_dados.hpp"

class Leitor {
public:
    explicit Leitor(const std::string& filename);
    ~Leitor();

    void read(u1 *buffer, size_t length);

    u4 readu4();
    u2 readu2();
    u1 readu1();

private:
    std::string filename;
    std::ifstream file;

    u2 toBigEndian(u2 value);
    u4 toBigEndian(u4 value);

};

#endif // LEITOR_HPP