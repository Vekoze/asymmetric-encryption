#ifndef RSAKEY_HEADER
#define RSAKEY_HEADER

#include <iostream>
#include <string>
#include <climits>
#include <fstream>
#include <random>
#include <algorithm>
#include "cipher.hpp"

using namespace std;

class RSAKey {

private:
    uint64_t p;         // secret prime number
    uint64_t q;         // secret prime number
    uint64_t n;         // public modulus
    uint64_t euler;     // prime number
    uint64_t e;         // public exponent
    uint64_t d;         // secret exponent

    mt19937 gen;

public:
    RSAKey(mt19937& gen);
    ~RSAKey();

    bool create_public_key(string file_path = string());
    bool create_private_key(string file_path = string());

    pair<uint64_t, uint64_t> get_public_key() const;
    pair<uint64_t, uint64_t> get_private_key() const;

    void summary() const;

};

#endif