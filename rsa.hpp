#ifndef RSA_HEADER
#define RSA_HEADER

#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>
#include <fstream>
#include <sstream>

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

string digitization(string text);
vector<string> cutting(string text, uint64_t n);

string rsa_block(string text, pair<uint64_t,uint64_t> key);

string rsa_encrypt(string plaintext, pair<uint64_t,uint64_t> public_key);
string rsa_decrypt(string ciphertext, pair<uint64_t,uint64_t> private_key);

#endif