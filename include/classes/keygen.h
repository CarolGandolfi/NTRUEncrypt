#ifndef KEYGEN_H
#define KEYGEN_H

#include "polynomial.h"

struct NTRUParams {
    int N;
    int p;
    int q;
    int d; // número de coeficientes 1 e -1
};

struct NTRUKeyPair {
    Polynomial f;
    Polynomial fp;
    Polynomial fq;
    Polynomial g;
    Polynomial h;

    // Construtor explícito
    NTRUKeyPair(int N)
        : f(N), fp(N), fq(N), g(N), h(N) {}
};

NTRUKeyPair generateKeyPair(const NTRUParams& params);
NTRUKeyPair generateKeyPairFromFG(const NTRUParams& params, Polynomial f, Polynomial g);


#endif
