// deve testar se o leitor e exibidor estão funcionando corretamente, ou seja, se eles conseguem ler e exibir as informações do arquivo .class corretamente
// do arquivo Hello.class

#include <iostream>
#include <cassert>
#include "../leitor.hpp"

int main() {
    Leitor leitor("../exemplos/Hello.class");
    leitor.read();
    class_info info = leitor.getClassInfo();


    assert(info.magic_number == 0xCAFEBABE);
    assert(info.minor_version == 0);
    assert(info.major_version == 65);
    assert(info.constant_pool_count == 59);
    return 0;
}