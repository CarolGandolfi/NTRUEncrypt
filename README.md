# NTRUEncrypt

Este projeto implementa do zero o algoritmo de criptografia assimétrica **NTRUEncrypt**, utilizando aritmética de polinômios e segurança baseada em reticulados. A implementação foi feita inteiramente em C++, sem o uso de bibliotecas externas.

---

## 🔧 Como compilar:

```bash
g++ -o ntru main.cpp source/classes/* source/util.cpp
```

---

## ▶️ Como executar:

```bash
./ntru ./test-cases/arq.txt
```

A saída será algo como:

```
====    Plain Text     ====
O que será, que será?
Que andam suspirando pelas alcovas
...
==== End of Plain Text ====

***Time to Encrypt: 154321 us

===    Cipher Coeffs   ===
[ 843 1289 0 119 754 ... ]
=== End of Cipher Coeffs ===

***Time to Decrypt: 219876 us

====    Decrypted Text     ====
O que será, que será?
Que andam suspirando pelas alcovas
...
==== End of Decrypted Text ====
```

---

## ⚙️ Como foi implementado?

- A implementação segue a especificação do algoritmo NTRU original proposto por Hoffstein, Pipher e Silverman.
- Os parâmetros utilizados são ajustáveis: `N`, `p`, `q`, `d`.
- Inclui:
  - Geração de chaves (`f`, `g`, inversos `f⁻¹ mod p` e `f⁻¹ mod q`)
  - Operações com polinômios cíclicos
  - Ciframento com polinômio aleatório `r`
  - Deciframento e reconstrução do texto original

---

## 🧠 Conceitos envolvidos

- Criptografia pós-quântica baseada em reticulados
- Polinômios em anéis Z[X]/(X^N-1)
- Reduções modulares, center-lift e inversão polinomial
- Controle de overflow e integridade dos dados em C++

---

## 💾 Teste de memória

Use o script `memory-test.sh` para rodar o **Valgrind**:

```bash
./memory-test.sh
```

O resultado está salvo em:

```
experiment-result/memory/
```

---

## ⏱️ Teste de tempo

Use o script `time-test.sh` para medir o tempo de execução completo:

```bash
./time-test.sh
```

O resultado está salvo em:

```
experiment-result/test/
```

---

## 📁 Estrutura do projeto

```
include/
├── classes/
│   ├── polynomial.h
│   ├── keygen.h
│   ├── crypto.h
│   └── util.h

source/
├── classes/
│   ├── polynomial.cpp
│   ├── keygen.cpp
│   ├── crypto.cpp
├── util.cpp

test-cases/
└── arq.txt         # texto da música a ser criptografada

main.cpp            # ponto de entrada do programa
```

---

## 📚 Base Teórica

Implementado com base na proposta original de:

> Hoffstein, J., Pipher, J., & Silverman, J.H. (1998). [_NTRU: A ring-based public key cryptosystem._](NTRU.pdf)

---

## 👨‍💻 Autor

Implementado por Caroline Duarte Gandolfi — IME 🚀
