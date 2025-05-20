#include "include/classes/keygen.h"
#include "include/classes/crypto.h"
#include "include/util.h"
#include <chrono>
#include <fstream>
#include <iostream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Uso: ./ntru <caminho_do_arquivo_txt>" << std::endl;
        return 1;
    }

    std::string message = get_message_from_file(argv[1]);
    std::cout << "====    Plain Text     ====" << std::endl;
    std::cout << message << std::endl;
    std::cout << "==== End of Plain Text ====" << std::endl;

    // === CONFIGURAÇÃO DE PARÂMETROS NTRU ===
    NTRUParams params;
    params.N = 1543; // Deve ser >= tamanho da mensagem
    params.p = 127;
    params.q = 2053;
    params.d = 11;

    // === GERAÇÃO DE CHAVES ===
    std::cout << "[INFO] Gerando chave NTRU..." << std::endl;
    NTRUKeyPair keypair = generateKeyPair(params);

    // === CONVERSÃO DA MENSAGEM PARA POLINÔMIO ===
    Polynomial m = fromText(message, params.N);
    m = polyMod(m, params.p);

    // === CIFRAGEM ===
    auto start = std::chrono::high_resolution_clock::now();
    Polynomial cipher = encrypt(m, keypair.h, params);
    auto end = std::chrono::high_resolution_clock::now();

    auto encryptTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "***Time to Encrypt: " << encryptTime.count() << " us" << std::endl;

    std::cout << "===    Cipher Coeffs   ===" << std::endl;
    printPolynomial(cipher);
    std::cout << "=== End of Cipher Coeffs ===" << std::endl;

    // === DECRIPTAÇÃO ===
    start = std::chrono::high_resolution_clock::now();
    Polynomial decrypted = decrypt(cipher, keypair.f, keypair.fp, params);
    end = std::chrono::high_resolution_clock::now();

    auto decryptTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "***Time to Decrypt: " << decryptTime.count() << " us" << std::endl;

    std::cout << "====    Decrypted Text     ====" << std::endl;
    std::cout << toText(decrypted) << std::endl;
    std::cout << "==== End of Decrypted Text ====" << std::endl;

    return 0;
}
