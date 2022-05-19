#include "rsa.hpp"

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

    if(!file_path.empty()){
        ofstream file(file_path);
        file << "-----BEGIN PUBLIC KEY-----\n";
        file << "-----END PUBLIC KEY-----\n";
    }

    return true;
}

bool RSAKey::create_private_key(string file_path){

    int64_t x, y;
    int64_t g = gcd_extended(e, euler, &x, &y);

    //https://math.stackexchange.com/questions/355066/find-the-inverse-modulo-of-a-number-got-a-negative-result
    d=(x<0) ? euler + x : x;

    if(!file_path.empty()){
        ofstream file(file_path);
        file << "-----BEGIN RSA PRIVATE KEY-----\n";

        file << "-----END RSA PRIVATE KEY-----\n";
    }

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

/* --- --- --- --- --- --- */

string digitization(string plaintext){
    string out = "";
    for(char c : plaintext)
        out+=to_string(c-' ');
    return out;
}

vector<string> cutting(string text, uint64_t n){
    int len = text.length();
    int n_len = to_string(n).length();
    int block_len = ( (n_len-1) % 2 == 0) ? n_len-1 : n_len-2;
    int blocks_number = ceil( (double)len/block_len );

    vector<string> blocks(blocks_number);

    while(text.length()%block_len!=0)
        text+='0';

    int pos = 0;
    while(!text.empty()){
        blocks[pos++] = text.substr(0,block_len);
        text.erase(text.begin(), text.begin()+block_len);
    }

    for(auto b : blocks){
        cout << b << " ";
    }
    cout << endl;

    return blocks;
}

string rsa_block(string text, pair<uint64_t,uint64_t> public_key){
    return to_string( power(stoi(text), public_key.first, public_key.second) );
}

string rsa_encrypt(string plaintext, pair<uint64_t,uint64_t> public_key) {
    string ciphertext = "";
    string digitized = digitization(plaintext);
    vector<string> blocks = cutting(digitized, public_key.second);

    for(string block : blocks){
        cout << "encrypt block: " << rsa_block(block, public_key) << endl;
        ciphertext+=rsa_block(block, public_key)+' ';
    }

    return ciphertext;
}

string rsa_decrypt(string ciphertext, pair<uint64_t,uint64_t> private_key) {
    string plaintext = "";
    //cutting(ciphertext, private_key.second);
    return plaintext;
}