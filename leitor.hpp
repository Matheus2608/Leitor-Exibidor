#ifndef LEITOR_HPP
#define LEITOR_HPP

#include <fstream>
#include <string>

#include "estrutura_dados.hpp"

class Leitor {
public:
    explicit Leitor(const std::string& filename);
    ~Leitor();

    void read();

private:
    std::string filename;

    u2 toBigEndian(u2 value);
    u4 toBigEndian(u4 value);
    u4 readu4(std::ifstream& f);
};

#endif // LEITOR_HPP