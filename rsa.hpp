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

#define BLOCK_LENGTH 5

string digitize(string text);
vector<string> cutting(string text, uint64_t n);

vector<string> rsa_encrypt(string plaintext, pair<uint64_t,uint64_t> public_key);
string rsa_decrypt(vector<string> ciphertext, pair<uint64_t,uint64_t> private_key);

#endif