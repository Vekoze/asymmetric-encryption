#include "hash.hpp"

string hash_file(string path){
    string hash = string();
    ifstream file(path, ios::binary);
    if(!file) return string();

    vector<int> file_xor(M,0);

    for(;;)
        vector<uint8_t> buffer(N*M, 0);
        file.read((char*) &buffer[0], buffer.size());

        uint8_t block[M][N];
        for(int i = 0; i<M; i++){
            copy(buffer.begin(), buffer.begin()+N, block[i]);
            buffer.erase(buffer.begin(), buffer.begin()+N);
        }

        for(int i = 0; i<M; i++){
            int temp_xor = 0;
            for(int j = 0; j<N; j++){
                temp_xor ^= block[i][j];
            }
            file_xor[i] += temp_xor;
        }

        if(file.eof()) break;
    }

    for(auto x : file_xor){
        hash+=to_string(x);
    }

    file.close();
    return hash;
}