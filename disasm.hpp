#ifndef DISASM_HPP
#define DISASM_HPP

#include <vector>
#include "estrutura_dados.hpp"

void disassembleCode(const std::vector<u1> &code, u4 code_length, const class_info &cls);

#endif // DISASM_HPP
