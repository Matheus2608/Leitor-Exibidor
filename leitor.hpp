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
    class_info getClassInfo() const { return classInfo; }

private:
    std::string filename;
    std::ifstream file;
    class_info classInfo;

    u2 toBigEndian(u2 value);
    u4 toBigEndian(u4 value);
    u4 readu4();
    u2 readu2();
    u1 readu1();
    
    void magicCheck(); 
    void minorVersionCheck();
    void majorVersionCheck();
    void constantPoolCountCheck();
    void constantPoolCheck();

};

#endif // LEITOR_HPP