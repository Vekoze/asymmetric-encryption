#include "rsa.hpp"

string digitize(string plaintext){
    string out = "";
    for(char c : plaintext)
        out+=to_string(c-' ');
    return out;
}

vector<string> rsa_encrypt(string plaintext, pair<uint64_t,uint64_t> public_key) {
    string ascii = string();
    for(char c : plaintext){
        int x = c-' ';
        ascii+= (x<10) ? '0'+to_string(x) : to_string(x);
    }

    while(ascii.length()%BLOCK_LENGTH!=0)
        ascii+='0';

    int blocks_number = ceil( (double)ascii.length()/BLOCK_LENGTH );
    int pos = 0;
    vector<string> blocks(blocks_number);
    while(!ascii.empty()){
        blocks[pos++] = ascii.substr(0,BLOCK_LENGTH);
        ascii.erase(ascii.begin(), ascii.begin()+BLOCK_LENGTH);
    }

    for(string &block : blocks)
        block=to_string( power(stoull(block), public_key.first, public_key.second) );   

    return blocks;
}

string rsa_decrypt(vector<string> blocks, pair<uint64_t,uint64_t> private_key) {
    string plaintext = string();
    string ascii = string();

    for(string &block : blocks){
        block=to_string( power(stoull(block), private_key.first, private_key.second) );
        ascii+=block;
    }

    for(int i = 0; i<ascii.length()-1; i+=2){
        string current = ascii.substr(i, 2);
        plaintext+=stoi(current)+' ';
    }

    return plaintext;
}