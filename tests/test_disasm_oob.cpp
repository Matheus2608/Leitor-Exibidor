// Verifica que disassembleCode lança exceção para bytecode truncado,
// em vez de acessar memória fora dos limites do vetor.

#include <cassert>
#include <stdexcept>
#include <iostream>
#include <vector>
#include "disasm.hpp"
#include "estrutura_dados.hpp"

// class_info vazio serve como contexto; esses testes não precisam de cp real.
static class_info empty_cls;

static void test_bipush_sem_operando()
{
    // 0x10 = bipush; precisa de 1 byte de operando que não existe
    std::vector<u1> code = {0x10};
    bool threw = false;
    try {
        disassembleCode(code, 1, empty_cls);
    } catch (const std::runtime_error &) {
        threw = true;
    }
    assert(threw && "bipush sem operando deve lançar runtime_error");
}

static void test_invokevirtual_sem_operando()
{
    // 0xB6 = invokevirtual; precisa de 2 bytes de índice
    std::vector<u1> code = {0xB6};
    bool threw = false;
    try {
        disassembleCode(code, 1, empty_cls);
    } catch (const std::runtime_error &) {
        threw = true;
    }
    assert(threw && "invokevirtual sem operando deve lançar runtime_error");
}

static void test_ifeq_sem_operando()
{
    // 0x99 = ifeq; precisa de 2 bytes de offset
    std::vector<u1> code = {0x99};
    bool threw = false;
    try {
        disassembleCode(code, 1, empty_cls);
    } catch (const std::runtime_error &) {
        threw = true;
    }
    assert(threw && "ifeq sem operando deve lançar runtime_error");
}

static void test_iinc_sem_segundo_operando()
{
    // 0x84 = iinc; precisa de 2 bytes de operando; fornecemos só 1
    std::vector<u1> code = {0x84, 0x01};
    bool threw = false;
    try {
        disassembleCode(code, 2, empty_cls);
    } catch (const std::runtime_error &) {
        threw = true;
    }
    assert(threw && "iinc com operando incompleto deve lançar runtime_error");
}

static void test_goto_w_sem_operando()
{
    // 0xC8 = goto_w; precisa de 4 bytes de offset
    std::vector<u1> code = {0xC8, 0x00};
    bool threw = false;
    try {
        disassembleCode(code, 2, empty_cls);
    } catch (const std::runtime_error &) {
        threw = true;
    }
    assert(threw && "goto_w com operando incompleto deve lançar runtime_error");
}

static void test_bytecode_valido_nao_lanca()
{
    // return (0xB1) é opcode de 1 byte — não deve lançar
    std::vector<u1> code = {0xB1};
    bool threw = false;
    try {
        disassembleCode(code, 1, empty_cls);
    } catch (const std::exception &) {
        threw = true;
    }
    assert(!threw && "return válido não deve lançar exceção");
}

int main()
{
    test_bipush_sem_operando();
    test_invokevirtual_sem_operando();
    test_ifeq_sem_operando();
    test_iinc_sem_segundo_operando();
    test_goto_w_sem_operando();
    test_bytecode_valido_nao_lanca();

    std::cout << "test_disasm_oob: todos os testes passaram." << std::endl;
    return 0;
}
