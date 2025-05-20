#include "../../include/classes/crypto.h"
#include "../../include/util.h"

Polynomial encrypt(const Polynomial& message, const Polynomial& h, const NTRUParams& params) {
    // printPolynomial(message);

    // Gera r com distribuição ternária
    Polynomial r = generateTernaryPolynomial(params.N, params.d, params.d);

    // e = r * h + m mod q
    Polynomial e = polyAdd(polyMul(r, h, params.q), message, params.q);
    e = polyTru(e, params.N, params.q);
    e = centerLiftPoly(e, params.q);
    
    return e;
}

Polynomial decrypt(const Polynomial& ciphertext, const Polynomial& f, const Polynomial& fp, const NTRUParams& params) {
    // a = f * e mod q
    Polynomial a = polyTru(polyMul(f, ciphertext, params.q), params.N, params.q);
    a=centerLiftPoly(a, params.q);
    
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] > params.q / 2 || a[i] < -params.q / 2) {
            std::cout << "!!!! overflow em a[" << i << "] = " << a[i] << std::endl;
        }
    }

    // aModP = a mod p
    Polynomial aModP = polyMod(a, params.p);

    // m = f_p^-1 * a mod p
    Polynomial m = polyMul(fp, aModP, params.p);
    m = polyTru(m, params.N, params.p);
    // m = centerLiftPoly(m, params.p);

    // printPolynomial(m);
    return m;
}


