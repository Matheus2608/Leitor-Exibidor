// Verifica que tableswitch com high=INT32_MAX é rejeitado antes de entrar
// em um loop de ~2^31 iterações com UB por overflow de int32_t.
// Sem a correção, disassembleCode trava ou crashe; com ela, lança runtime_error.

#include <cassert>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <climits>
#include "disasm.hpp"
#include "estrutura_dados.hpp"

static class_info empty_cls;

// Monta os bytes de um tableswitch com padding e low/high arbitrários.
// O vetor resultante começa no opcode 0xAA e tem padding para alinhar
// em offset 1 (pc=0 no disassembler → padding de 3 bytes).
static std::vector<u1> make_tableswitch(int32_t low, int32_t high, int32_t def_offset)
{
    // pc do opcode = 0; após incrementar pc++, pc=1; padding até múltiplo de 4 → pc=4
    std::vector<u1> code;
    code.push_back(0xAA);       // tableswitch
    code.push_back(0x00);       // padding
    code.push_back(0x00);
    code.push_back(0x00);
    // default offset (4 bytes big-endian)
    code.push_back((def_offset >> 24) & 0xFF);
    code.push_back((def_offset >> 16) & 0xFF);
    code.push_back((def_offset >>  8) & 0xFF);
    code.push_back( def_offset        & 0xFF);
    // low
    code.push_back((low >> 24) & 0xFF);
    code.push_back((low >> 16) & 0xFF);
    code.push_back((low >>  8) & 0xFF);
    code.push_back( low        & 0xFF);
    // high
    code.push_back((high >> 24) & 0xFF);
    code.push_back((high >> 16) & 0xFF);
    code.push_back((high >>  8) & 0xFF);
    code.push_back( high        & 0xFF);
    // não incluímos entradas de offset: bytes insuficientes propositalmente
    return code;
}

static void test_tableswitch_high_int32_max()
{
    // low=0, high=INT32_MAX: ~2 bilhões de entradas; deve ser rejeitado
    std::vector<u1> code = make_tableswitch(0, INT32_MAX, 0);
    u4 len = static_cast<u4>(code.size());
    bool threw = false;
    try {
        disassembleCode(code, len, empty_cls);
    } catch (const std::runtime_error &) {
        threw = true;
    }
    assert(threw && "tableswitch com high=INT32_MAX deve lançar runtime_error");
}

static void test_tableswitch_high_menor_que_low()
{
    // high < low é inválido pela spec JVM
    std::vector<u1> code = make_tableswitch(10, 5, 0);
    u4 len = static_cast<u4>(code.size());
    bool threw = false;
    try {
        disassembleCode(code, len, empty_cls);
    } catch (const std::runtime_error &) {
        threw = true;
    }
    assert(threw && "tableswitch com high < low deve lançar runtime_error");
}

static void test_tableswitch_dados_insuficientes()
{
    // count = 3 entradas mas sem bytes para elas
    std::vector<u1> code = make_tableswitch(0, 2, 0);
    // não acrescentamos os 3*4=12 bytes de offsets
    u4 len = static_cast<u4>(code.size());
    bool threw = false;
    try {
        disassembleCode(code, len, empty_cls);
    } catch (const std::runtime_error &) {
        threw = true;
    }
    assert(threw && "tableswitch sem offsets deve lançar runtime_error");
}

int main()
{
    test_tableswitch_high_int32_max();
    test_tableswitch_high_menor_que_low();
    test_tableswitch_dados_insuficientes();

    std::cout << "test_tableswitch_overflow: todos os testes passaram." << std::endl;
    return 0;
}
