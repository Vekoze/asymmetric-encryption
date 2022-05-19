#ifndef CIPHER_HPP
#define CIPHER_HPP

#include <random>
#include <ctime>

using namespace std;

bool is_prime(uint64_t n);
uint64_t random_prime(mt19937& gen);

int64_t gcd_extended(uint64_t a, uint64_t b, int64_t* x, int64_t* y);
uint64_t power(uint64_t x, uint64_t y, uint64_t p);

#endif