#ifndef EXIBIDOR_HPP
#define EXIBIDOR_HPP

#include <fstream>
#include <string>
#include <utility>

#include "estrutura_dados.hpp"
#include "constants.hpp"
#include "parser.hpp"

class Exibidor {
public:
    explicit Exibidor(const std::string& filename);
    ~Exibidor();

    void display();

private:
    std::string filename;
    class_info classInfo;

    void constantPoolDisplay();
    void fieldsDisplay();
    void methodsDisplay();
    void attributesDisplay();
    std::pair<std::string, std::string> getMethodSignature(const method_info &method);
    std::string toType(const std::string& descriptor);
};

#endif // EXIBIDOR_HPP