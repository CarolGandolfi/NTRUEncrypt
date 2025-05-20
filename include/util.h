#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <random>
#include <iostream>
#include <chrono>
#include "../include/classes/polynomial.h"

// Função para gerar número aleatório entre min e max
int randomInt(int min, int max);

// Função para gerar um polinômio com coeficientes ternários (-1, 0, 1)
std::vector<int> generateTernaryPolynomial(int N, int ones, int neg_ones);

// Imprime o polinômio
void printPolynomial(const std::vector<int>& poly);

std::string get_message_from_file(std::string filename);
Polynomial fromText(const std::string& text, int N);
std::string toText(const std::vector<int>& poly);
void saveToFile(const std::string& content, const std::string& filename);

#endif
