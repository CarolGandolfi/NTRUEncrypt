#include "../../include/classes/polynomial.h"
#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

void normalize(Polynomial& p, int mod) {
    for (int& x : p) x = (x % mod + mod) % mod;
}

void removeTrailingZeros(Polynomial& p) {
    while (!p.empty() && p.back() == 0) p.pop_back();
}

int modinv(int a, int m) {
    // Inverso modular de a mod m (a * x ≡ 1 mod m)
    a = (a % m + m) % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1; // Não existe
}

Polynomial polyMod(const Polynomial& a, int k) {
    Polynomial res = a;
    for (int& coef : res) {
        coef = ((coef % k) + k) % k; 
    }
    return res;
}

Polynomial polyTru(const Polynomial& p, int N, int mod) {
    Polynomial result(N, 0);
    for (int i = 0; i < p.size(); ++i) {
        result[i % N] = (result[i % N] + p[i]) % mod;
    }
    return result;
}


void printPoly(const Polynomial& p, int mod) {
    bool first = true;
    for (int i = p.size() - 1; i >= 0; --i) {
        int c = (p[i] % mod + mod) % mod;
        if (c == 0) continue;
        if (!first) cout << " + ";
        if (i == 0) cout << c;
        else if (c == 1) cout << "x^" << i;
        else cout << c << "x^" << i;
        first = false;
    }
    if (first) cout << "0";
    cout << endl;
}

Polynomial polyAdd(const Polynomial& a, const Polynomial& b, int mod) {
    int n = max(a.size(), b.size());
    Polynomial res(n, 0);
    for (int i = 0; i < n; i++) {
        if (i < a.size()) res[i] += a[i];
        if (i < b.size()) res[i] += b[i];
        res[i] = (res[i] % mod + mod) % mod;
    }
    return res;
}

Polynomial polySub(const Polynomial& a, const Polynomial& b, int mod) {
    int n = max(a.size(), b.size());
    Polynomial res(n, 0);
    for (int i = 0; i < n; i++) {
        int ai = (i < a.size()) ? a[i] : 0;
        int bi = (i < b.size()) ? b[i] : 0;
        res[i] = ((ai - bi) % mod + mod) % mod;
    }
    return res;
}

Polynomial polyMul(const Polynomial& a, const Polynomial& b, int mod) {
    Polynomial res(a.size() + b.size() - 1, 0);
    
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            int64_t product = static_cast<int64_t>(a[i]) * b[j];
            int64_t sum = static_cast<int64_t>(res[i + j]) + product;

            res[i + j] = static_cast<int>((sum % mod + mod) % mod);
        }
    }

    return res;
}



Polynomial polyDivMod(const Polynomial& a, const Polynomial& b, Polynomial& rem, int mod) {
    Polynomial q;
    rem = a;
    Polynomial bCopy = b;
    removeTrailingZeros(bCopy);
    int degB = bCopy.size()-1;

    int invLead = modinv(bCopy[degB], mod);
    if (invLead == -1) {
        throw runtime_error("Coeficiente líder de b(x) não tem inverso modular.");
    }

    while (rem.size() >= bCopy.size()) {
        int coef = rem.back() * invLead % mod;
        int deg = rem.size() - bCopy.size();

        Polynomial term(deg + 1, 0);
        term[deg] = coef;

        q = polyAdd(q, term, mod);
        Polynomial sub = polyMul(term, bCopy, mod);
        rem = polySub(rem, sub, mod);
        removeTrailingZeros(rem);
    }

    return q;
}

Polynomial polyGCD(const Polynomial& a, const Polynomial& b, Polynomial& sOut, int mod) {
    Polynomial r0 = a, r1 = b;
    Polynomial s0 = {1}, s1 = {0};
    while (!r1.empty()) {
        Polynomial q, r;
        q = polyDivMod(r0, r1, r, mod);
        Polynomial s2 = polySub(s0, polyMul(q, s1, mod), mod);
        r0 = r1; r1 = r;
        s0 = s1; s1 = s2;
    }
    int leadInv = modinv(r0.back(), mod);
    for (int& coeff : r0) coeff = (coeff * leadInv) % mod;
    for (int& coeff : s0) coeff = (coeff * leadInv) % mod;
    sOut = s0;
    return r0; // gcd
}

Polynomial polyInverse(const Polynomial& a, const Polynomial& m, int mod) {
    Polynomial s;
    Polynomial g = polyGCD(a, m, s, mod);
    if (g.size() == 1 && g[0] == 1) {
        return s; // Inversa
    } else {
        throw runtime_error("Inversa não existe");
    }
}

Polynomial generateXNMinus1(int N) {
    Polynomial res(N + 1, 0); // Cria um vetor com N+1 zeros
    res[0] = -1;        // Termo constante: -1
    res[N] = 1;         // Termo x^N: +1
    return res;
}

Polynomial centerLiftPoly(const Polynomial& poly, int q) {
    Polynomial result = poly;
    int threshold = q / 2;

    for (int& coeff : result) {
        if (coeff > threshold) {
            coeff -= q;
        }
    }

    return result;
}