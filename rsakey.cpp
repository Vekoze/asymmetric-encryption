#include "rsakey.hpp"

RSAKey::RSAKey(mt19937& gen) : gen(gen) {}

RSAKey::~RSAKey(){}

bool RSAKey::create_public_key(string file_path){
    p = random_prime(gen);
    q = random_prime(gen);
    while(p==q)
        q = random_prime(gen);

    n = p*q;
    euler = (p-1)*(q-1);

    e = 1;
    while(++e<euler && __gcd(e,euler)!=1);
    if(e>=euler)
        return false;

    return true;
}

bool RSAKey::create_private_key(string file_path){

    int64_t x, y;
    int64_t g = gcd_extended(e, euler, &x, &y);

    //https://math.stackexchange.com/questions/355066/find-the-inverse-modulo-of-a-number-got-a-negative-result
    d=(x<0) ? euler + x : x;

    return true;
}

pair<uint64_t, uint64_t> RSAKey::get_public_key() const {
    return make_pair(e,n);
}

pair<uint64_t, uint64_t> RSAKey::get_private_key() const {
    return make_pair(d,n);
}

void RSAKey::summary() const {
    cout << "---RSA Summary---" << endl;
    cout << "p: " << p << endl;
    cout << "q: " << q << endl;
    cout << "n: " << n << endl;
    cout << "euler: " << euler << endl;
    cout << "e: " << e << endl;
    cout << "d: " << d << endl;
    cout << "-----------------" << endl;
}
