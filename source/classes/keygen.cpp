#include "../../include/classes/keygen.h"
#include "../../include/classes/polynomial.h"
#include "../../include/util.h"
#include <stdexcept>

NTRUKeyPair generateKeyPair(const NTRUParams& params) {
    Polynomial f, g, fp, fq, h, aux;

    while (true) {
        try {
            f = generateTernaryPolynomial(params.N, params.d+1, params.d);
            aux = generateXNMinus1(params.N);
            fp = polyInverse(f, aux, params.p);
            fq = polyInverse(f, aux, params.q);

            break;
        } catch (...) {
            std::cout << "Erro ao calcular fp ou fq. Tentando novamente..." << std::endl;
            continue; // tenta novamente com outro f
        }
    }

    g = generateTernaryPolynomial(params.N, params.d, params.d);
    Polynomial pg = std::vector<int>(params.N, 0);
    pg[0] = params.p;

    h = polyMul(polyMul(pg, fq, params.q), g, params.q);

    NTRUKeyPair keypair(params.N);
    keypair.f = f;
    keypair.fp = fp;
    keypair.fq = fq;
    keypair.g = g;
    keypair.h = h;
    return keypair;
}

NTRUKeyPair generateKeyPairFromFG(const NTRUParams& params, Polynomial f, Polynomial g) {
    // Gera fp e fq a partir de f
    Polynomial fp, fq, h, aux;

    while (true) {
        try {
            aux = generateXNMinus1(params.N);
            
            fp = polyInverse(f, aux, params.p);
            
            fq = polyInverse(f, aux, params.q);

            break;
        } catch (...) {
            std::cout << "Erro ao calcular fp ou fq. Tentando novamente..." << std::endl;
            continue; // tenta novamente com outro f
        }
    }

    Polynomial pg = std::vector<int>(params.N, 0);
    pg[0] = params.p;

    h = polyTru(polyMul(pg, polyMul( fq, g, params.q), params.q), params.N, params.q);

    NTRUKeyPair keypair(params.N);
    keypair.f = f;
    keypair.fp = fp;
    keypair.fq = fq;
    keypair.g = g;
    keypair.h = h;
    return keypair;
}
