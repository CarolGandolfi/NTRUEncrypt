#include "../include/util.h"
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include "../include/classes/polynomial.h"


// Gera número aleatório entre min e max (inclusive)
int randomInt(int min, int max) {
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

// Gera um polinômio ternário (valores -1, 0, 1) com N coeficientes
// e exatamente 'ones' coeficientes iguais a 1, 'neg_ones' iguais a -1
std::vector<int> generateTernaryPolynomial(int N, int ones, int neg_ones) {
    std::vector<int> poly(N, 0);
    int count = 0;

    while (count < ones) {
        int idx = randomInt(0, N - 1);
        if (poly[idx] == 0) {
            poly[idx] = 1;
            count++;
        }
    }

    count = 0;
    while (count < neg_ones) {
        int idx = randomInt(0, N - 1);
        if (poly[idx] == 0) {
            poly[idx] = -1;
            count++;
        }
    }

    return poly;
}

// Imprime os coeficientes do polinômio
void printPolynomial(const std::vector<int>& poly) {
    std::cout << "[ ";
    for (int coeff : poly) {
        std::cout << coeff << ", ";
    }
    std::cout << "]" << std::endl;
}

std::string get_message_from_file(std::string filename) {
    std::ifstream file(filename);
    if(!file.is_open()) {
        throw std::runtime_error("File not Open.");
    }

    std::string line;
    std::ostringstream oss;

    while(std::getline(file,line)) {
        oss << line << std::endl;
    }

    size_t message_size = oss.str().size();

    return oss.str().substr(0,message_size-1);
}

Polynomial fromText(const std::string& text, int N) {
    Polynomial poly(N);
    for (int i = 0; i < N && i < (int)text.size(); ++i) {
        poly[i] = static_cast<int>(text[i]);
    }
    return poly;
}

std::string toText(const Polynomial& p) {
    std::string result;
    for (int i = 0; i < p.size(); ++i) {
        int c = p[i];

        // Converte apenas caracteres ASCII visíveis (0 a 126), substitui os outros por '.'
        if (c >= 0 && c <= 255)
            result += static_cast<char>(c);
        else
            result += '.';
    }
    return result;
}