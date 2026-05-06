#include <iostream>
#include <string>
#include "leitor.hpp"

using namespace std;

int main(int argc, char* argv[]) {

    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " <arquivo.class>" << endl;
        return 1;
    }

    Leitor leitor(argv[1]);
    leitor.read();

    return 0;
}