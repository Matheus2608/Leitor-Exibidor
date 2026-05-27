# Leitor-Exibidor

Leitor-Exibidor é uma ferramenta simples para ler arquivos Java `.class` e exibir suas estruturas internas (constant pool, fields, methods, etc.).

Build e execução
-----------------

Requisitos: `g++` (compatível com C++11/C++17) e `make`.

1) Compilar o projeto:

```bash
make
```

2) Executar o binário (passar o arquivo `.class` como argumento):

```bash
make run ARGS="exemplos/Hello.class"
# ou diretamente
./bin/leitor-exibidor exemplos/Hello.class
```

Compilação manual (sem make)
-----------------------------

```bash
mkdir -p bin obj
g++ -std=c++11 -Wall -Wextra -O2 -c main.cpp     -o obj/main.o
g++ -std=c++11 -Wall -Wextra -O2 -c leitor.cpp   -o obj/leitor.o
g++ -std=c++11 -Wall -Wextra -O2 -c parser.cpp   -o obj/parser.o
g++ -std=c++11 -Wall -Wextra -O2 -c exibidor.cpp -o obj/exibidor.o
g++ -std=c++11 -Wall -Wextra -O2 -c disasm.cpp   -o obj/disasm.o
g++ -std=c++11 -Wall -Wextra -O2 obj/main.o obj/leitor.o obj/parser.o obj/exibidor.o obj/disasm.o -o bin/leitor-exibidor
```

Ou em uma linha:

```bash
mkdir -p bin && g++ -std=c++11 -Wall -Wextra -O2 main.cpp leitor.cpp parser.cpp exibidor.cpp disasm.cpp -o bin/leitor-exibidor
```

Testes
------

Os testes ficam em `tests/`. Para compilar e executar os testes use:

```bash
make test
```

Isso compila o projeto e executa todos os binários presentes em `tests/`.

Limpeza
-------

```bash
make clean
```

Observações
-----------

- Caso os testes dependam de arquivos `.class` de exemplo, certifique-se de que o caminho nos testes esteja correto (por exemplo `tests/hello.cpp` referencia `../exemplos/Hello.class`).
- Se quiser executar um teste específico direto, rode `./bin/tests/<nome_do_teste>` após `make test` compilar os testes.

