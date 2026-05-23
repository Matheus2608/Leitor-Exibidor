#ifndef LEITOR_HPP
#define LEITOR_HPP

#include <fstream>
#include <string>
#include <vector>
#include <cstddef>

#include "estrutura_dados.hpp"

class Leitor {
public:
    explicit Leitor(const std::string& filename);
    ~Leitor();

    void read(u1 *buffer, size_t length);

    std::vector<u1> read_bytes(size_t length);

    // stream position helpers
    size_t tell();
    void seek(size_t pos);

    u4 readu4();
    u2 readu2();
    u1 readu1();

private:
    std::string filename;
    std::ifstream file;

};

#endif // LEITOR_HPP
