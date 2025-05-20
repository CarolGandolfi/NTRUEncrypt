#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <string>

using Polynomial = std::vector<int>;

Polynomial polyInverse(const Polynomial& a, const Polynomial& m, int mod);
void printPoly(const Polynomial& p, int mod);
Polynomial polyAdd(const Polynomial& a, const Polynomial& b, int mod);
Polynomial polySub(const Polynomial& a, const Polynomial& b, int mod);
Polynomial polyMul(const Polynomial& a, const Polynomial& b, int mod);
Polynomial polyMod(const Polynomial& a, int k);
Polynomial polyDivMod(const Polynomial& a, const Polynomial& b, Polynomial& rem, int mod);
Polynomial polyGCD(const Polynomial& a, const Polynomial& b, Polynomial& sOut, int mod);
Polynomial generateXNMinus1(int N);
Polynomial polyTru(const Polynomial& p, int N, int mod);
Polynomial centerLiftPoly(const Polynomial& poly, int q);

#endif
