#ifndef CRYPTO_H
#define CRYPTO_H

#include "keygen.h"

Polynomial encrypt(const Polynomial& message, const Polynomial& h, const NTRUParams& params);
Polynomial decrypt(const Polynomial& ciphertext, const Polynomial& f, const Polynomial& fp, const NTRUParams& params);

#endif
