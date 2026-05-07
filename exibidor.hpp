#ifndef EXIBIDOR_HPP
#define EXIBIDOR_HPP

#include <fstream>
#include <string>

#include "estrutura_dados.hpp"

class Exibidor {
public:
    explicit Exibidor(const std::string& filename);
    ~Exibidor();

    void display();

private:
    std::string filename;

    void constantPoolDisplay();
    void fieldsDisplay();
    void methodsDisplay();
    void attributesDisplay();
};

#endif // EXIBIDOR_HPP