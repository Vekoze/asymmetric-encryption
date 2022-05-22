#include "cipher.hpp"
#include "rsa.hpp"
#include "rsakey.hpp"
#include "hash.hpp"

bool is_prime(uint64_t n){
    if (n == 2 || n == 3)
        return true;
        
    if (n <= 1 || n % 2 == 0 || n % 3 == 0)
        return false;

    for (int i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;

    return true;
}

uint64_t random_prime(mt19937& gen){

    uniform_int_distribution<uint64_t> distrib(1E3, 1E5);
    uint64_t n;
    do {
        n = distrib(gen);
    } while(!is_prime(n));
    return n;
}

// Function for extended Euclidean Algorithm
int64_t gcd_extended(uint64_t a, uint64_t b, int64_t* x, int64_t* y){
    if (a == 0){
        *x = 0, *y = 1;
        return b;
    }
     
    int64_t x1, y1;
    int64_t gcd = gcd_extended(b % a, a, &x1, &y1);
 
    *x = y1 - (b / a) * x1;
    *y = x1;
 
    return gcd;
}

// Exponentiation modulaire
uint64_t power(uint64_t x, uint64_t y, uint64_t p){
    uint64_t res = 1;

    x = x % p;

    if (x == 0) return 0;

    while (y > 0){
        if (y & 1)
            res = (res*x) % p;

        y = y>>1;
        x = (x*x) % p;
    }
    return res;
}

int main(){

    mt19937 gen(time(nullptr));

    RSAKey rsa_key(gen);
    while(!rsa_key.create_public_key());
    while(!rsa_key.create_private_key());

    rsa_key.summary();

    vector<string> encrypt = rsa_encrypt("0_testRSA_9", rsa_key.get_public_key());
    string decrypt = rsa_decrypt(encrypt, rsa_key.get_private_key());
    
    cout << "decrypt: " << decrypt << endl;

    cout << hash_file("test.txt") << endl;

    return 0;
}