#ifndef PARSER_HPP
#define PARSER_HPP

#include "estrutura_dados.hpp"
#include <string>
#include "constants.hpp"
#include "leitor.hpp"

class Parser
{
public:
    explicit Parser(const std::string &filename);
    ~Parser();
    class_info getClassInfo() const { return classInfo; }

    class_info parse();

private:
    class_info classInfo;
    Leitor leitor;

    void magicCheck(); 
    void minorVersionCheck();
    void majorVersionCheck();
    void constantPoolCountCheck();
    void constantPoolCheck();
};

#endif // PARSER_HPP